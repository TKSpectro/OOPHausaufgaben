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

		//für Vehicles müsste man z.B. den Namen und die Geschwindigkeit speichern
		//Position ist mit der momentan Implementierung von Vehicle zu vernachlässigen,
		//da man die Position nicht setzen könnte

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
	//öffnen der Datei in die geschrieben wird
	ifstream inFile(path);
	//nur duchführen wenn der Stream wirklich geöffnet wurde
	if(inFile.is_open())
	{
		cout << "inputFile opened" << endl;
		string line;
		//solange die Zeilen durchgehen, bis keine mehr gefunden wird
		while(getline(inFile, line))
		{
			string delimiter = ";";
			unsigned int pos = 0;
			string token = "a";
			vector<string> stringVector;

			//alle Wörter dieser Zeile in einen Vector pushen
			while(!token.empty())
			{
				pos = line.find(delimiter);
				token = line.substr(0, pos);
				line.erase(0, pos + delimiter.length());
				stringVector.push_back(token);
			}

			//wenn das erste Wort = Junction
			if(stringVector[0] == "Junction")
			{
				//x, y und den Namen einlesen und die Junction erstellen und in das RoadNetwork hinzufügen
				double x = stod(stringVector[1]);
				double y = stod(stringVector[2]);
				const char* tmpName = stringVector[3].c_str();
				char name[256] = {};
				strcpy(name, tmpName);
				Point2D const* point = new Point2D(x, y);
				Junction* junction = new Junction(*point, *this, name);
				this->add(*junction);
			}
			//wenn das erste Wort = Road
			else if(stringVector[0] == "Road")
			{
				//namen einlesen
				const char* tmpName = stringVector[3].c_str();
				char name[256] = {};
				strcpy(name, tmpName);
				//Punkte aus den zugehörigen Junctions holen und speichern
				Point2D* startPoint = new Point2D(this->junctions[stringVector[1]]->getLocation());
				Point2D* endPoint = new Point2D(this->junctions[stringVector[2]]->getLocation());
				//Polyline erstellen und alle folgenden Punkte dazwischen einfügen
				Polyline2D* polyline = new Polyline2D(*startPoint, *endPoint);
				for(unsigned int i = 4; i < stringVector.size() - 1; i = i + 2)
				{
					Point2D* pointAdd = new Point2D(stod(stringVector[i]), stod(stringVector[i + 1]));
					polyline->insertPoint(*pointAdd, polyline->getNumberOfPoints());
				}
				//Junction erstellen -> wird automatisch durch den Konstruktor in das RoadNetwork hinzugefügt
				if(this->junctions.count(stringVector[1]) > 0 && this->junctions.count(stringVector[2]) > 0)
					Road* road = new Road(*this->junctions[stringVector[1]], *this->junctions[stringVector[2]], *polyline, name);
			}
		}
		//Schließen der Datei
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
