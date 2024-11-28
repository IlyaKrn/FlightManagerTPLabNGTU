#pragma once

#include <string>

class TokenRepository {
public:
    std::string getToken();
    long int getUser Id();
    bool setTokenAndUser Id(const std::string& token, long int userId);
};