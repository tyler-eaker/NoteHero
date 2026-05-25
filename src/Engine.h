#pragma once

#include <memory>
#include "GameState.h"
#include "fmod.hpp"

class Engine {
public:
    Engine();
    ~Engine();

    void Run();
    void ChangeState(std::unique_ptr<GameState> newState);
    void Quit();

private:
    std::unique_ptr<GameState> currentState;
    std::unique_ptr<GameState> nextState;

    FMOD::System* audioSystem;
    bool isRunning;
};