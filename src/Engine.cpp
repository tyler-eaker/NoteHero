#include "Engine.h"
#include "States.h"
#include "raylib.h"
#include "rlImGui.h"
#include "spdlog/spdlog.h"

Engine::Engine() : isRunning(true), audioSystem(nullptr) 
{
    SetTraceLogLevel(LOG_NONE);
    spdlog::info("Booting Note Hero...");

    InitWindow(GetDefaultVideoSettings().windowWidth, GetDefaultVideoSettings().windowHeight, GetWindowInfo().title);
    SetTargetFPS(GetDefaultVideoSettings().targetFPS);

    FMOD_RESULT result = FMOD::System_Create(&audioSystem);
    if (result == FMOD_OK) {
        audioSystem->init(512, FMOD_INIT_NORMAL, nullptr);
    }
    else {
        spdlog::error("FMOD failed to initialize!");
    }

    rlImGuiSetup(true);

    ChangeState(std::make_unique<BootState>(this));
}

Engine::~Engine() 
{
    rlImGuiShutdown();

    if (audioSystem) {
        audioSystem->release();
    }

    CloseWindow();
    spdlog::info("Note Hero shut down safely.");
}

void Engine::ChangeState(std::unique_ptr<GameState> newState) {
    nextState = std::move(newState);
}

void Engine::Quit() {
    isRunning = false;
}

void Engine::Run() {
    while (isRunning && !WindowShouldClose()) {

        if (nextState) {
            if (currentState) {
                currentState->Exit();
            }
            currentState = std::move(nextState);
            currentState->Enter();
        }

        if (audioSystem) {
            audioSystem->update();
        }

        if (currentState) {
            currentState->Update();
        }

        BeginDrawing();
        ClearBackground(BLACK);
        rlImGuiBegin();

        if (currentState) {
            currentState->Draw();
        }

        rlImGuiEnd();
        EndDrawing();
    }

    if (currentState) {
        currentState->Exit();
    }
}