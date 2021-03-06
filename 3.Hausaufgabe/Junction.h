//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : GruppeC
//  @ File Name : Junction.h
//  @ Date : 29.04.2019
//  @ Author : 
//
//


#if !defined(_JUNCTION_H)
#define _JUNCTION_H

#include "RoadNetwork.h"
#include "Road.h"

class Junction
{
public:
	void Junction(Point2D position, RoadNetwork network);
	bool join(Road road, bool atStart);
private:
	Road *outRoads;
	Road *inRoads;
	RoadNetwork *network;
};

#endif  //_JUNCTION_H
