#pragma once
#include <string>

const int SERVER_PORT = std::stoi(std::string(std::getenv("PLANE_SERVICE_PORT")));
const std::string SERVER_HOST = "0.0.0.0";
const std::string SERVICE_TOKEN_NAME = std::string(std::getenv("SERVICE_TOKEN_NAME"));
const std::string SERVICE_TOKEN_VALUE = std::string(std::getenv("SERVICE_TOKEN_VALUE"));


// database-service connection
const int DATABASE_SERVICE_PORT = std::stoi(std::string(std::getenv("DATABASE_SERVICE_PORT")));
const std::string DATABASE_SERVICE_URL = std::string(std::getenv("DATABASE_SERVICE_URL"));
const std::string DATABASE_SERVICE_GET_AIRPORTS = "/api/airport/get";


// identity-service connection
const int IDENTITY_SERVICE_PORT = std::stoi(std::string(std::getenv("IDENTITY_SERVICE_PORT")));
const std::string IDENTITY_SERVICE_URL = std::string(std::getenv("IDENTITY_SERVICE_URL"));
const std::string IDENTITY_SERVICE_GET_AIRPORTS = "/api/airport/get";

// mappings
const std::string SAMPLE_MAPPING = "/api/sample/mapping";
