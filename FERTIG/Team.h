#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Vessel.h"

using std::vector;

class Team
{
public:
	Team();
	Team(string name) { teamName = name; };
	String^ getTeamName()
	{
		String^ name = gcnew String(teamName.c_str());
		return name;
	};
	void setShootTimes() { ShootTimes++; };

	int getShootTimes() { return ShootTimes; };
private:
	vector<Vessel*> vessels;
	string teamName;
	int ShootTimes = 0;
};
