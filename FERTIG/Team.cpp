#include "Team.h"



Team::Team()
{
}

int Team::isNameVessel(String ^ name)
{
	for (int x = 0; x < vessels.size(); x++) {
		if (name == vessels[x]->getName()) {
			return x;
		}
	}
	return -1;
}
