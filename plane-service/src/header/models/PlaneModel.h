#pragma once

#include <string>

class PlaneModel
{
private:
    int _id = 0;
    std::string _name;
    std::string _pilot;
    int _builtYear = 0;
    int _brokenPercentage = 0;
    int _speed = 0;
    int _minAirportSize = 0;
public:
    PlaneModel(int id, std::string name, std::string pilot, int builtYear, int brokenPercentage, int speed, int minAirportSize);
    PlaneModel() = default;

    int getId();
    std::string getName();
    std::string getPilot();
    int getBuiltYear();
    int getBrokenPercentage();
    int getSpeed();
    int getMinAirportSize();

    void setId(int id);
    void setName(std::string name);
    void setPilot(std::string pilot);
    void setBuiltYear(int builtYear);
    void setBrokenPercentage(int brokenPercentage);
    void setSpeed(int speed);
    void setMinAirportSize(int minAirportSize);

};

