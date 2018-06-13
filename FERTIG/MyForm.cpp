#include "MyForm.h"
#include "Team.h"
#include "Shell.h"

#include <iostream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include <math.h>

using namespace System;
using namespace System::Windows::Forms;
using std::vector;
using std::string;

// �s��ĥ��
vector <Vessel> vessels;

// �s���u��
vector <Shell> shells;

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

//S_TeamA , S_TeamB �U�W��q Team ���Ҧ����

Team TeamA("TeamA");
Team TeamB("TeamB");

//result �˪��O�P�_�������G,���ǭn�ۤv�T�{
//ShowBattleLog() �L�����O��result�Ҧ����r��hLog��textBox
//analaysisString() �Ҧ����B�ⳣ�b�o�̳B�z
//�������ܼƸI�@�U�L �L�|������

/// <summary>
/// <para>��Start���ɭԤw�g��"TeamA"��"TeamB"���ȧ�n</para> 
/// <para>�o�̭��N�Ӧۤv���覡��@�N�n�F</para> 
///	<para>��o�ӷ�@ Main function �b��@�N��F</para> 
///	<para>!�`�N! �C�@��|����o�� function �@��</para> 
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
	int cmd = changeType(input->Substring(0, input->IndexOf(' ')));
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

void FERTIG::MyForm::set(String ^, Team)
{
	throw gcnew System::NotImplementedException();
}

void FERTIG::MyForm::fire(String ^, Team)
{
	throw gcnew System::NotImplementedException();
}

void FERTIG::MyForm::defense(String ^, Team)
{
	throw gcnew System::NotImplementedException();
}

void FERTIG::MyForm::tag(String ^, Team)
{
	throw gcnew System::NotImplementedException();
}

void FERTIG::MyForm::move(String ^, Team)
{
	throw gcnew System::NotImplementedException();
}

void FERTIG::MyForm::not(String ^, Team)
{
	throw gcnew System::NotImplementedException();
}

void addObjectoWF(Base* object, Team team) {
	String ^ labelName = team.getTeamName() + "_" + object->getName;
	Label ^ newObject = gcnew Label();
	newObject->Name = labelName;
	if (labelName->IndexOf("Shell") != -1)
		newObject->Text = "��" + object->getName();
	else
		newObject->Text = "��" + object->getName();
}

void removeObjectoWF(Base*){

}

array<String ^>^ FERTIG::MyForm::cutString(String ^ input) {
	input = input->Replace("\r\n", "\n");
	return input->Split('\n');
}

/// <summary>
/// <para>��result�Ҧ��s�񪺵��G��������X�X��</para> 
/// <para>�n�T�O��ƨS�����D</para> 
///	<para>���Ǧb��ireuslt�e�d�w</para> 
/// </summary>

void FERTIG::MyForm::ShowBattleLog()
{
	txtLog->Text = "";
	for (int i = 0; i < result->Count; i++)
	{
		txtLog->Text += result[i] + "\r\n";
	}
}