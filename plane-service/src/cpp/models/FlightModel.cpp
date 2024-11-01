#include "../../header/models/FlightModel.h"

FlightModel::FlightModel(int id, long int timestampstart, long int timestampend, int dispatcherId, int planeId, int airportId)
{
    _id = id;
    _timstampstart = timestampstart;
    _timestampend = timestampend;
    _dispatcherId = dispatcherId;
    _planeId = planeId;
    _airportId = airportId;
}

int FlightModel::getId()
{
    return _id;
}
long int FlightModel::getTimestampStart()
{
    return _timstampstart;
}
long int FlightModel::getTimestampEnd()
{
    return _timestampend;
}
int FlightModel::getDispatcherId()
{
    return _dispatcherId;
}
int FlightModel::getPlaneId()
{
    return _planeId;
}
int FlightModel::getAirportId()
{
    return _airportId;
}

void FlightModel::setId(int id)
{
    _id = id;
}
void FlightModel::setTimestampStart(long int timestampstart)
{
    _timstampstart = timestampstart;
}
void FlightModel::setTimestampEnd(long int timestampend)
{
    _timestampend = timestampend;
}
void FlightModel::setDispatcherId(int dispatcherId)
{
    _dispatcherId = dispatcherId;
}
void FlightModel::setPlaneId(int planeId)
{
    _planeId = planeId;
}
void FlightModel::setAirportId(int airportId)
{
    _airportId = airportId;
}



