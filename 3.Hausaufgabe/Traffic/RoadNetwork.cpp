#include "RoadNetwork.h"
#include "Junction.h"
#include "Road.h"
#include <sstream>
#include <vector>

bool RoadNetwork::add(Junction& junction)
{
	bool done = false;
	if(this->junctions.find(junction.getName()) == this->junctions.end())
	{
		this->junctions.insert(NodeMap::value_type(junction.getName(), &junction));
		//this->junctions[junction.getName()] = &junction; // So ginge es f�r maps auch
		done = true;
	}
	return done;
}

void RoadNetwork::add(Road& road)
{
	this->roads.insert(RoadMap::value_type(road.getName(), &road));
}

void RoadNetwork::remove(Road& road)
{
	// Es k�nnten mehrere Eintr�ge mit dem vorgegebenen Namen sein...
	//std::pair<RoadMap::iterator, RoadMap::iterator> iters = this->roads.equal_range(road.getName());
	auto iters = this->roads.equal_range(road.getName());
	// Wir suchen in dem Bereich gleicher Namen nach dem Eintrag mit der richtigen Stra�e
	for(; iters.first != iters.second; ++iters.first)
	{
		if(iters.first->second == &road)
		{
			// Stra�e gefunden --> l�schen und tsch�ss!
			this->roads.erase(iters.first);
			break;
		}
	}
}

void RoadNetwork::remove(Junction& junction)
{
	auto iter = this->junctions.find(junction.getName());
	if(iter != this->junctions.end())
	{
		this->junctions.erase(iter);
	}
}

void RoadNetwork::draw(Drawer2D& drawer) const
{
	for(RoadMap::value_type entry : this->roads)
	{
		entry.second->draw(drawer);
	}
	for(NodeMap::value_type entry : this->junctions)
	{
		entry.second->draw(drawer);
	}
}

bool RoadNetwork::save(string path)
{
	// open the text file you want to write in
	ofstream outFile(path);
	if(outFile.is_open())
	{
		cout << "outputFile opened" << endl;

		//output all junctions
		for(auto const& element : this->junctions)
		{
			element.second->save(outFile);
		}

		//output all roads
		for(auto const& element : this->roads)
		{
			element.second->save(outFile);
		}

		outFile.close();
		cout << "outputFile closed" << endl;
		return true;
	}
	else
	{
		cout << "Unable to open file" << endl;
		return false;
	}
}

bool RoadNetwork::load(string path)
{
	// open the text file you want to write in
	ifstream inFile(path);
	if(inFile.is_open())
	{
		string line;
		cout << "inputFile opened" << endl;
		cout << "________________" << endl;
		while(getline(inFile, line))
		{
			bool isInRoad = true;
			string delimiter = ";";
			unsigned int pos = 0;
			std::string token = "a";
			std::vector<string> stringVector;

			while(!token.empty())
			{
				pos = line.find(delimiter);
				token = line.substr(0, pos);
				line.erase(0, pos + delimiter.length());
				stringVector.push_back(token);
			}

			if(stringVector[0] == "Junction")
			{
				//create junction
				double x = stod(stringVector[1]);
				double y = stod(stringVector[2]);
				const char* tmpName = stringVector[3].c_str();
				char name[256] = {};
				strcpy(name, tmpName);
				Point2D const* point = new Point2D(x, y);
				Junction* junction = new Junction(*point, *this, name);
				this->add(*junction);
				cout << "Junction:" << name << ";" << x << ";" << y << endl;
			}
			else if(stringVector[0] == "Road")
			{
				//create roads
				//Typ; Name; Junction1Name; Junction2Name; x; y; ...; ...;
				const char* tmpName = stringVector[3].c_str();
				char name[256] = {};
				strcpy(name, tmpName);

				Point2D* point1 = new Point2D(stod(stringVector[4]), stod(stringVector[5]));
				Point2D* point2 = new Point2D(stod(stringVector[6]), stod(stringVector[7]));
				Polyline2D* polyline = new Polyline2D(*point1, *point2);
				for(unsigned int i = 8; i < stringVector.size() - 1; i = i + 2)
				{
					Point2D* pointAdd = new Point2D(stod(stringVector[i]), stod(stringVector[i + 1]));
					polyline->insertPoint(*pointAdd, polyline->getNumberOfPoints());
				}
				//*this->junctions.find(Temp_R.s_name)).second

				bool bStart = false;
				bool bEnd = false;

				if(this->junctions.count(stringVector[1]) > 0)
					bStart = true;
				if(this->junctions.count(stringVector[2]) > 0)
					bEnd = true;
				if(bStart && bEnd)
					Road* road = new Road(*(*this->junctions.find(stringVector[1])).second, *(*this->junctions.find(stringVector[2])).second, *polyline, name);
			}
		}
		inFile.close();
		cout << "----------------" << endl;
		cout << "inputFile closed" << endl;
		return true;
	}
	else
	{
		cout << "Unable to open file" << endl;
		return false;
	}
}

ostream& operator<<(ostream& os, const RoadNetwork& dt)
{
	cout << "<< fertig" << endl;
	return os;
}

istream& operator>>(istream& is, const RoadNetwork& dt)
{
	//�ffnen der Datei aus der gelesen wird
	//Pr�fen ob die Datei ge�ffnet wurde
	//wenn nicht User eingabe des Pfades

	//Erstellen  einer leeren Roadmap
	//Durch komplette Datei laufen und einlesen:
	//Array von Roads/Joints anlegen im Heap


	//Road(Junction& start, Junction& end, const Polyline2D& position, const char roadName[])
	/*
		"Road junctionNameStart junctionNameEnd RoadName
		All Points in order with -> P1x P1y P2x P2y P3x P3y ...."
	*/

	//Junction(const Point2D& position, RoadNetwork& network, const char junctionName[])
	/*
		"Junction PositionX PositionY junctionName"
	*/

	//Polyline erstellen mit den punkten die �bergeben werden
	//Array von Roads und Junctions im Heap erstellen lassen bei
	//mithilfe von zuordnung nullptr bef�llen
	//Roadnetwork::Add nutzen um Road und Junctions hinzuzuf�gen

	cout << ">> fertig" << endl;
	return is;
}
