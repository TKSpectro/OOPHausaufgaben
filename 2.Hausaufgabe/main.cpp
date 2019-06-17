#include "Cube.h"
#include "Cuboid.h"
#include "Tower.h"
#include "Cylinder.h"
#include "Sphere.h"
#include "Prism.h"
#include "House.h"
#include "Cone.h"
#include "BodyQueue.h"

using namespace std;

void QueueAdd(BodyQueue* my_queue);
void QueueRemove(BodyQueue* my_queue);

unsigned int menu(bool RemoveVisibility);

/* Zusatz 6.) :
	Die ID vergabe müsste in den Klassen selbst erfolgen und nicht in Body.
	Hochzählen/Vergabe der ID passiert im Konstruktor
*/


int main()
{
	BodyQueue my_queue = BodyQueue();
	bool finish = false;
	do
	{
		switch(menu(!my_queue.isEmpty()))
		{
			case 0: finish = true;
				break;
			case 1: QueueAdd(&my_queue);
				break;
			case 2: QueueRemove(&my_queue);
				break;
			default:
				cout << "wrong input" << endl;
				break;
		}
	} while(!finish);

	return 0;
}

unsigned int menu(bool RemoveVisibility)
{
	unsigned int pick = 0;
	bool end = false;
	do
	{
		cout << endl << "*****************Body Menu*****************" << endl;
		cout << "Choose between:" << endl;
		cout << "Close:       0" << endl;
		cout << "Create Body: 1" << endl;
		if(RemoveVisibility)
			cout << "Remove Body: 2" << endl;
		cout << "*******************************************" << endl;

		cin >> pick;
		if(pick == 0 || pick == 1 || (pick == 2 && RemoveVisibility))
			end = true;
		else
			cout << ("wrong input") << endl;
	} while(!end);
	system("cls");
	return pick;
}

void QueueAdd(BodyQueue* my_queue)
{
	unsigned int pick = 0;
	cout << "What type of body do you wanna add: " << endl;
	bool end = false;
	do
	{
		cout << "1 - Cube" << endl;
		cout << "2 - Cuboid" << endl;
		cout << "3 - Sphere" << endl;
		cout << "4 - Cone" << endl;
		cout << "5 - Cylinder" << endl;
		cout << "6 - Prism" << endl;
		cout << "7 - House" << endl;
		cout << "8 - Tower" << endl;

		cin >> pick;

		if(pick > 0 && pick < 9)
			end = true;
		else
			cout << "wrong input" << endl;
	} while(!end);

	system("cls");

	switch(pick)
	{
		case 1:
			my_queue->enqueue(*Cube::createByDialog());
			break;
		case 2:
			my_queue->enqueue(*Cuboid::createByDialog());
			break;
		case 3:
			my_queue->enqueue(*Sphere::createByDialog());
			break;
		case 4:
			my_queue->enqueue(*Cone::createByDialog());
			break;
		case 5:
			my_queue->enqueue(*Cylinder::createByDialog());
			break;
		case 6:
			my_queue->enqueue(*Prism::createByDialog());
			break;
		case 7:
			my_queue->enqueue(*House::createByDialog());
			break;
		case 8:
			my_queue->enqueue(*Tower::createByDialog());
			break;

		default:
			break;
	}
}

void QueueRemove(BodyQueue* my_queue)
{
	cout << "Removing body" << endl;
	Body* body = (Body*)my_queue->dequeue();
	cout << "ID:      \t" << body->getCount() << endl;
	cout << "Type:    \t" << body->getBodyName() << endl;
	cout << "Position:\tx= " << body->getLocation().getX() << endl << "\t\ty= " << body->getLocation().getY() << endl << "\t\tz= " << body->getLocation().getZ() << endl;
	cout << "Volume:  \t" << body->getVolume() << endl;
	cout << "Surface: \t" << body->getSurface() << endl;
	delete body;
	system("pause");
	system("cls");
}