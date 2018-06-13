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
	String ^ type = elements[2];
	const char* chars =
		(const char*)(System::Runtime::InteropServices::Marshal::StringToHGlobalAnsi(elements[1])).ToPointer();
	string name = chars;
	array <String ^>^ numbers = elements[3]->Split(',');
	float x = Convert::ToDouble(numbers[0]->Replace("(", "")), y = Convert::ToDouble(numbers[1]->Replace(")", ""));
	if (type == "CV")
		newVessel = new CV(name, x, y);
	else if (type == "DD")
		newVessel = new DD(name, x, y);
	else if (type == "CG")
		newVessel = new CG(name, x, y);
	else if (type == "BB")
		newVessel = new BB(name, x, y);
	addObjecttoWF(newVessel, team);
	vessels.push_back(newVessel);
}

void FERTIG::MyForm::fire(String ^, Team)
{

}

void FERTIG::MyForm::defense(String ^, Team)
{

}

void FERTIG::MyForm::tag(String ^, Team)
{

}

void FERTIG::MyForm::move(String ^, Team)
{

}

void FERTIG::MyForm::not(String ^, Team)
{

}

void FERTIG::MyForm::addObjecttoWF(Base* object, Team team) {
	String ^ labelName = team.getTeamName() + "_" + object->getName();
	Label ^ newObject = gcnew Label();
	newObject->Name = labelName;
	if (labelName->IndexOf("Shell") != -1)
		newObject->Text = "●" + object->getName();
	else
		newObject->Text = "▲" + object->getName();
	newObject->Location = Point(object->getX() * 20 + 10, object->getY() * 20 + 10);
	//確認他的隊伍然後改顏色
	if (team.getTeamName() == "TeamA")
		newObject->ForeColor = Color::Red;
	else
		newObject->ForeColor = Color::Blue;
	//放到畫面上
	this->Controls->Add(newObject);
}

void FERTIG::MyForm::removeObjectbyWF(Base*, Team team) {

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