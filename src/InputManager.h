#pragma once

#include <vector>
#include <chrono>
#include <thread>
#include <atomic>

class Engine;

struct InputEvent {
    int buttonID;
    bool isPressed;
    uint32_t timestamp;
};

constexpr size_t INPUT_BUFFER_SIZE = 1024;

class InputManager {
public:
    InputManager(Engine* engineContext);
    ~InputManager();

    void StartThread();
    
    std::vector<InputEvent> PopAllEvents();

private:
    Engine* engine;
    std::atomic<bool> killThread{ false };
    std::thread inputThread;

    InputEvent ringBuffer[INPUT_BUFFER_SIZE];

    std::atomic<size_t> head { 0 };
    std::atomic<size_t> tail{ 0 };

    void ThreadHandleInputs();
};