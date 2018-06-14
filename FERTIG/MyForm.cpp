#include "MyForm.h"
using namespace System;
using namespace System::Windows::Forms;
using std::vector;
using std::string;

// 存戰艦們
vector <Vessel*> vessels;

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
	result->Add("");
	shellMove(shells);
	ShowBattleLog();

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

void FERTIG::MyForm::set(String ^ input, Team team)
{
	array <String ^>^ elements = input->Split(' ');
	Vessel *newVessel;
	String ^ type_ = elements[2];
	const char* chars =
		(const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(elements[1])).ToPointer();
	string name = chars;
	chars = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(type_)).ToPointer();
	string type = chars;
	array <String ^>^ numbers = elements[3]->Split(',');
	float x = Convert::ToDouble(numbers[0]->Replace("(", "")), y = Convert::ToDouble(numbers[1]->Replace(")", ""));
	for (int i = 0; i < TeamA.vessels.size(); i++)
		if (TeamA.vessels[i]->getsName() == name)
		return;
	for (int i = 0; i < TeamB.vessels.size(); i++)
		if (TeamB.vessels[i]->getsName() == name)
		return;	
	if (type == "CV")
		newVessel = new CV(name, type, x, y);
	else if (type == "DD")
		newVessel = new DD(name, type, x, y);
	else if (type == "CG")
		newVessel = new CG(name, type, x, y);
	else if (type == "BB")

		newVessel = new BB(name, type, x, y);
	addVesseltoWF(newVessel, team);
	

	if (team.getTeamName() == "TeamA")
		TeamA.vessels.push_back(newVessel);
	else
		TeamB.vessels.push_back(newVessel);
}

void FERTIG::MyForm::shellMove(vector <Shell*> shells) {/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	float tempR;
	float boom;
	for (int index = 0; index < shells.size(); index++) {
		shells[index]->setX(shells[index]->getX() + shells[index]->xSpeed);
		shells[index]->setY(shells[index]->getY() + shells[index]->ySpeed);

		tempR = sqrt(pow(shells[index]->getX() - shells[index]->originX, 2) + pow(shells[index]->getY() - shells[index]->originY, 2));
		if (tempR >= shells[index]->r) {
			for (int x = 0; x < TeamA.vessels.size(); x++) {
				boom = sqrt(pow(TeamA.vessels[x]->getX() - shells[index]->disX, 2) + pow(TeamA.vessels[x]->getY() - shells[index]->disY, 2));
				if (boom <= 1.5) {
					TeamA.vessels[x]->hp -= shells[index]->damage;
					if (TeamA.vessels[x]->hp <= 0) {
						TeamA.vessels.erase(TeamA.vessels.begin() + x);
					}
				}
			}
			for (int y = 0; y < TeamB.vessels.size(); y++) {
				boom = sqrt(pow(TeamB.vessels[y]->getX() - shells[index]->disX, 2) + pow(TeamB.vessels[y]->getY() - shells[index]->disY, 2));
				if (boom <= 1.5) {
					TeamB.vessels[y]->hp -= shells[index]->damage;
					if (TeamB.vessels[y]->hp <= 0) {
						TeamB.vessels.erase(TeamB.vessels.begin() + y);
					}
				}
			}

			shells.erase(shells.begin() + index);
		}



		addShelltoWF(shells[index]);
	}
}


void FERTIG::MyForm::fire(String ^ input, Team T)
{
	array <String ^>^ elements = input->Split(' ');
	String ^ name = elements[1];
	array <String ^>^ numbers = elements[2]->Split(',');
	float x = Convert::ToDouble(numbers[0]->Replace("(", "")), y = Convert::ToDouble(numbers[1]->Replace(")", ""));
	
	int index = T.isNameVessel(name);
	if (index == -1) {
		//Fail
	}

	if (T.vessels[index]->atkCurrent != 0) {
		//Fail
	}

	float r = sqrt(pow(T.vessels[index]->getX() - x, 2) + pow(T.vessels[index]->getY() - y, 2));
	if (r > T.vessels[index]->atkDistance) {
		//Fail
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
	float xSpeed = cos * T.vessels[index]->shellSpeed / 60 * 15;
	float ySpeed = sin * T.vessels[index]->shellSpeed / 60 * 15;
	chars = (const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(T.getTeamName()).ToPointer());
	string Tname = chars;
	Shell A(Tname ,T.vessels[index]->getX(), T.vessels[index]->getY(),x, y, xSpeed, ySpeed, r, T.vessels[index]->damage);
	A.setName(shellName);
	
	shells.push_back(&A);
}



void FERTIG::MyForm::defense(String ^ input, Team T)
{
	array <String ^>^ elements = input->Split(' ');
	String ^ vesselName = elements[1];
	String ^ shellName = elements[2];
	int index = T.isNameVessel(vesselName);
	if (index == -1) {
		//Fail
	}

	//if ()//Shell是否在場上

	int index2 = -1;
	for (int x = 0; x < shells.size(); x++) {
		if (shellName == shells[x]->getName()) {
			index2 = x;
		}
	}
	if (index2 == -1) {
		//Fail
	}



	float r = sqrt(pow(T.vessels[index]->getX() - shells[index2]->getX(), 2) + pow(T.vessels[index]->getY() - shells[index2]->getY(), 2));
	if (r > T.vessels[index]->defDistance) {
		//Fail
	}

	T.vessels[index]->defCurrent = T.vessels[index]->defCD;
	
	
	//把炮彈刪掉
	shells.erase(shells.begin() + index2);

}

void FERTIG::MyForm::tag(String ^ input, Team)
{
	array <String ^>^ elements = input->Split(' ');
	String ^ oldname = elements[1];
	String ^ newname = elements[2];
	int index1 = -1;
	int index2 = -1;
	for (size_t i = 0; i < vessels.size(); i++)
	{
		if (vessels[i]->getName == oldname)
		{
			index1 = i;
			break;
		}
	}
	for (size_t i = 0; i < vessels.size(); i++)
	{
		if (vessels[i]->getName == oldname)
		{
			index2 = i;
			break;
		}
	}
	if (index1 != -1 && index2 == -1)
	{
		vessels[index1]->setName(newname);
	}

}

void FERTIG::MyForm::move(String ^ input, Team T)
{
	array <String ^>^ elements = input->Split(' ');
	String ^ vesselName = elements[1];
	String ^ speedstring = elements[2];
	String ^ anglestring = elements[3];
	
	double speed = Convert::ToDouble(speedstring);
	double angle = Convert::ToDouble(anglestring);

	int index = T.isNameVessel(vesselName);
	if (index == -1) {
		//Fail
	}

	if (abs(speed) > T.vessels[index]->speed) {
		//Fail
	}
	float q = angle / 180 * PI;
	float xSpeed = std::cos(q) * speed;
	float ySpeed = -std::sin(q) * speed;
	T.vessels[index]->setX(T.vessels[index]->getX() + xSpeed);
	T.vessels[index]->setY(T.vessels[index]->getY() + ySpeed);
	bool outOfRange = false;
	if (T.vessels[index]->getX() - 20 > ERR) {
		T.vessels[index]->setX(20);
		outOfRange = true;
	}
	if (T.vessels[index]->getX() < -ERR) {
		T.vessels[index]->setX(0); 
		outOfRange = true;
	}
	if (T.vessels[index]->getY() - 20 > ERR) {
		T.vessels[index]->setY(20);
		outOfRange = true;
	}
	if (T.vessels[index]->getY() < -ERR) {
		T.vessels[index]->setY(0);
		outOfRange = true;
	}
	if (!outOfRange)
		addVesseltoWF(T.vessels[index], T);
}

void FERTIG::MyForm::not(String ^, Team)
{

}

void FERTIG::MyForm::addShelltoWF(Shell* object) {
	String ^ labelName = object->getName();
	Label ^ newObject = gcnew Label();
	removeShellbyWF(object);
	newObject->Name = labelName;
	newObject->Text = "●" + object->getName();
	newObject->Location = Point(object->getX() * 20 + 10, object->getY() * 20 + 10);
	//確認他的隊伍然後改顏色
	newObject->ForeColor = Color::Purple;
	//放到畫面上
	newObject->AutoSize = true;
	this->Controls->Add(newObject);
}

void FERTIG::MyForm::addVesseltoWF(Base* object, Team team) {
	String ^ labelName = team.getTeamName() + "_" + object->getName();
	Label ^ newObject = gcnew Label();
	removeVesselbyWF(object, team);
	newObject->Name = labelName;
	newObject->Text = "▲" + object->getName();
	newObject->Location = Point(object->getX() * 20 + 10, object->getY() * 20 + 10);
	//確認他的隊伍然後改顏色
	if (team.getTeamName() == "TeamA")
		newObject->ForeColor = Color::Red;
	else
		newObject->ForeColor = Color::Blue;
	newObject->AutoSize = true;
	//放到畫面上
	this->Controls->Add(newObject);
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