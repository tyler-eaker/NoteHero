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

    unsigned int GetSongPositionMs() const;
    unsigned int GetTrackLengthMs() const;

    bool IsPlaying() const;
    bool IsFinished() const;

private:
    FMOD::System* system;
    FMOD::Sound* track;
    FMOD::Channel* channel;

    unsigned int currentPositionMs;
    unsigned int trackLengthMs;
    bool isPlaying;
    bool isFinished;
};