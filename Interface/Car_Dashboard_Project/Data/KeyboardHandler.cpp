#include "KeyboardHandler.hpp"
#include <iostream>
#include <thread>
// #include <termios.h>
#include <unistd.h>
#include <conio.h> // Thay thế cho <termios.h> trong môi trường Windows

// Constructor
KeyboardHandler::KeyboardHandler(DatabaseHandler& db) : dbHandler(db), isRunning(false) {
    keyMapping = {
        {72, SystemAttribute::UP},
        {80, SystemAttribute::DOWN},
        {77, SystemAttribute::RIGHT},
        {'v', SystemAttribute::V},
        {'b', SystemAttribute::B},
        {32, SystemAttribute::SPACE},
        {13, SystemAttribute::ENTER}, // '\n' cho phím Enter trên macOS
        {'n', SystemAttribute::N},
        {'m', SystemAttribute::M}
    };
}

// Destructor
KeyboardHandler::~KeyboardHandler() {
    stop();
}

// Bắt đầu lắng nghe bàn phím
void KeyboardHandler::start() {
    isRunning = true;
    std::thread(&KeyboardHandler::keyboardListener, this).detach();
}

// Dừng lắng nghe bàn phím
void KeyboardHandler::stop() {
    isRunning = false;
}

// Hàm lắng nghe bàn phím
void KeyboardHandler::keyboardListener() {
    while (isRunning){
        if (_kbhit()){          // Kiểm tra nếu có phím nào đó được nhấn    
            char ch = _getch(); // Đọc phím từ bàn phím

            if (ch == 0 || ch == 224){  // Kiểm tra phím đặc biệt (mũi tên)
                ch = getch();   // Đọc thêm một ký tự để xác định phím mũi tên
                if (keyMapping.find(ch) != keyMapping.end()){
                    dbHandler.setData(keyMapping[ch], 1);   // Đặt trạng thái phím nhấn
                }
            } else if (keyMapping.find(ch) != keyMapping.end()){
                dbHandler.setData(keyMapping[ch], 1);   // Đặt trạng thái phím nhấn
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
        for (const auto& pair : keyMapping) {
            dbHandler.setData(pair.second, 0); // Đặt lại trạng thái phím sau mỗi chu kỳ
        }
    }
}
