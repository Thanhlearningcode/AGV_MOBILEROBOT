#ifndef DATABASE_HANDLER_HPP
#define DATABASE_HANDLER_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <vector>
#include <string>
#include <stdexcept>
#include <variant>
#include "EnumDefinitions.hpp" // Bao gồm file chứa định nghĩa enum và hàm chuyển đổi

using namespace std;

// Đường dẫn cứng tới file CSV
#define DATABASE_PATH ".\\Data\\Database.csv"

// Định nghĩa kiểu dữ liệu có thể chứa nhiều loại giá trị
using DataVariant = std::variant<int, std::string, DriveMode, TurnSignalState, KeyState, GearShift, PedalState>;

/**
 * @class DatabaseHandler
 * @brief Quản lý việc đọc, ghi và thao tác dữ liệu trong file CSV.
 */
class DatabaseHandler
{
private:
    // Bản đồ lưu trữ dữ liệu từ file CSV
    std::unordered_map<std::string, std::string> data;
    // Vector lưu thứ tự của các key để giữ nguyên vị trí khi ghi lại tệp
    std::vector<std::string> keysOrder;

    /**
     * @brief Tải dữ liệu từ file CSV vào bộ nhớ.
     */
    void loadData();

    /**
     * @brief Lưu dữ liệu từ bộ nhớ vào file CSV.
     */
    void saveData() const;

    /**
     * @brief Chuyển đổi giá trị sang chuỗi để ghi vào map.
     * @tparam T Kiểu dữ liệu của giá trị.
     * @param value Giá trị cần chuyển đổi.
     * @return Chuỗi đại diện cho giá trị.
     */
    template <typename T>
    std::string valueToString(T value) const
    {
        if constexpr (std::is_enum_v<T>)
        {
            return enumToString(value);
        }
        else
        {
            return std::to_string(value);
        }
    }

public:
    /**
     * @brief Constructor. Tự động tải dữ liệu từ file CSV khi đối tượng được khởi tạo.
     */
    DatabaseHandler();

    /**
     * @brief Lấy dữ liệu từ enum key và trả về dưới dạng enum.
     * @tparam EnumType Kiểu enum cần trả về.
     * @param key Enum biểu diễn thuộc tính cần lấy dữ liệu.
     * @return EnumType Giá trị trả về dưới dạng enum.
     */
    // template <typename EnumType>
    // EnumType getData(SystemAttribute key) const
    // {
    //     std::string keyStr = enumToString(key);
    //     auto it = data.find(keyStr);
    //     if (it != data.end())
    //     {
    //         return stringToEnum<EnumType>(it->second); // Chuyển chuỗi thành enum
    //     }
    //     throw std::runtime_error("Không tìm thấy key: " + keyStr);
    // }

    template <typename ReturnType>
    ReturnType getData(SystemAttribute key) const
    {
        std::string keyStr = enumToString(key);
        auto it = data.find(keyStr);

        if (it != data.end())
        {
            // std::cout << "Giá trị lấy ra cho key '" << keyStr << "': " << it->second << std::endl; // In ra để gỡ lỗi
            if constexpr (std::is_enum<ReturnType>::value)
            {
                return stringToEnum<ReturnType>(it->second); // Chuyển chuỗi thành enum
            }
            else if constexpr (std::is_same<ReturnType, int>::value)
            {
                return std::stoi(it->second); // Chuyển chuỗi thành int
            }
            else
            {
                throw std::runtime_error("Kiểu dữ liệu không được hỗ trợ.");
            }
        }
        throw std::runtime_error("Không tìm thấy key: " + keyStr);
    }


    /**
     * @brief Lấy dữ liệu từ enum key và trả về dưới dạng chuỗi.
     * @param key Enum biểu diễn thuộc tính cần lấy dữ liệu.
     * @return Chuỗi chứa giá trị tương ứng.
     */
    std::string getDataString(SystemAttribute key) const;

    /**
     * @brief Đặt dữ liệu từ enum key với giá trị chuỗi.
     * @param key Enum biểu diễn thuộc tính cần cập nhật.
     * @param value Chuỗi giá trị mới.
     */
    void setData(SystemAttribute key, const std::string &value);

    /**
     * @brief Đặt dữ liệu từ enum key với giá trị số nguyên.
     * @param key Enum biểu diễn thuộc tính cần cập nhật.
     * @param value Giá trị số nguyên mới.
     */
    void setData(SystemAttribute key, int value);

    /**
     * @brief Đặt dữ liệu từ enum key với giá trị enum khác.
     * @tparam EnumType Kiểu enum của giá trị cần cập nhật.
     * @param key Enum biểu diễn thuộc tính cần cập nhật.
     * @param value Giá trị enum mới.
     */
    template <typename EnumType>
    void setData(SystemAttribute key, EnumType value){
        string keyStr = enumToString(key);
        string valueStr = enumToString(value);

        if (data.find(keyStr) != data.end()) {
            data[keyStr] = valueStr;
            saveData();
        } else {
            cerr << "Key không tồn tại: " << keyStr << std::endl;
        }
    }

    /**
     * @brief Đặt nhiều cặp key-value cùng một lúc với các kiểu giá trị khác nhau.
     *
     * Hàm này cho phép cập nhật nhiều giá trị vào cơ sở dữ liệu từ một vector chứa các cặp key-value.
     * Các giá trị có thể là các kiểu dữ liệu khác nhau như số nguyên, chuỗi, hoặc các kiểu enum khác.
     * Nếu một key tồn tại trong cơ sở dữ liệu, giá trị tương ứng sẽ được cập nhật.
     *
     * @tparam T Kiểu dữ liệu của giá trị (có thể là số nguyên, chuỗi, hoặc enum).
     * @param keyValuePairs Vector chứa các cặp key-value, với mỗi phần tử là một cặp gồm:
     * - `SystemAttribute`: Enum biểu diễn key cần cập nhật.
     * - `DataVariant`: Kiểu `std::variant` chứa giá trị có thể là int, std::string, hoặc các enum.
     */
    void setMultipleData(const std::vector<std::pair<SystemAttribute, DataVariant>> &keyValuePairs);

    /**
     * @brief Hiển thị toàn bộ dữ liệu để kiểm tra và debug.
     */
    void printData() const;
};

#endif // DATABASE_HANDLER_HPP
