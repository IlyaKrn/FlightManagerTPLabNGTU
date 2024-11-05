#pragma once

#include <string>

class FlightModel
{
private:
    int _id = 0;
    long int _timstampstart = 0;
    long int _timestampend = 0;
    int _dispatcherId = 0;
    int _planeId = 0;
    int _airportId = 0;
public:
    FlightModel(int id, long int timestampstart, long int timestampend, int dispatcherId, int planeId, int airportId);
    FlightModel() = default;

    int getId();
    long int getTimestampStart();
    long int getTimestampEnd();
    int getDispatcherId();
    int getPlaneId();
    int getAirportId();

    void setId(int id);
    void setTimestampStart(long int timestampstart);
    void setTimestampEnd(long int timestampend);
    void setDispatcherId(int dispatcherId);
    void setPlaneId(int planeId);
    void setAirportId(int airportId);

};