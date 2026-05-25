#include "States.h"
#include "imgui.h"

// --- BootState ---
BootState::BootState(Engine* engineContext) : engine(engineContext) {}
void BootState::Enter() {}
void BootState::Update() {}
void BootState::Draw() {
    ImGui::Begin("Note Hero");
    ImGui::Text("Boot Menu:");
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
    ImGui::Begin("Note Hero");

    switch (currentScreen) {
        case MenuScreen::Main:
            ImGui::Text("Main Menu:");
            if (ImGui::Button("QUICKPLAY")) currentScreen = MenuScreen::SongSelect;
            if (ImGui::Button("VERSUS")) currentScreen = MenuScreen::SongSelect;
            if (ImGui::Button("ONLINE")) currentScreen = MenuScreen::SongSelect;
            if (ImGui::Button("PRACTICE")) currentScreen = MenuScreen::SongSelect;
            if (ImGui::Button("NEWS")) currentScreen = MenuScreen::News;
            if (ImGui::Button("SETTINGS")) currentScreen = MenuScreen::Settings;
            if (ImGui::Button("QUIT")) engine->Quit();
            break;

        case MenuScreen::SongSelect:
            ImGui::Text("Song Select:");
            if (ImGui::Button("SONG 1")) currentScreen = MenuScreen::PreGame;
            if (ImGui::Button("SONG 2")) currentScreen = MenuScreen::PreGame;
            if (ImGui::Button("SONG 3")) currentScreen = MenuScreen::PreGame;
            if (ImGui::Button("GO BACK")) currentScreen = MenuScreen::Main;
            break;

        case MenuScreen::Online:
            ImGui::Text("Online:");
            ImGui::Text("Servers and shit");
            if (ImGui::Button("GO BACK")) currentScreen = MenuScreen::Main;
            break;

        case MenuScreen::News:
            ImGui::Text("News:");
            ImGui::Text("News and shit");
            if (ImGui::Button("GO BACK")) currentScreen = MenuScreen::Main;
            break;

        case MenuScreen::Settings:
            ImGui::Text("Settings:");
            ImGui::Text("Settings and shit");
            if (ImGui::Button("GO BACK")) currentScreen = MenuScreen::Main;
            break;

        case MenuScreen::PreGame:
            ImGui::Text("Pre Game:");
            ImGui::Text("Changing difficulty, instrument, etc.");
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
    ImGui::Begin("Note Hero");
    ImGui::Text("Current State: GAMEPLAY");

    if (ImGui::Button("Exit to Main Menu")) {
        engine->ChangeState(std::make_unique<MenuState>(engine));
    }
    ImGui::End();
}
void GameplayState::Exit() {}

// --- ResultsState ---
ResultsState::ResultsState(Engine* engineContext, int finalScore) : engine(engineContext) {}
void ResultsState::Enter() {}
void ResultsState::Update() {}
void ResultsState::Draw() {
    ImGui::Begin("Note Hero");
    ImGui::Text("Current State: GAMEPLAY");

    if (ImGui::Button("Exit to Main Menu")) {
        engine->ChangeState(std::make_unique<MenuState>(engine));
    }
    ImGui::End();
}
void ResultsState::Exit() {}