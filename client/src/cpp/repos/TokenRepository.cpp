#include <fstream>
#include "../../header/repos/TokenRepository.h"
#include "../../Config.h"

using namespace std;

std::string TokenRepository::getToken() {
    ifstream file(TOKEN_FILE_PATH);
    string token;
    if (getline(file, token)) {
        return token; // Возвращаем токен
    }
    return ""; // Если токен не найден, возвращаем пустую строку
}

long int TokenRepository::getUserId() {
    ifstream file(TOKEN_FILE_PATH);
    string line;
    long int userId = 0;

    // Считываем токен и ID пользователя
    if (getline(file, line) && getline(file, line)) {
        userId = stol(line); // Преобразуем ID пользователя в long int
    }
    return userId; // Возвращаем ID пользователя
}

bool TokenRepository::setTokenAndUserId(const std::string& token, long int userId) {
    ofstream file(TOKEN_FILE_PATH, ios::trunc); // Открываем файл для записи, очищая его
    if (file.is_open()) {
        file << token << endl; // Записываем токен
        file << userId << endl; // Записываем ID пользователя
        return true; // Успешно записано
    }
    return false; // Ошибка при открытии файла
}