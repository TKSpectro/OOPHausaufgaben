//
//
//  Generated by StarUML(tm) C++ Add-In
//
//  @ Project : GruppeC
//  @ File Name : RoadNetwork.h
//  @ Date : 15.04.2019
//  @ Author : Kay G�rtzig
//
//
#if !defined(ROADNETWORK_H)
#define ROADNETWORK_H
#define _CRT_SECURE_NO_WARNINGS

#include <map>
#include <string>
using std::map;
using std::multimap;
using std::string;
#include "Drawer2D.h"
#include <iostream>
#include <fstream>
using namespace std;

class Junction;
class Road;

class RoadNetwork {
public:
	// TODO: Destructor should destroy roads and junction
	bool add(Junction& junction);
	void add(Road& road);
	void remove(Road& road);
	void remove(Junction& junction);
	void draw(Drawer2D& drawer) const;
	//the course of the roads has to be set to public else we couldnt access it
	//same goes for the in/outRoad of the Junction
	//both could be accessed trough a getter function which would return them
	bool save(string path);
	bool load(string path);
private:
	// char-Pointer ungeeignet als Suchschl�ssel (Vergleich �ber Adresse!)
	typedef map<string, Junction*> NodeMap;
	typedef multimap<string, Road*> RoadMap;
	NodeMap junctions;
	RoadMap roads;
};

#endif  //ROADNETWORK_H
