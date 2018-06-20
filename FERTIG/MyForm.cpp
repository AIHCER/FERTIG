#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms;
using std::vector;
using std::string;

// 存砲彈們
vector <Shell*> shells;

enum Command {
	SET,
	FIRE,
	DEFENSE,
	TAG,
	MOVE,
	NOT
};

void moveSecond(double speed, double angle, Team& T, int index) {
	double q = angle / 180 * PI;
	double xSpeed = std::cos(q) * speed;
	double ySpeed = -std::sin(q) * speed;
	if (T.vessels[index]->getX() > 20 || T.vessels[index]->getX() < 0 || T.vessels[index]->getY() > 20 || T.vessels[index]->getY() < 0) {
		return;
	}
	T.vessels[index]->setX(T.vessels[index]->getX() + xSpeed);
	T.vessels[index]->setY(T.vessels[index]->getY() + ySpeed);
}

Command changeType(String ^ input) {
	if (input == "SET")
		return SET;
	else if (input == "FIRE")
		return FIRE;
	else if (input == "DEFENSE")
		return DEFENSE;
	else if (input == "TAG")
		return TAG;
	else if (input == "MOVE")
		return MOVE;
	else if (input == "NOT")
		return NOT;
	else {
		////////////////////
		// RUN TIME ERROR //
		////////////////////
	}
}

[STAThreadAttribute]
void Main(array<System::String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	FERTIG::MyForm form;

	Application::Run(%form);
}

//S_TeamA , S_TeamB 顧名思義 Team 的所有資料

Team TeamA("TeamA");
Team TeamB("TeamB");

//result 裝的是判斷完的結果,順序要自己確認
//ShowBattleLog() 他做的是把result所有的字丟去Log的textBox
//analaysisString() 所有的運算都在這裡處理
//不懂的變數碰一下他 他會有說明


/// <summary>
/// <para>按Start的時候已經把"TeamA"跟"TeamB"的值抓好</para> 
/// <para>這裡面就照自己的方式實作就好了</para> 
///	<para>把這個當作 Main function 在實作就對了</para> 
///	<para>!注意! 每一秒會執行這個 function 一次</para> 
/// </summary>
void FERTIG::MyForm::analysisString()
{
	array<String ^>^ Team_A_data = cutString(S_TeamA);
	array<String ^>^ Team_B_data = cutString(S_TeamB);
	for (int i = 0; i < Team_A_data->Length; i++) {
		excute(Team_A_data[i], TeamA);
	}
	for (int i = 0; i < Team_B_data->Length; i++) {
		excute(Team_B_data[i], TeamB);
	}
	crash();
	shellMove();
	vesselMove(TeamA.vessels, TeamA);
	vesselMove(TeamB.vessels, TeamB);
	cd(TeamA.vessels, TeamB.vessels);
	ShowBattleLog();
	showTime();
	time++;
}

void FERTIG::MyForm::showTime()
{
	TimeSpan ^ts = gcnew TimeSpan(time * 10000000);
	lblTimes->Text = ((int)ts->TotalMinutes).ToString("0#") + ":" + ts->Seconds.ToString("0#");
}



void FERTIG::MyForm::excute(String ^ input, Team team) {
	if (input == "")
		return;
	Command cmd = changeType(input->Substring(0, input->IndexOf(' ')));
	switch (cmd) {
	case SET:
		set(input, team);
		break;
	case FIRE:
		fire(input, team);
		break;
	case DEFENSE:
		defense(input, team);
		break;
	case TAG:
		tag(input, team);
		break;
	case MOVE:
		move(input, team);
		break;
	case NOT:
		not(input, team);
		break;
	}
}

void FERTIG::MyForm::cd(vector <Vessel*> A, vector <Vessel*> B) {
	for (int x = 0; x < A.size(); x++) {
		if (A[x]->atkCurrent > 0) {
			A[x]->atkCurrent--;
		}
		if (A[x]->defCurrent > 0) {
			A[x]->defCurrent--;
		}
	}
	for (int x = 0; x < B.size(); x++) {
		if (B[x]->atkCurrent > 0) {
			B[x]->atkCurrent--;
		}
		if (B[x]->defCurrent > 0) {
			B[x]->defCurrent--;
		}
	}
}

void FERTIG::MyForm::set(String ^ input, Team team)
{
	String ^ gg = "[" + lblTimes->Text + "] ";
	gg += team.getTeamName();
	gg += " SET ";

	array <String ^>^ elements = input->Split(' ');
	Vessel *newVessel;
	String ^ type_ = elements[2];
	const char* chars =
		(const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(elements[1])).ToPointer();
	gg += elements[1];
	gg += " with ";
	string name = chars;
	chars = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(type_)).ToPointer();
	gg += type_;
	gg += " at ";
	string type = chars;
	gg += elements[3];
	array <String ^>^ numbers = elements[3]->Split(',');
	float x = Convert::ToDouble(numbers[0]->Replace("(", "")), y = Convert::ToDouble(numbers[1]->Replace(")", ""));
	for (int i = 0; i < team.vessels.size(); i++)
		if (team.vessels[i]->getsName() == name)
		{
			gg += " -> Fail";
			result->Add(gg);
			return;
		}

	if (type == "CV")
		newVessel = new CV(name, type, x, y);
	else if (type == "DD")
		newVessel = new DD(name, type, x, y);
	else if (type == "CG")
		newVessel = new CG(name, type, x, y);
	else if (type == "BB")
		newVessel = new BB(name, type, x, y);
	else if (type == "GG")
		newVessel = new GG(name, type, x, y);
	else
	{
		gg += " -> Fail";
		result->Add(gg);
		return;
	}
	addVesseltoWF(newVessel, team);


	if (team.getTeamName() == "TeamA")
		TeamA.vessels.push_back(newVessel);
	else
		TeamB.vessels.push_back(newVessel);
	gg += " -> Success";
	result->Add(gg);
}

void FERTIG::MyForm::shellMove() {/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	float tempR = 0;
	float boom = 0;
	for (int index = 0; index < shells.size(); index++) {
		bool hit = false;
		List <String ^> ^ output = gcnew List <String ^>();
		shells[index]->setX(shells[index]->getX() + shells[index]->xSpeed);
		shells[index]->setY(shells[index]->getY() + shells[index]->ySpeed);

		tempR = sqrt(pow(shells[index]->getX() - shells[index]->originX, 2) + pow(shells[index]->getY() - shells[index]->originY, 2));
		if (tempR >= shells[index]->r && shells.size() != 0) {
			for (int x = 0; x < TeamA.vessels.size(); x++) {
				boom = sqrt(pow(TeamA.vessels[x]->getX() - shells[index]->disX, 2) + pow(TeamA.vessels[x]->getY() - shells[index]->disY, 2));
				if (boom <= 1.5) {
					output->Add("TeamA " + TeamA.vessels[x]->getName());
					hit = true;
					TeamA.vessels[x]->minus += shells[index]->damage;
				}
			}
			for (int y = 0; y < TeamB.vessels.size(); y++) {
				boom = sqrt(pow(TeamB.vessels[y]->getX() - shells[index]->disX, 2) + pow(TeamB.vessels[y]->getY() - shells[index]->disY, 2));
				if (boom <= 1.5) {
					output->Add("TeamB " + TeamB.vessels[y]->getName());
					hit = true;
					TeamB.vessels[y]->minus += shells[index]->damage;

				}
			}
			String ^ gg = "";
			gg = "[" + lblTimes->Text + "] " + shells[index]->getName() + " arrived (" + shells[index]->disX + ", " + shells[index]->disY + ") ";
			if (hit) {
				gg += " -> hit {";
				for (int i = 0; i < output->Count; i++) {
					gg += output[i];
					if (i != output->Count - 1)
						gg += ", ";
				}
				gg += "}";
			}
			else {
				gg += " -> miss";
			}
			result->Add(gg);
			removeShellbyWF(shells[index]);
			shells.erase(shells.begin() + index);
			index--;
		}
		else {
			addShelltoWF(shells[index]);
		}
	}
	for (int y = 0; y < TeamB.vessels.size(); y++) {
		TeamB.vessels[y]->hp -= TeamB.vessels[y]->minus;
		TeamB.vessels[y]->minus = 0;
		if (TeamB.vessels[y]->hp <= 0) {
			removeVesselbyWF(TeamB.vessels[y], TeamB);
			TeamB.vessels.erase(TeamB.vessels.begin() + y);
			y--;
		}
	}
	for (int y = 0; y < TeamA.vessels.size(); y++) {
		TeamA.vessels[y]->hp -= TeamA.vessels[y]->minus;
		TeamA.vessels[y]->minus = 0;
		if (TeamA.vessels[y]->hp <= 0) {
			removeVesselbyWF(TeamA.vessels[y], TeamA);
			TeamA.vessels.erase(TeamA.vessels.begin() + y);
			y--;
		}
	}
}


void FERTIG::MyForm::fire(String ^ input, Team T)
{
	String ^ gg = "[" + lblTimes->Text + "] ";
	gg += T.getTeamName();
	array <String ^>^ elements = input->Split(' ');
	String ^ name = elements[1];
	gg += " ";
	gg += name;
	gg += " Fire to ";
	gg += elements[2];
	array <String ^>^ numbers = elements[2]->Split(',');
	float x = Convert::ToDouble(numbers[0]->Replace("(", "")), y = Convert::ToDouble(numbers[1]->Replace(")", ""));

	int index = T.isNameVessel(name);
	if (index == -1) {
		gg += " -> Fail ";
		result->Add(gg);
		return; // fail
	}

	if (T.vessels[index]->atkCurrent != 0) {
		gg += " -> Fail ";
		result->Add(gg);
		return; // fail
	}

	float r = sqrt(pow(T.vessels[index]->getX() - x, 2) + pow(T.vessels[index]->getY() - y, 2));
	if (r > T.vessels[index]->atkDistance) {
		gg += " -> Fail ";
		result->Add(gg);
		return; // fail
	}

	T.vessels[index]->atkCurrent = T.vessels[index]->atkCD;
	//每次跑的時候還沒減掉CD

	T.setShootTimes();
	const char* chars =
		(const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(T.getTeamName())).ToPointer();
	string teamName = chars;
	string a = std::to_string(T.getShootTimes());
	string shellName = "Shell_" + teamName + a;

	float c = x - T.vessels[index]->getX();
	float d = y - T.vessels[index]->getY();
	float cos = c / r;
	float sin = d / r;
	float xSpeed = cos * T.vessels[index]->shellSpeed / 60;
	float ySpeed = sin * T.vessels[index]->shellSpeed / 60;
	chars = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(T.getTeamName()).ToPointer());
	string Tname = chars;
	Shell * A;
	A = new Shell(Tname, T.vessels[index]->getX(), T.vessels[index]->getY(), x, y, xSpeed, ySpeed, r, T.vessels[index]->damage);
	A->setX(T.vessels[index]->getX());
	A->setY(T.vessels[index]->getY());
	A->setName(shellName);

	shells.push_back(A);
	gg += " -> Success ";
	result->Add(gg);
}



void FERTIG::MyForm::defense(String ^ input, Team T)
{
	String ^ log = "[" + lblTimes->Text + "] ";
	array <String ^>^ elements = input->Split(' ');
	String ^ vesselName = elements[1];
	String ^ shellName = elements[2];
	log += vesselName + " DEFENSE " + shellName;
	int index = T.isNameVessel(vesselName);
	if (index == -1) {
		log += " -> Fail";
		result->Add(log);
		return;
	}

	//if ()//Shell是否在場上

	int index2 = -1;
	for (int x = 0; x < shells.size(); x++) {
		if (shellName == shells[x]->getName()) {
			index2 = x;
		}
	}
	if (index2 == -1) {
		log += " -> Fail";
		result->Add(log);
		return;
	}

	float r = sqrt(pow(T.vessels[index]->getX() - shells[index2]->getX(), 2) + pow(T.vessels[index]->getY() - shells[index2]->getY(), 2));
	if (r > T.vessels[index]->defDistance) {
		log += " -> Fail";
		result->Add(log);
		return;
	}

	T.vessels[index]->defCurrent = T.vessels[index]->defCD;
	
	//把炮彈刪掉
	removeShellbyWF(shells[index2]);
	shells.erase(shells.begin() + index2);
	log += " -> Hit";
	result->Add(log);
}

void FERTIG::MyForm::tag(String ^ input, Team T)
{
	String ^ gg = "[" + lblTimes->Text + "] ";
	gg += T.getTeamName();
	gg += " RENAME ";
	array <String ^>^ elements = input->Split(' ');
	String ^ oldname = elements[1];
	String ^ newname = elements[2];
	gg += oldname;
	gg += " to ";
	gg += newname;
	int index1 = -1;
	int index2 = -1;
	for (size_t i = 0; i < T.vessels.size(); i++)
	{
		if (T.vessels[i]->getName() == oldname)
		{
			index1 = i;
			break;
		}
	}
	for (size_t i = 0; i < T.vessels.size(); i++)
	{
		if (T.vessels[i]->getName() == newname)
		{
			index2 = i;
			break;
		}
	}
	if (index1 != -1 && index2 == -1)
	{
		removeVesselbyWF(T.vessels[index1], T);
		T.vessels[index1]->setName(newname);
		addVesseltoWF(T.vessels[index1], T);
		gg += " -> Success";
		result->Add(gg);
	}
	else
	{
		gg += " -> Fail";
		result->Add(gg);
	}
}

void FERTIG::MyForm::move(String ^ input, Team T)
{
	String ^ gg = "[" + lblTimes->Text + "] ";
	gg += T.getTeamName();
	gg += " ";
	array <String ^>^ elements = input->Split(' ');
	String ^ vesselName = elements[1];
	String ^ speedstring = elements[2];
	String ^ anglestring = elements[3];
	gg += elements[1];
	gg += " MOVE to ";
	gg += elements[3];
	gg += " as ";
	gg += elements[2];
	double speed = Convert::ToDouble(speedstring);
	double angle = Convert::ToDouble(anglestring);

	int index = T.isNameVessel(vesselName);
	if (index == -1) {
		gg += " -> Fail";
		result->Add(gg);
		return; //Fail
	}

	if (abs(speed) > T.vessels[index]->speed) {
		gg += " -> Fail";
		result->Add(gg);
		return;
		//Fail
	}
	float q = angle / 180 * PI;
	float xSpeed = std::cos(q) * speed / 60;
	float ySpeed = -std::sin(q) * speed / 60;
	T.vessels[index]->xSpeed = xSpeed;
	T.vessels[index]->ySpeed = ySpeed;
	T.vessels[index]->moveORnot = true;
	gg += " -> Success";
	result->Add(gg);
}

void FERTIG::MyForm::vesselMove(vector <Vessel*> vessels, Team T) {
	for (int index = 0; index < vessels.size(); index++) {
		if (vessels[index]->moveORnot == true) {
			vessels[index]->setX(vessels[index]->getX() + vessels[index]->xSpeed);
			vessels[index]->setY(vessels[index]->getY() + vessels[index]->ySpeed);
			bool outOfRange = false;
			if (vessels[index]->getX() - 20 > ERR) {
				vessels[index]->setX(20);
				outOfRange = true;
				vessels[index]->moveORnot = false;
			}
			if (vessels[index]->getX() < -ERR) {
				vessels[index]->setX(0);
				outOfRange = true;
				vessels[index]->moveORnot = false;
			}
			if (vessels[index]->getY() - 20 > ERR) {
				vessels[index]->setY(20);
				outOfRange = true;
				vessels[index]->moveORnot = false;
			}
			if (vessels[index]->getY() < -ERR) {
				vessels[index]->setY(0);
				outOfRange = true;
				vessels[index]->moveORnot = false;
			}
			if (!outOfRange)
				addVesseltoWF(vessels[index], T);
		}

	}
}

void FERTIG::MyForm::not(String ^, Team)
{

}

void FERTIG::MyForm::addShelltoWF(Shell* object) {
	String ^ labelName = object->getName();
	labelName = labelName->Replace("-", "");
	Label ^ newObject = gcnew Label();
	if (this->Controls[labelName] != nullptr)
		newObject = (Label^)this->Controls[labelName];
	else {
		newObject->Name = labelName;
		newObject->Text = "●" + object->getName();
		//確認他的隊伍然後改顏色
		newObject->ForeColor = Color::Purple;
		//放到畫面上
		newObject->AutoSize = true;
	}
	newObject->Location = Point(object->getX() * 20 + 10, object->getY() * 20 + 10);
	if (this->Controls[labelName] == nullptr) {
		removeShellbyWF(object);
		this->Controls->Add(newObject);
	}
}

void FERTIG::MyForm::addVesseltoWF(Base* object, Team team) {
	String ^ labelName = team.getTeamName() + "_" + object->getName();
	labelName = labelName->Replace("-", "");
	Label ^ newObject = gcnew Label();
	if (this->Controls[labelName] != nullptr)
		newObject = (Label^)this->Controls[labelName];
	else {
		newObject->Name = labelName;
		newObject->Text = "▲" + object->getName();
		//確認他的隊伍然後改顏色
		if (team.getTeamName() == "TeamA")
			newObject->ForeColor = Color::Red;
		else
			newObject->ForeColor = Color::Blue;
		newObject->AutoSize = true;
	}
	newObject->Location = Point(object->getX() * 20 + 10, object->getY() * 20 + 10);
	//放到畫面上
	if (this->Controls[labelName] == nullptr) {
		removeVesselbyWF(object, team);
		this->Controls->Add(newObject);
	}
}

void FERTIG::MyForm::removeVesselbyWF(Base* object, Team team) {
	String^ LabelName = team.getTeamName() + "_" + object->getName();
	LabelName = LabelName->Replace("-", "");
	if (this->Controls[LabelName] != nullptr)
		this->Controls->RemoveByKey(LabelName);
}

void FERTIG::MyForm::removeShellbyWF(Shell* object) {
	String^ LabelName = object->getName();
	LabelName = LabelName->Replace("-", "");
	if (this->Controls[LabelName] != nullptr)
		this->Controls->RemoveByKey(LabelName);
}

array<String ^>^ FERTIG::MyForm::cutString(String ^ input) {
	input = input->Replace("\r\n", "\n");
	return input->Split('\n');
}

/// <summary>
/// <para>把result所有存放的結果全部都輸出出來</para> 
/// <para>要確保資料沒有問題</para> 
///	<para>順序在放進reuslt前搞定</para> 
/// </summary>

void FERTIG::MyForm::ShowBattleLog()
{
	txtLog->Text = "";
	for (int i = 0; i < result->Count; i++)
	{
		txtLog->Text += result[i] + "\r\n";
	}
}

void FERTIG::MyForm::crash() {

	for (size_t i = 0; i < TeamA.vessels.size(); i++)
	{
		for (size_t j = i + 1; j < TeamA.vessels.size(); j++)
		{
			float r = sqrt(pow(TeamA.vessels[i]->getX() - TeamA.vessels[j]->getX(), 2) + pow(TeamA.vessels[i]->getY() - TeamA.vessels[j]->getY(), 2));
			if (r < 0.5 && TeamA.vessels[i]->hp > 0 && TeamA.vessels[j]->hp > 0)
			{
				TeamA.vessels[i]->moveORnot = false;
				TeamA.vessels[j]->moveORnot = false;
				TeamA.vessels[i]->hp -= 1;
				TeamA.vessels[j]->hp -= 1;
				String ^ gg = "[" + lblTimes->Text + "] ";
				gg += TeamA.getTeamName();
				gg += "'s ";
				gg += TeamA.vessels[i]->getName();
				gg += " & ";
				gg += TeamA.getTeamName();
				gg += "'s ";
				gg += TeamA.vessels[j]->getName();
				gg += " collide and stop. \r\n             ";
				gg = gg + TeamA.vessels[i]->getName() + "'s hp -> " + TeamA.vessels[i]->hp;
				gg += "\r\n             ";
				gg = gg + TeamA.vessels[j]->getName() + "'s hp -> " + TeamA.vessels[j]->hp;
				result->Add(gg);
			}
		}
	}
	for (size_t i = 0; i < TeamB.vessels.size(); i++)
	{
		for (size_t j = i + 1; j < TeamB.vessels.size(); j++)
		{
			float r = sqrt(pow(TeamB.vessels[i]->getX() - TeamB.vessels[j]->getX(), 2) + pow(TeamB.vessels[i]->getY() - TeamB.vessels[j]->getY(), 2));
			if (r < 0.5 && TeamB.vessels[i]->hp > 0 && TeamB.vessels[j]->hp > 0)
			{
				TeamB.vessels[i]->moveORnot = false;
				TeamB.vessels[j]->moveORnot = false;
				TeamB.vessels[i]->hp -= 1;
				TeamB.vessels[j]->hp -= 1;
				String ^ gg = "[" + lblTimes->Text + "] ";
				gg += TeamB.getTeamName();
				gg += "'s ";
				gg += TeamB.vessels[i]->getName();
				gg += " & ";
				gg += TeamB.getTeamName();
				gg += "'s ";
				gg += TeamB.vessels[j]->getName();
				gg += " collide and stop. \r\n             ";
				gg = gg + TeamB.vessels[i]->getName() + "'s hp -> " + TeamB.vessels[i]->hp;
				gg += "\r\n             ";
				gg = gg + TeamB.vessels[j]->getName() + "'s hp -> " + TeamB.vessels[j]->hp;
				result->Add(gg);
			}
		}
	}
	for (size_t i = 0; i < TeamA.vessels.size(); i++)
	{
		for (size_t j = 0; j < TeamB.vessels.size(); j++)
		{
			float r = sqrt(pow(TeamA.vessels[i]->getX() - TeamB.vessels[j]->getX(), 2) + pow(TeamA.vessels[i]->getY() - TeamB.vessels[j]->getY(), 2));
			if (r < 0.5 && TeamA.vessels[i]->hp > 0 && TeamB.vessels[j]->hp > 0)
			{
				TeamA.vessels[i]->moveORnot = false;
				TeamB.vessels[j]->moveORnot = false;
				TeamA.vessels[i]->hp -= 1;
				TeamB.vessels[j]->hp -= 1;
				String ^ gg = "[" + lblTimes->Text + "] ";
				gg += TeamA.getTeamName();
				gg += "'s ";
				gg += TeamA.vessels[i]->getName();
				gg += " & ";
				gg += TeamB.getTeamName();
				gg += "'s ";
				gg += TeamB.vessels[j]->getName();
				gg += " collide and stop. \r\n             ";
				gg = gg + TeamA.vessels[i]->getName() + "'s hp -> " + TeamA.vessels[i]->hp;
				gg += "\r\n             ";
				gg = gg + TeamB.vessels[j]->getName() + "'s hp -> " + TeamB.vessels[j]->hp;
				result->Add(gg);

			}
		}
	}
	for (size_t i = 0; i < TeamA.vessels.size(); i++)
	{
		if (TeamA.vessels[i]->hp <= 0)
		{
			removeVesselbyWF(TeamA.vessels[i], TeamA);
			TeamA.vessels.erase(TeamA.vessels.begin() + i);
			i--;
		}
	}
	for (size_t i = 0; i < TeamB.vessels.size(); i++)
	{
		if (TeamB.vessels[i]->hp <= 0)
		{
			removeVesselbyWF(TeamB.vessels[i], TeamB);
			TeamB.vessels.erase(TeamB.vessels.begin() + i);
			i--;
		}
	}
}