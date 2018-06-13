#pragma once

#include <iostream>
#include <vector>
#include <string>
#include "Vessel.h"
#include "Shell.h"

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
	int isNameVessel(String ^ name);
	vector<Vessel*> vessels;


private:
	string teamName;
	int ShootTimes = 0;
};
