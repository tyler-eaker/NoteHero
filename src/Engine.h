#pragma once

#include <memory>
#include "GameState.h"
#include "EngineInfo.h"
#include "fmod.hpp"

class Engine {
public:
    Engine();
    ~Engine();

    void Run();
    void ChangeState(std::unique_ptr<GameState> newState);
    void Quit();

    WindowInfo& GetWindowInfo() { return windowInfo; }
    DefaultVideoSettings& GetDefaultVideoSettings() { return defaultVideoSettings; }
    FMOD::System* GetAudioSystem() { return audioSystem; }

private:
    std::unique_ptr<GameState> currentState;
    std::unique_ptr<GameState> nextState;

    WindowInfo windowInfo;
    DefaultVideoSettings defaultVideoSettings;
    FMOD::System* audioSystem;
    bool isRunning;
};