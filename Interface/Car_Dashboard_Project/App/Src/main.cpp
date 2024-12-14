#include "DatabaseHandler.hpp"
#include "KeyboardHandler.hpp"
#include <iostream>
#include <thread>

using namespace std;

int main() {
    DatabaseHandler dbHandler;
    KeyboardHandler keyboardHandler(dbHandler);

    dbHandler.setData(SystemAttribute::WIND_LEVEL, 4);
    cout << "Battery Level: " << dbHandler.getData<int>(SystemAttribute::BATTERY_LEVEL) << endl;

    dbHandler.setData(SystemAttribute::BRAKE, PedalState::RELEASED);

    dbHandler.setMultipleData({
        {SystemAttribute::VEHICLE_SPEED, 100},
        {SystemAttribute::DRIVE_MODE, DriveMode::ECO},
        {SystemAttribute::BATTERY_LEVEL, 90}
    });

    if (PedalState::RELEASED == dbHandler.getData<PedalState>(SystemAttribute::BRAKE)){
        cout << "True";
    } else {
        cout << "False";
    }

    // Khởi chạy listener để bắt đầu ghi nhận sự kiện bàn phím
    keyboardHandler.start();

    bool isKeyPressed = false; // Biến để theo dõi thay đổi

    // Vòng lặp để in ra phím đang nhấn
    while (1) {
        if (dbHandler.getDataString(SystemAttribute::UP) == "1"){
            std::cout << "UP key is pressed" << std::endl;
            isKeyPressed = true;
        } else if (dbHandler.getDataString(SystemAttribute::DOWN) == "1"){
            std::cout << "DOWN key is pressed" << std::endl;
            isKeyPressed = true;
        } else if (dbHandler.getDataString(SystemAttribute::RIGHT) == "1"){
            std::cout << "RIGHT key is pressed" << std::endl;
            isKeyPressed = true;
        } else if (dbHandler.getDataString(SystemAttribute::V) == "1"){
            std::cout << "V key is pressed" << std::endl;
            isKeyPressed = true;
        } else if (dbHandler.getDataString(SystemAttribute::B) == "1"){
            std::cout << "B key is pressed" << std::endl;
            isKeyPressed = true;
        } else if (dbHandler.getDataString(SystemAttribute::N) == "1"){
            std::cout << "N key is pressed" << std::endl;
            isKeyPressed = true;
        } else if (dbHandler.getDataString(SystemAttribute::M) == "1"){
            std::cout << "M key is pressed" << std::endl;
            isKeyPressed = true;
        } else if (dbHandler.getDataString(SystemAttribute::SPACE) == "1"){
            std::cout << "SPACE key is pressed" << std::endl;
            isKeyPressed = true;
        } else if (dbHandler.getDataString(SystemAttribute::ENTER) == "1"){
            std::cout << "ENTER key is pressed" << std::endl;
            isKeyPressed = true;
        }

        // Chỉ xóa và in lại màn hình khi có phím nhấn mới
        if (isKeyPressed) {
            isKeyPressed = false;
            std::this_thread::sleep_for(std::chrono::milliseconds(200));
            // system("cls"); // Dùng "cls" cho Windows; nếu trên Linux thì dùng "clear"
        }
    }

    // Dừng listener (không bao giờ được gọi vì vòng lặp là vô hạn, chỉ có tác dụng khi bạn thêm logic thoát)
    keyboardHandler.stop();



    return 0;
}
