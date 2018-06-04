#include "MyForm.h"
#include <iostream>
#include <vector>
#include <string>
using namespace System;
using namespace System::Windows::Forms;
using std::vector;
using std::string;

[STAThreadAttribute]
void Main(array<System::String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	FERTIG::MyForm form;
	Application::Run(%form);
}

//S_TeamA , S_TeamB �U�W��q Team ���Ҧ����
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
	//Add ��ƶi��X��function
	result->Add("");
	ShowBattleLog();
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
