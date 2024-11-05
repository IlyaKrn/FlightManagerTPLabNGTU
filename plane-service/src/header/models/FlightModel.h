#pragma once

#include <string>

class FlightModel
{
private:
    int _id;
    long int _timstampstart;
    long int _timestampend;
    int _dispatcherId;
    int _planeId;
    int _airportId;
public:
    FlightModel(int id, long int timestampstart, long int timestampend, int dispatcherId, int planeId, int airportId);

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