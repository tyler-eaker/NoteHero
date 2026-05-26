#include "States.h"
#include "imgui.h"
#include "raylib.h"
#include "AudioClock.h"

// --- BootState ---
// Splash screen. 'PRESS ANY BUTTON' type shit.
// We should probably load everything when going into the menu state to ensure
// the game starts up quickly. User settings should be loaded when booting though.
BootState::BootState(Engine* engineContext) : engine(engineContext) {}
void BootState::Enter() {}
void BootState::Update() {}
void BootState::Draw() {

    DrawText("NOTE HERO", 20, 20, 60, BLUE);
    DrawText("Pre-Alpha Build v0.1", 20, 80, 20, GRAY);
    DrawRectangle(0, 110, 1280, 5, PURPLE);
    DrawText("BOOT MENU", 20, 125, 20, GREEN);

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

    DrawText("NOTE HERO", 20, 20, 60, BLUE);
    DrawText("Pre-Alpha Build v0.1", 20, 80, 20, GRAY);
    DrawRectangle(0, 110, 1280, 5, PURPLE);

    ImGui::Begin("Note Hero");

    switch (currentScreen) {
        case MenuScreen::Main:
            DrawText("MAIN MENU", 20, 125, 20, GREEN);

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
                DrawText("SONG SELECT: QUICKPLAY", 20, 125, 20, GREEN);
            if (chosenGameMode == GameMode::Versus)
                DrawText("SONG SELECT: VERSUS", 20, 125, 20, GREEN);
            if (chosenGameMode == GameMode::Practice)
                DrawText("SONG SELECT: PRACTICE", 20, 125, 20, GREEN);

            if (ImGui::Button("SONG 1", ImVec2(200, 50))) currentScreen = MenuScreen::PreGame;
            if (ImGui::Button("SONG 2", ImVec2(200, 50))) currentScreen = MenuScreen::PreGame;
            if (ImGui::Button("SONG 3", ImVec2(200, 50))) currentScreen = MenuScreen::PreGame;
            if (ImGui::Button("GO BACK", ImVec2(200, 50))) currentScreen = MenuScreen::Main;

            break;

        case MenuScreen::Online:
            DrawText("ONLINE", 20, 125, 20, GREEN);

            ImGui::Text("Servers and shit");
            if (ImGui::Button("GO BACK", ImVec2(200, 50))) currentScreen = MenuScreen::Main;

            break;

        case MenuScreen::News:
            DrawText("NEWS", 20, 125, 20, GREEN);

            ImGui::Text("News and shit");
            if (ImGui::Button("GO BACK", ImVec2(200, 50))) currentScreen = MenuScreen::Main;

            break;

        case MenuScreen::Settings:
            DrawText("SETTINGS", 20, 125, 20, GREEN);

            ImGui::Text("Settings and shit");
            if (ImGui::Button("GO BACK", ImVec2(200, 50))) currentScreen = MenuScreen::Main;

            break;

        case MenuScreen::PreGame:
            DrawText("PRE-GAME", 20, 125, 20, GREEN);

            ImGui::Text("Changing difficulty,");
            ImGui::Text("instrument, etc.");
            if (ImGui::Button("PLAY", ImVec2(200, 50))) engine->ChangeState(std::make_unique<GameplayState>(engine));
            if (ImGui::Button("GO BACK", ImVec2(200, 50))) currentScreen = MenuScreen::SongSelect;

            break;
    }
    
    ImGui::End();
}
void MenuState::Exit() {}


// --- GameplayState ---
GameplayState::GameplayState(Engine* engineContext) : engine(engineContext) {}
void GameplayState::Enter() {
    audioClock = std::make_unique<AudioClock>(engine->GetAudioSystem());
    audioClock->LoadSong("assets/songs/lil-pump-d-rose.wav");
    audioClock->Play();
}
void GameplayState::Update() {
    audioClock->Update();

    if (audioClock->IsFinished()) {
        engine->ChangeState(std::make_unique<ResultsState>(engine, 69420));
    }
}
void GameplayState::Draw() {

    DrawText("NOTE HERO", 20, 20, 60, BLUE);
    DrawText("Pre-Alpha Build v0.1", 20, 80, 20, GRAY);
    DrawRectangle(0, 110, 1280, 5, PURPLE);
    DrawText("GAMEPLAY", 20, 125, 20, GREEN);

    ImGui::Begin("Note Hero");

    ImGui::Text("Song Time: %u ms", audioClock->GetSongPositionMs());
    ImGui::Text("Track Length: %u ms", audioClock->GetTrackLengthMs());
    if (ImGui::Button("FINISH SONG", ImVec2(200, 50))) {
        audioClock->Stop();
        engine->ChangeState(std::make_unique<ResultsState>(engine, 69420));
    }
    if (ImGui::Button("PLAY", ImVec2(200, 50))) {
        audioClock->Play();
    }
    if (ImGui::Button("PAUSE", ImVec2(200, 50))) {
        audioClock->Pause();
    }
    if (ImGui::Button("RESUME", ImVec2(200, 50))) {
        audioClock->Resume();
    }
    if (ImGui::Button("STOP", ImVec2(200, 50))) {
        audioClock->Stop();
    }
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

    DrawText("NOTE HERO", 20, 20, 60, BLUE);
    DrawText("Pre-Alpha Build v0.1", 20, 80, 20, GRAY);
    DrawRectangle(0, 110, 1280, 5, PURPLE);
    DrawText("RESULTS", 20, 125, 20, GREEN);

    ImGui::Begin("Note Hero");

    ImGui::Text("Score: %d", score);
    if (ImGui::Button("MAIN MENU", ImVec2(200, 50))) {
        engine->ChangeState(std::make_unique<MenuState>(engine));
    }
    ImGui::End();
}
void ResultsState::Exit() {}