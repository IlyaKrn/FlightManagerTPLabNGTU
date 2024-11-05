#pragma once
#include <string>

constexpr int SERVER_PORT = 8083;
const std::string SERVER_HOST = "0.0.0.0";
const std::string SERVICE_TOKEN_NAME = "Service-Token";
const std::string SERVICE_TOKEN_VALUE = "123";


constexpr int DATABASE_SERVICE_PORT = 8081;
const std::string DATABASE_SERVICE_HOST = "127.0.0.1";
const std::string DATABASE_SERVICE_GET_AIRPORTS = "/api/airport/get";


const std::string AIRPORT_GET_MAPPING = "/api/airport/get";
const std::string AIRPORT_CREATE_MAPPING = "/api/airport/create";
const std::string AIRPORT_UPDATE_MAPPING = "/api/airport/update";
const std::string AIRPORT_DELETE_MAPPING = "/api/airport/delete";

const std::string PLANE_GET_MAPPING = "/api/plane/get";
const std::string PLANE_CREATE_MAPPING = "/api/plane/create";
const std::string PLANE_UPDATE_MAPPING = "/api/plane/update";
const std::string PLANE_DELETE_MAPPING = "/api/plane/delete";

const std::string DISPATCHER_GET_MAPPING = "/api/dispatcher/get";
const std::string DISPATCHER_UPDATE_MAPPING = "/api/dispatcher/update";

const std::string FLIGHT_GET_MAPPING = "/api/flight/get";
const std::string FLIGHT_CREATE_MAPPING = "/api/flight/create";
const std::string FLIGHT_UPDATE_MAPPING = "/api/flight/update";