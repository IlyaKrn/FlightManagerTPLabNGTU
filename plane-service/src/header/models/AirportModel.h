#pragma once

#include <string>

class AirportModel
{
private:
    int _id;
    std::string _name;
    int _size;
    double _x;
    double _y;
public:
    AirportModel(int id, std::string name, int size, double x, double y);

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
