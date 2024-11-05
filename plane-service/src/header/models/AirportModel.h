#pragma once

#include <string>

class AirportModel
{
private:
    int _id = 0;
    std::string _name;
    int _size = 0;
    double _x = 0;
    double _y = 0;
public:
    AirportModel(int id, std::string name, int size, double x, double y);
    AirportModel() = default;

    int getId();
    std::string getName();
    int getSize();
    double getX();
    double getY();

    void setId(int id);
    void setName(std::string name);
    void setSize(int size);
    void setX(double x);
    void setY(double y);

};
