#pragma once

#include <string>
#include "fmod.hpp"

class AudioClock {
public:
    AudioClock(FMOD::System* audioSystemContext);
    ~AudioClock();

    void LoadSong(const std::string& filePath);
    void Play();
    void Pause();
    void Resume();
    void Stop();

    void Update();

    uint32_t GetSongPositionMs() const;
    uint32_t GetTrackLengthMs() const;

    bool IsPlaying() const;
    bool IsFinished() const;

private:
    FMOD::System* system;
    FMOD::Sound* track;
    FMOD::Channel* channel;

    uint32_t currentPositionMs;
    uint32_t trackLengthMs;
    bool isPlaying;
    bool isFinished;
};