#include "States.h"
#include "imgui.h"
#include "raylib.h"
#include "spdlog/spdlog.h"
#include "AudioClock.h"
#include "InputManager.h"

// --- BootState ---
BootState::BootState(Engine* engineContext) : engine(engineContext) {}
void BootState::Enter() {}
void BootState::Update() {}
void BootState::Draw() {
    DrawTextEx(engine->GetMainFont(), "NOTE HERO", { 20, 10 }, 70, 2, WHITE);
    DrawTextEx(engine->GetMainFont(), "Pre-Alpha", { 20, 80 }, 20, 2, GRAY);
    DrawRectangle(0, 110, 1280, 2, BLUE);
    DrawTextEx(engine->GetMainFont(), "BOOT MENU", { 20, 125 }, 20, 2, GREEN);

    ImGui::Begin("Note Hero");
    if (ImGui::Button("START", ImVec2(200, 50))) {
        engine->ChangeState(std::make_unique<MenuState>(engine));
    }
    ImGui::End();
}
void BootState::Exit() {}

// --- MenuState ---
MenuState::MenuState(Engine* engineContext) : engine(engineContext) {}
void MenuState::Enter() {}
void MenuState::Update() {}
void MenuState::Draw() {
    DrawTextEx(engine->GetMainFont(), "NOTE HERO", { 20, 10 }, 70, 2, WHITE);
    DrawTextEx(engine->GetMainFont(), "Pre-Alpha", { 20, 80 }, 20, 2, GRAY);
    DrawRectangle(0, 110, 1280, 2, BLUE);

    ImGui::Begin("Note Hero");

    switch (currentScreen) {
    case MenuScreen::Main:
        DrawTextEx(engine->GetMainFont(), "MAIN MENU", { 20, 125 }, 20, 2, GREEN);

        if (ImGui::Button("QUICKPLAY", ImVec2(200, 50))) {
            chosenGameMode = GameMode::Quickplay;
            currentScreen = MenuScreen::SongSelect;
        }
        if (ImGui::Button("VERSUS", ImVec2(200, 50))) {
            chosenGameMode = GameMode::Versus;
            currentScreen = MenuScreen::SongSelect;
        }
        if (ImGui::Button("ONLINE", ImVec2(200, 50))) currentScreen = MenuScreen::Online;
        if (ImGui::Button("PRACTICE", ImVec2(200, 50))) {
            chosenGameMode = GameMode::Practice;
            currentScreen = MenuScreen::SongSelect;
        }
        if (ImGui::Button("NEWS", ImVec2(200, 50))) currentScreen = MenuScreen::News;
        if (ImGui::Button("SETTINGS", ImVec2(200, 50))) currentScreen = MenuScreen::Settings;
        if (ImGui::Button("QUIT", ImVec2(200, 50))) engine->Quit();
        break;

    case MenuScreen::SongSelect:
        if (chosenGameMode == GameMode::Quickplay)
            DrawTextEx(engine->GetMainFont(), "SONG SELECT: QUICKPLAY", { 20, 125 }, 20, 2, GREEN);
        if (chosenGameMode == GameMode::Versus)
            DrawTextEx(engine->GetMainFont(), "SONG SELECT: VERSUS", { 20, 125 }, 20, 2, GREEN);
        if (chosenGameMode == GameMode::Practice)
            DrawTextEx(engine->GetMainFont(), "SONG SELECT: PRACTICE", { 20, 125 }, 20, 2, GREEN);

        if (ImGui::Button("SONG 1", ImVec2(200, 50))) currentScreen = MenuScreen::PreGame;
        if (ImGui::Button("SONG 2", ImVec2(200, 50))) currentScreen = MenuScreen::PreGame;
        if (ImGui::Button("SONG 3", ImVec2(200, 50))) currentScreen = MenuScreen::PreGame;
        if (ImGui::Button("GO BACK", ImVec2(200, 50))) currentScreen = MenuScreen::Main;
        break;

    case MenuScreen::Online:
        DrawTextEx(engine->GetMainFont(), "ONLINE", { 20, 125 }, 20, 2, GREEN);
        ImGui::Text("Servers and shit");
        if (ImGui::Button("GO BACK", ImVec2(200, 50))) currentScreen = MenuScreen::Main;
        break;

    case MenuScreen::News:
        DrawTextEx(engine->GetMainFont(), "NEWS", { 20, 125 }, 20, 2, GREEN);
        ImGui::Text("News and shit");
        if (ImGui::Button("GO BACK", ImVec2(200, 50))) currentScreen = MenuScreen::Main;
        break;

    case MenuScreen::Settings:
        DrawTextEx(engine->GetMainFont(), "SETTINGS", { 20, 125 }, 20, 2, GREEN);
        ImGui::Text("Settings and shit");
        if (ImGui::Button("GO BACK", ImVec2(200, 50))) currentScreen = MenuScreen::Main;
        break;

    case MenuScreen::PreGame:
        DrawTextEx(engine->GetMainFont(), "PRE-GAME", { 20, 125 }, 20, 2, GREEN);
        ImGui::Text("Changing difficulty,");
        ImGui::Text("instrument, etc.");
        if (ImGui::Button("PLAY", ImVec2(200, 50))) engine->ChangeState(std::make_unique<GameplayState>(engine, engine->GetAudioClock()));
        if (ImGui::Button("GO BACK", ImVec2(200, 50))) currentScreen = MenuScreen::SongSelect;
        break;
    }
    ImGui::End();
}
void MenuState::Exit() {}

// --- GameplayState ---
GameplayState::GameplayState(Engine* engineContext, AudioClock* ptrAudioClock)
    : engine(engineContext), audioClock(ptrAudioClock) {}

void GameplayState::Enter() {
    
    audioClock->LoadSong("assets/songs/lil-pump-d-rose.wav");
    audioClock->Play();
}
void GameplayState::Update() {
    audioClock->Update();
    std::vector<InputEvent> frameInputs = engine->GetInputManager()->PopAllEvents();

    for (const auto& event : frameInputs) {
        std::string logLine = std::format("Btn: {} | State: {} | Time: {}ms",
            event.buttonID,
            (event.isPressed ? "DOWN" : "UP  "),
            event.timestamp);

        inputHistory.push_back(logLine);

        if (inputHistory.size() > 15) {
            inputHistory.erase(inputHistory.begin());
        }
    }
}
void GameplayState::Draw() {
    DrawTextEx(engine->GetMainFont(), "NOTE HERO", { 20, 10 }, 70, 2, WHITE);
    DrawTextEx(engine->GetMainFont(), "Pre-Alpha", { 20, 80 }, 20, 2, GRAY);
    DrawRectangle(0, 110, 1280, 2, BLUE);
    DrawTextEx(engine->GetMainFont(), "GAMEPLAY", { 20, 125 }, 20, 2, GREEN);

    ImGui::Begin("Note Hero");
    ImGui::Text("Song Time: %u ms", audioClock->GetSongPositionMs());
    ImGui::Text("Track Length: %u ms", audioClock->GetTrackLengthMs());
    ImGui::Text("Live Key State:");
    ImGui::Separator();
    ImGui::Text("Ring Buffer History:");
    for (const auto& log : inputHistory) {
        ImGui::Text("%s", log.c_str());
    }
    if (IsKeyDown(KEY_X)) ImGui::Button(" X ", ImVec2(50, 50));
    if (ImGui::Button("FINISH SONG", ImVec2(200, 50))) {
        audioClock->Stop();
        engine->ChangeState(std::make_unique<ResultsState>(engine, 69420));
    }
    if (ImGui::Button("PLAY", ImVec2(200, 50))) audioClock->Play();
    if (ImGui::Button("PAUSE", ImVec2(200, 50))) audioClock->Pause();
    if (ImGui::Button("RESUME", ImVec2(200, 50))) audioClock->Resume();
    if (ImGui::Button("STOP", ImVec2(200, 50))) audioClock->Stop();
    if (ImGui::Button("QUIT", ImVec2(200, 50))) {
        engine->ChangeState(std::make_unique<MenuState>(engine));
    }
    ImGui::End();
}
void GameplayState::Exit() {}

// --- ResultsState ---
ResultsState::ResultsState(Engine* engineContext, int finalScore) : engine(engineContext), score(finalScore) {}
void ResultsState::Enter() {}
void ResultsState::Update() {}
void ResultsState::Draw() {
    DrawTextEx(engine->GetMainFont(), "NOTE HERO", { 20, 10 }, 70, 2, WHITE);
    DrawTextEx(engine->GetMainFont(), "Pre-Alpha", { 20, 80 }, 20, 2, GRAY);
    DrawRectangle(0, 110, 1280, 2, BLUE);
    DrawTextEx(engine->GetMainFont(), "RESULTS", { 20, 125 }, 20, 2, GREEN);

    ImGui::Begin("Note Hero");
    ImGui::Text("Score: %d", score);
    if (ImGui::Button("MAIN MENU", ImVec2(200, 50))) {
        engine->ChangeState(std::make_unique<MenuState>(engine));
    }
    ImGui::End();
}
void ResultsState::Exit() {}