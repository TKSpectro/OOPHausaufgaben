//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : GruppeC
//  @ File Name : Junction.h
//  @ Date : 15.04.2019
//  @ Author : 
//
//
#if !defined(_JUNCTION_H)
#define _JUNCTION_H

#define _CRT_SECURE_NO_WARNINGS

#include "Point2D.h"
#include <list>
#include <iostream>
#include <fstream>

using std::list;

class Road;
class RoadNetwork;

class Junction {
	//friend Road::Road(Junction&, Junction&);
	friend class Road;
public:
	Junction(const Point2D& position, RoadNetwork& network, const char junctionName[]);
	// ATTENTION: Junctions must not be destroyed while they still hold road references!
	~Junction();
	RoadNetwork* getNetwork() const;
	const char* getName() const;
	Point2D getLocation() const;
	void draw(Drawer2D& drawer) const;
	//outputs the junction into the ofstream
	void save(std::ofstream& outFile);
	Junction* load(std::string line, RoadNetwork* roadn);
private:
	char* name;
	Point2D location;
	list<Road*> outRoads;
	list<Road*> inRoads;
	RoadNetwork *network;
	bool join(Road& road, bool atStart);
	bool disjoin(Road& road, bool atStart);
};

#endif  //_JUNCTION_H
