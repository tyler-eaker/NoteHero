#pragma once

#include "GameState.h"
#include "Engine.h"
#include "AudioClock.h"

#include <optional>

class Engine;
class AudioClock;

class BootState : public GameState 
{
public:
    BootState(Engine* engineContext);

    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;

private:
    Engine* engine;
};

enum class MenuScreen {
    Main,
    SongSelect,
    Online,
    News,
    Settings,
    PreGame
};

enum class GameMode { 
    Quickplay,
    Versus, 
    Online, 
    Practice 
};

class MenuState : public GameState 
{
public:
    MenuState(Engine* engineContext);

    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;

private:
    Engine* engine;

    MenuScreen currentScreen = MenuScreen::Main;
    std::optional<GameMode> chosenGameMode = std::nullopt;
};

class GameplayState : public GameState 
{
public:
    GameplayState(Engine* engineContext);

    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;

private:
    Engine* engine;

    std::unique_ptr<AudioClock> audioClock;
};

class ResultsState : public GameState 
{
public:
    ResultsState(Engine* engineContext, int finalScore);

    void Enter() override;
    void Update() override;
    void Draw() override;
    void Exit() override;

private:
    Engine* engine;

    int score = 0;
};