#include "AudioClock.h"
#include "spdlog/spdlog.h"

AudioClock::AudioClock(FMOD::System* audioSystemContext)
	: system(audioSystemContext), track(nullptr), channel(nullptr),
	currentPositionMs(0), trackLengthMs(0), isPlaying(false) {}

AudioClock::~AudioClock() {
	if (track) {
		track->release();
	}
}

void AudioClock::LoadSong(const std::string& filePath) {
    if (track) {
        track->release();
        track = nullptr;
    }

    FMOD_RESULT result = system->createStream(filePath.c_str(), FMOD_DEFAULT, nullptr, &track);

    if (result == FMOD_OK) {
        spdlog::info("AudioClock successfully loaded: {}", filePath);
        result = track->getLength(&trackLengthMs, FMOD_TIMEUNIT_MS);
    }
    else {
        spdlog::error("AudioClock failed to load: {}", filePath);
    }
}

void AudioClock::Play() {
    if (track) {
        system->playSound(track, nullptr, false, &channel);
        isPlaying = true;
        isFinished = false;
    }
}

void AudioClock::Pause() {
    if (isPlaying) {
        channel->setPaused(true);
        isPlaying = false;
    }
}

void AudioClock::Resume() {
    if (!channel) return;

    bool isPaused = false;
    FMOD_RESULT result = channel->getPaused(&isPaused);

    if (result == FMOD_OK && isPaused) {
        channel->setPaused(false);
        isPlaying = true;
    }
}

void AudioClock::Stop() {
    if (channel) {
        channel->stop();
        isPlaying = false;
        currentPositionMs = 0;
    }
}

void AudioClock::Update() {
    if (isPlaying && channel) {
        bool isChannelPlaying = false;
        channel->isPlaying(&isChannelPlaying);

        if (isChannelPlaying) {
            channel->getPosition(&currentPositionMs, FMOD_TIMEUNIT_MS);
        }
        else {
            isPlaying = false;
            isFinished = true;
        }
    }
}

unsigned int AudioClock::GetSongPositionMs() const {
    return currentPositionMs;
}

unsigned int AudioClock::GetTrackLengthMs() const {
    return trackLengthMs;
}

bool AudioClock::IsPlaying() const {
    return isPlaying;
}

bool AudioClock::IsFinished() const {
    return isFinished;
}