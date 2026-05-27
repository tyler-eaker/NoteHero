#pragma once

#include <memory>
#include "AudioClock.h"
#include "GameState.h"
#include "EngineInfo.h"
#include "fmod.hpp"
#include "raylib.h"

class InputManager;

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
    std::shared_ptr<AudioClock> GetAudioClock() { return audioClock; }
    InputManager* GetInputManager() { return inputManager.get(); }

    Font GetMainFont() const { return mainFont; }

private:
    std::unique_ptr<GameState> currentState;
    std::unique_ptr<GameState> nextState;

    WindowInfo windowInfo;
    DefaultVideoSettings defaultVideoSettings;
    FMOD::System* audioSystem;
    std::shared_ptr<AudioClock> audioClock;
    std::unique_ptr<InputManager> inputManager;
    
    bool isRunning;

    Font mainFont;
};