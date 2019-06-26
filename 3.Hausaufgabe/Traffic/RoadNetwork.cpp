#include "RoadNetwork.h"
#include "Junction.h"
#include "Road.h"
#include <sstream>

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

		//for(string str : this->junctions.first)
		for(auto const& element : this->junctions)
		{
			//Junction(const Point2D& position, RoadNetwork& network, const char junctionName[])
			/*
				"Junction PositionX PositionY junctionName"
			*/
			outFile << "Junction" << ";" // keyword
				<< element.second->getLocation().getX() << ";" // x-value
				<< element.second->getLocation().getY() << ";" // y-value
				<< element.second->getName() << ";"; // junctionName

			//put the inRoads
			outFile << "IN" << ";";
			for(auto const& el : element.second->inRoads)
			{
				outFile << el->getName() << ";";
			}
			//put the outRoads
			outFile << "OUT" << ";";
			for(auto const& el : element.second->outRoads)
			{
				outFile << el->getName() << ";";
			}
			outFile << "\n";
		}

		for(auto const& element : this->roads)
		{
			//Road(Junction& start, Junction& end, const Polyline2D& position, const char roadName[])
			/*
				"Road junctionNameStart junctionNameEnd RoadName
				All Points in order with -> P1x P1y P2x P2y P3x P3y ...."
			*/
			outFile << "Road" << ";" // keyword
				<< element.second->getJunction(true)->getName() << ";" // startJunction
				<< element.second->getJunction(false)->getName() << ";" // endJunction
				<< element.second->getName() << ";"; // roadName

			for(unsigned short i = 0; i < element.second->course.getNumberOfPoints(); i++) //for every point
			{
				outFile << element.second->course.getPoint(i).getX() << ";"
					<< element.second->course.getPoint(i).getY() << ";";
			}
			outFile << "\n";
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
			/*
			Alle erstmal einlesen
			for(roads){
			Road.JunctionStartName = Junctions.junctionName
			road.junctionEndName = Junctions.junctionName
			mit insert die Road ans ende der RoadMap einf�gen und der String ist der Name der Stra�e
			}
			*/

			//if(line.find("Road") != string::npos)
			//{			
			//}
			//else if(line.find("Junction") != string::npos)
			//{
			//	//const Point2D& position, RoadNetwork& network, const char junctionName[]
			//	//double x; double y;
			//	//Point2D* pos = new Point2D();
			//	//Junction* junc = new Junction();
			
			string delimiter = ";";
			unsigned int pos = 0;
			std::string token;
			//Function or Road
			pos = line.find(delimiter);
			token = line.substr(0, pos);
			line.erase(0, pos + delimiter.length());
			if(token == "Junction")
			{
				cout << "Found Junction" << endl;
				//get X
				pos = line.find(delimiter);
				token = line.substr(0, pos);
				line.erase(0, pos + delimiter.length());
				double x = stod(token);
				cout << "X-Value:" << token << endl;

				//get Y
				pos = line.find(delimiter);
				token = line.substr(0, pos);
				line.erase(0, pos + delimiter.length());
				double y = stod(token);
				cout << "Y-Value:" << token << endl;

				//get Name 
				pos = line.find(delimiter);
				token = line.substr(0, pos);
				line.erase(0, pos + delimiter.length());
				cout << "Name:" << token << endl;
				char* str = strcpy(token);
				Point2D* pos = new Point2D(x, y);
				Junction* junc = new Junction(pos,this, token);
				
				
			}
			else if(token == "Road")
			{
				cout << "Found Road" << endl;
			}



			//while((pos = line.find(delimiter)) != std::string::npos)
			//{
			//	token = line.substr(0, pos);
			//	std::cout << token << std::endl;
			//	line.erase(0, pos + delimiter.length());
			//}
			//cout << line << endl;




			//}
			//else
			//{
			//	cout << "only numbers:   ";
			//}
			////cout << line;
			//cout << endl;


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
