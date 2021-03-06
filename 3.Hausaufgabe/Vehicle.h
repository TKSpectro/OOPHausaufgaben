//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : GruppeC
//  @ File Name : Vehicle.h
//  @ Date : 15.04.2019
//  @ Author : 
//
//


#if !defined(_VEHICLE_H)
#define _VEHICLE_H

#include "Road.h"

class Vehicle {
public:
    double getPosition();
    double getSpeed();
    void setSpeed(double newSpeed);
    bool setRoad(Road road);
private:
    double startPosition;
    time_t startTime;
    double speed;
    Road *road;
};

#endif  //_VEHICLE_H
