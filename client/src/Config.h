#pragma once
#include <string>

// gateway connection
const int GATEWAY_PORT = std::stoi(std::string(std::getenv("GATEWAY_PORT")));
const std::string GATEWAY_HOST = "127.0.0.1";
const std::string GATEWAY_URL = std::string(std::getenv("GATEWAY_URL"));
