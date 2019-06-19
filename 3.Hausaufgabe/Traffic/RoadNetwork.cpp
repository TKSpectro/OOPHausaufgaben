#include "RoadNetwork.h"
#include "Junction.h"
#include "Road.h"

bool RoadNetwork::add(Junction & junction)
{
	bool done = false;
	if (this->junctions.find(junction.getName()) == this->junctions.end()) {
		this->junctions.insert(NodeMap::value_type(junction.getName(), &junction));
		//this->junctions[junction.getName()] = &junction; // So ginge es f�r maps auch
		done = true;
	}
	return done;
}

void RoadNetwork::add(Road & road)
{
	this->roads.insert(RoadMap::value_type(road.getName(), &road));
}

void RoadNetwork::remove(Road & road)
{
	// Es k�nnten mehrere Eintr�ge mit dem vorgegebenen Namen sein...
	//std::pair<RoadMap::iterator, RoadMap::iterator> iters = this->roads.equal_range(road.getName());
	auto iters = this->roads.equal_range(road.getName());
	// Wir suchen in dem Bereich gleicher Namen nach dem Eintrag mit der richtigen Stra�e
	for (; iters.first != iters.second; ++iters.first) {
		if (iters.first->second == &road) {
			// Stra�e gefunden --> l�schen und tsch�ss!
			this->roads.erase(iters.first);
			break;
		}
	}
}

void RoadNetwork::remove(Junction & junction)
{
	auto iter = this->junctions.find(junction.getName());
	if (iter != this->junctions.end()) {
		this->junctions.erase(iter);
	}
}

//void RoadNetwork::draw(Drawer2D & drawer) const
//{
//	for (RoadMap::value_type entry : this->roads) {
//		entry.second->draw(drawer);
//	}
//	for (NodeMap::value_type entry : this->junctions) {
//		entry.second->draw(drawer);
//	}
//}

ostream& operator<<(ostream& os, const RoadNetwork& dt)
{
	os << "test";
	return os;
}

istream& operator>>(istream& is, const RoadNetwork& dt)
{

	return is;
}
