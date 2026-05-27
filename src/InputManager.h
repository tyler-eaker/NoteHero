#pragma once

#include <chrono>
#include <tuple>
#include <queue>
#include <thread>
#include <set>
#include "Engine.h"
// Fix a compile collision between raylib and windows
//#define CloseWindow RlCloseWindow
//#define ShowCursor RlShowCursor
//#include <windows.h>

struct InputEvent {
    int buttonID;
    bool isPressed;
    uint32_t timestamp;
};

class InputManager {
public:
    InputManager(Engine* engineContext);
    ~InputManager();

    //void StartThread();
    

private:
    Engine* engine;
    //std::shared_ptr<AudioClock> audioClock;
    bool killThread { false };  
    std::thread inputThread;
    std::queue<InputEvent> inputQueue;

    void ThreadHandleInputs();
};