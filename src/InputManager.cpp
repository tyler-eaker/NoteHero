#include "InputManager.h"
#include "Engine.h"

extern "C" __declspec(dllimport) short __stdcall GetAsyncKeyState(int vKey);

InputManager::InputManager(Engine* engineContext) : engine(engineContext) {
}

InputManager::~InputManager() {
    killThread = true;
    if (inputThread.joinable()) {
        inputThread.join();
    }
}

void InputManager::StartThread() {
    inputThread = std::thread(&InputManager::ThreadHandleInputs, this);
}

void InputManager::ThreadHandleInputs() {
    bool wasX_PressedLastLoop = false;

    while (killThread == false) {
        bool isX_Pressed = (GetAsyncKeyState(0x58) & 0x8000) != 0;

        // Key Pressed
        if (isX_Pressed && !wasX_PressedLastLoop) {
            uint32_t exactHitTime = engine->GetAudioClock()->GetSongPositionMs();

            size_t currentHead = head.load();
            size_t nextHead = (currentHead + 1) % INPUT_BUFFER_SIZE;

            if (nextHead != tail.load()) {
                ringBuffer[currentHead] = { 1, true, exactHitTime };
                head.store(nextHead);
            }
        }

        // Key Released
        else if (!isX_Pressed && wasX_PressedLastLoop) {
            uint32_t exactReleaseTime = engine->GetAudioClock()->GetSongPositionMs();

            size_t currentHead = head.load();
            size_t nextHead = (currentHead + 1) % INPUT_BUFFER_SIZE;

            if (nextHead != tail.load()) {
                ringBuffer[currentHead] = { 1, false, exactReleaseTime };
                head.store(nextHead);
            }
        }

        wasX_PressedLastLoop = isX_Pressed;
        std::this_thread::sleep_for(std::chrono::microseconds(1));
    }
}

std::vector<InputEvent> InputManager::PopAllEvents() {
    std::vector<InputEvent> frameInputs;

    size_t currentTail = tail.load();
    size_t currentHead = head.load();

    while (currentTail != currentHead) {
        frameInputs.push_back(ringBuffer[currentTail]);
        currentTail = (currentTail + 1) % INPUT_BUFFER_SIZE;
    }

    tail.store(currentTail);

    return frameInputs;
}