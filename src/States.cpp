#include "States.h"
#include "imgui.h"
#include "raylib.h"

// --- BootState ---
BootState::BootState(Engine* engineContext) : engine(engineContext) {}
void BootState::Enter() {}
void BootState::Update() {}
void BootState::Draw() {

    DrawText("NOTE HERO", 20, 20, 60, BLUE);
    DrawText("Pre-Alpha Build v0.1", 20, 80, 20, GRAY);
    DrawRectangle(0, 110, 1280, 5, PURPLE);
    DrawText("BOOT MENU", 20, 125, 20, GREEN);

    ImGui::Begin("Note Hero");

    ImGui::Text("Splash screen. 'PRESS ANY BUTTON' type shit.");
    ImGui::Text("We should probably load everything when going into the menu state to ensure");
    ImGui::Text("the game starts up quickly. User settings should be loaded when booting though.");
    if (ImGui::Button("START")) {
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

            if (ImGui::Button("QUICKPLAY")) {
                chosenGameMode = GameMode::Quickplay;
                currentScreen = MenuScreen::SongSelect;
            }
            if (ImGui::Button("VERSUS")) {
                chosenGameMode = GameMode::Versus;
                currentScreen = MenuScreen::SongSelect;
            }
            if (ImGui::Button("ONLINE")) currentScreen = MenuScreen::Online;
            if (ImGui::Button("PRACTICE")) {
                chosenGameMode = GameMode::Practice;
                currentScreen = MenuScreen::SongSelect;
            }
            if (ImGui::Button("NEWS")) currentScreen = MenuScreen::News;
            if (ImGui::Button("SETTINGS")) currentScreen = MenuScreen::Settings;
            if (ImGui::Button("QUIT")) engine->Quit();

            break;

        case MenuScreen::SongSelect:
            if (chosenGameMode == GameMode::Quickplay)
                DrawText("SONG SELECT: QUICKPLAY", 20, 125, 20, GREEN);
            if (chosenGameMode == GameMode::Versus)
                DrawText("SONG SELECT: VERSUS", 20, 125, 20, GREEN);
            if (chosenGameMode == GameMode::Practice)
                DrawText("SONG SELECT: PRACTICE", 20, 125, 20, GREEN);

            if (ImGui::Button("SONG 1")) currentScreen = MenuScreen::PreGame;
            if (ImGui::Button("SONG 2")) currentScreen = MenuScreen::PreGame;
            if (ImGui::Button("SONG 3")) currentScreen = MenuScreen::PreGame;
            if (ImGui::Button("GO BACK")) currentScreen = MenuScreen::Main;

            break;

        case MenuScreen::Online:
            DrawText("ONLINE", 20, 125, 20, GREEN);

            ImGui::Text("Servers and shit");
            if (ImGui::Button("GO BACK")) currentScreen = MenuScreen::Main;

            break;

        case MenuScreen::News:
            DrawText("NEWS", 20, 125, 20, GREEN);

            ImGui::Text("News and shit");
            if (ImGui::Button("GO BACK")) currentScreen = MenuScreen::Main;

            break;

        case MenuScreen::Settings:
            DrawText("SETTINGS", 20, 125, 20, GREEN);

            ImGui::Text("Settings and shit");
            if (ImGui::Button("GO BACK")) currentScreen = MenuScreen::Main;

            break;

        case MenuScreen::PreGame:
            DrawText("PRE-GAME", 20, 125, 20, GREEN);

            ImGui::Text("Changing difficulty, instrument, etc.");
            if (ImGui::Button("PLAY")) engine->ChangeState(std::make_unique<GameplayState>(engine));
            if (ImGui::Button("GO BACK")) currentScreen = MenuScreen::SongSelect;

            break;
    }
    
    ImGui::End();
}
void MenuState::Exit() {}


// --- GameplayState ---
GameplayState::GameplayState(Engine* engineContext) : engine(engineContext) {}
void GameplayState::Enter() {}
void GameplayState::Update() {}
void GameplayState::Draw() {

    DrawText("NOTE HERO", 20, 20, 60, BLUE);
    DrawText("Pre-Alpha Build v0.1", 20, 80, 20, GRAY);
    DrawRectangle(0, 110, 1280, 5, PURPLE);
    DrawText("GAMEPLAY", 20, 125, 20, GREEN);

    ImGui::Begin("Note Hero");

    if (ImGui::Button("FINISH SONG")) {
        engine->ChangeState(std::make_unique<ResultsState>(engine, 69420));
    }
    if (ImGui::Button("QUIT")) {
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
    if (ImGui::Button("MAIN MENU")) {
        engine->ChangeState(std::make_unique<MenuState>(engine));
    }
    ImGui::End();
}
void ResultsState::Exit() {}