#include "InputManager.h"
#include "spdlog/spdlog.h"

extern "C" __declspec(dllimport) short __stdcall GetAsyncKeyState(int vKey);

InputManager::InputManager(Engine* engineContext) 
    : engine(engineContext) {
    //if (clock != nullptr) ptrAudioClock = clock;
    inputThread = std::thread(&InputManager::ThreadHandleInputs, this);
}

InputManager::~InputManager() {
    killThread = true;
    inputThread.join();
}

void InputManager::ThreadHandleInputs() {

    bool wasX_PressedLastLoop = false;

    auto start_time = std::chrono::steady_clock::now();
    uint32_t iteration_counter = 0;

    while (killThread == false) {
        // Do Work
        bool isX_Pressed = (GetAsyncKeyState(0x58) & 0x8000) != 0;
        if (isX_Pressed && !wasX_PressedLastLoop) {
            uint32_t exactHitTime = engine->GetAudioClock()->GetSongPositionMs();
            InputEvent event(1, true, exactHitTime);
            spdlog::info("x down added to queue");
            inputQueue.push(event);
        }
        else if (!isX_Pressed && wasX_PressedLastLoop) {
            uint32_t exactReleaseTime = engine->GetAudioClock()->GetSongPositionMs();
            InputEvent event(1, false, exactReleaseTime);
            spdlog::info("x up added to queue");
            inputQueue.push(event);
        }
        wasX_PressedLastLoop = isX_Pressed;

        // Prevent Excessive Processor Use
        std::this_thread::sleep_for(std::chrono::milliseconds(1));

        if (iteration_counter == 1000) {
            iteration_counter = 0;
            auto end_time = std::chrono::steady_clock::now();
            std::chrono::duration<float> elapsed = end_time - start_time;
            start_time = std::chrono::steady_clock::now();

            spdlog::info("InputManager::ThreadHandleInputs delta time: {}", elapsed.count());
        }

        iteration_counter++;
    }
}