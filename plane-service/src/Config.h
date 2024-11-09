#pragma once
#include <string>

const int SERVER_PORT = std::stoi(std::string(std::getenv("PLANE_SERVICE_PORT")));
const std::string SERVER_HOST = "0.0.0.0";
const std::string SERVICE_TOKEN_NAME = std::string(std::getenv("SERVICE_TOKEN_NAME"));
const std::string SERVICE_TOKEN_VALUE = std::string(std::getenv("SERVICE_TOKEN_VALUE"));


// database-service connection
const int DATABASE_SERVICE_PORT = std::stoi(std::string(std::getenv("DATABASE_SERVICE_PORT")));
const std::string DATABASE_SERVICE_HOST = "127.0.0.1";
const std::string DATABASE_SERVICE_URL = std::string(std::getenv("DATABASE_SERVICE_URL"));
const std::string DATABASE_SERVICE_GET_AIRPORTS = "/api/airport/get";


// identity-service connection
const int IDENTITY_SERVICE_PORT = std::stoi(std::string(std::getenv("IDENTITY_SERVICE_PORT")));
const std::string IDENTITY_SERVICE_URL = std::string(std::getenv("IDENTITY_SERVICE_URL"));
const std::string IDENTITY_SERVICE_GET_AIRPORTS = "/api/airport/get";

// mappings
const std::string GET_ID_BY_TOKEN_MAPPING = "/api/auth/getIdByToken";
const std::string AUTHORIZE_MAPPING = "/api/auth/authorize";

const std::string AIRPORT_GET_ALL_MAPPING = "/api/airport/getAll";
const std::string AIRPORT_GET_BY_ID_MAPPING = "/api/airport/get";
const std::string AIRPORT_CREATE_MAPPING = "/api/airport/create";
const std::string AIRPORT_UPDATE_MAPPING = "/api/airport/update";
const std::string AIRPORT_DELETE_MAPPING = "/api/airport/delete";


const std::string PLANE_GET_ALL_MAPPING = "/api/plane/getAll";
const std::string PLANE_GET_BY_ID_MAPPING = "/api/plane/get";
const std::string PLANE_CREATE_MAPPING = "/api/plane/create";
const std::string PLANE_UPDATE_MAPPING = "/api/plane/update";
const std::string PLANE_DELETE_MAPPING = "/api/plane/delete";

const std::string DISPATCHER_GET_ALL_MAPPING = "/api/dispatcher/getAll";
const std::string DISPATCHER_GET_BY_ID_MAPPING = "/api/dispatcher/get";
const std::string DISPATCHER_UPDATE_MAPPING = "/api/dispatcher/update";

const std::string FLIGHT_GET_ALL_MAPPING = "/api/flights/getAll";
const std::string FLIGHT_GET_BY_ID_MAPPING = "/api/flights/get";
const std::string FLIGHT_CREATE_MAPPING = "/api/flights/create";
