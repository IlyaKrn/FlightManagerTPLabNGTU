#pragma once

#include <string>

class FlightModel
{
private:
    long int _id = 0;
    long int _timstampstart = 0;
    long int _timestampend = 0;
    long int _dispatcherId = 0;
    long int _planeId = 0;
    long int _airportId = 0;
public:
    FlightModel(long int id, long int timestampstart, long int timestampend, long int dispatcherId, long int planeId, long int airportId);
    FlightModel() = default;

    long int getId();
    long int getTimestampStart();
    long int getTimestampEnd();
    long int getDispatcherId();
    long int getPlaneId();
    long int getAirportId();

    void setId(long int id);
    void setTimestampStart(long int timestampstart);
    void setTimestampEnd(long int timestampend);
    void setDispatcherId(long int dispatcherId);
    void setPlaneId(long int planeId);
    void setAirportId(long int airportId);

};