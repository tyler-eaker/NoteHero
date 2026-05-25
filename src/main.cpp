#include "raylib.h"
#include "fmod.hpp"
#include "imgui.h"
#include "rlImGui.h"
#include "MidiFile.h"
#include "spdlog/spdlog.h"

int main() 
{
    SetTraceLogLevel(LOG_NONE);

    spdlog::info("Booting Note Hero...");

    InitWindow(800, 600, "Note Hero");
    SetTargetFPS(60);
    spdlog::info("Raylib Window Initialized.");

    FMOD::System* audioSystem = nullptr;
    FMOD_RESULT result = FMOD::System_Create(&audioSystem);

    if (result == FMOD_OK) {
        audioSystem->init(512, FMOD_INIT_NORMAL, nullptr);
        spdlog::info("FMOD Audio System Initialized successfully.");
    }
    else {
        spdlog::error("FMOD failed to initialize!");
    }

    smf::MidiFile midifile;

    rlImGuiSetup(true);
    spdlog::info("ImGui Context Setup Complete. Entering main loop.");

    while (!WindowShouldClose()) {
        audioSystem->update();

        BeginDrawing();
        ClearBackground(BLACK);

        rlImGuiBegin();

        ImGui::Begin("Engine Debug");
        ImGui::Text("FMOD initialized successfully.");
        ImGui::Text("Current FPS: %i", GetFPS());
        ImGui::End();

        rlImGuiEnd();

        EndDrawing();
    }

    spdlog::info("Shutting down engine...");

    rlImGuiShutdown();
    audioSystem->release();
    CloseWindow();

    return 0;
}