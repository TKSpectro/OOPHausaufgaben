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
		//this->junctions[junction.getName()] = &junction; // So ginge es für maps auch
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
	// Es könnten mehrere Einträge mit dem vorgegebenen Namen sein...
	//std::pair<RoadMap::iterator, RoadMap::iterator> iters = this->roads.equal_range(road.getName());
	auto iters = this->roads.equal_range(road.getName());
	// Wir suchen in dem Bereich gleicher Namen nach dem Eintrag mit der richtigen Straße
	for(; iters.first != iters.second; ++iters.first)
	{
		if(iters.first->second == &road)
		{
			// Straße gefunden --> löschen und tschüss!
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
	//öffnen der Datei an dem übergebenen Pfad in einem Filestream
	ofstream outFile(path);
	//nur durchführen wenn der Stream wirklich geöffnet wurde
	if(outFile.is_open())
	{
		cout << "outputFile opened" << endl;

		//schreiben aller Junctions in die Datei
		for(auto const& element : this->junctions)
		{
			element.second->save(outFile);
		}

		//schreiben aller Roads in die Datei
		for(auto const& element : this->roads)
		{
			element.second->save(outFile);
		}

		//schließen der Datei
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
		while(getline(inFile, line))
		{
			string delimiter = ";";
			unsigned int pos = 0;
			string token = "a";
			vector<string> stringVector;

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

				Point2D* startPoint = new Point2D(this->junctions[stringVector[1]]->getLocation());
				Point2D* endPoint = new Point2D(this->junctions[stringVector[2]]->getLocation());
				Polyline2D* polyline = new Polyline2D(*startPoint, *endPoint);
				for(unsigned int i = 4; i < stringVector.size() - 1; i = i + 2)
				{
					Point2D* pointAdd = new Point2D(stod(stringVector[i]), stod(stringVector[i + 1]));
					polyline->insertPoint(*pointAdd, polyline->getNumberOfPoints());
				}

				if(this->junctions.count(stringVector[1]) > 0 && this->junctions.count(stringVector[2]) > 0)
					Road* road = new Road(*this->junctions[stringVector[1]], *this->junctions[stringVector[2]], *polyline, name);
			}
		}
		inFile.close();
		cout << "inputFile closed" << endl;
		return true;
	}
	else
	{
		cout << "Unable to open file" << endl;
		return false;
	}
}
