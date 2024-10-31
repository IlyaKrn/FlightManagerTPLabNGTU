#pragma once
#include <string>

constexpr int SERVER_PORT = 8083;
const std::string SERVER_HOST = "0.0.0.0";
const std::string SERVICE_TOKEN_NAME = "Service-Token";
const std::string SERVICE_TOKEN_VALUE = "123";


constexpr int DATABASE_SERVICE_PORT = 8081;
const std::string DATABASE_SERVICE_HOST = "127.0.0.1";
const std::string DATABASE_SERVICE_GET_AIRPORTS = "/api/airport/get";

//TODO("replace to here mappings and other const values")
const std::string SAMPLE_MAPPING = "/api/sample/mapping";
