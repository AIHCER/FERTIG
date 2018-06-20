#pragma once
#include "Team.h"
#include "Shell.h"
#include "Vessel.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <string>
#include <ctime>
#include <cmath>
#include <math.h>
#define PI 3.14159
#define ERR 0.00001

namespace FERTIG
{

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// MyForm 的摘要
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TextBox^  txtTeamA;
	protected:

	private: System::Windows::Forms::Button^  btnPause;

	private: System::Windows::Forms::Button^  btnStart;
	private: System::Windows::Forms::Label^  lblTimes;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::TextBox^  txtTeamB;

	private: System::Windows::Forms::GroupBox^  groupBox2;
			 //他是BattleLog的那個輸出欄
	private: System::Windows::Forms::TextBox^  txtLog;
	private: System::Windows::Forms::Timer^  TimerStart;
	private: System::ComponentModel::IContainer^  components;



	protected:

	private:
		/*------------------------------------方法跟變數定義都在這-----------------------------------------*/
		///<summary>
		/// 我只是要確定他不會重複開啟
		///</summary>
		bool start = false;
		/// <summary>
		/// 抓 TeamA 的所有資料
		/// <para>換行符號是 "\r\n" 要注意</para> 
		/// </summary>
		String ^S_TeamA;
		/// <summary>
		/// 抓 TeamB 的所有資料
		/// <para>換行符號是 "\r\n" 要注意</para> 
		/// </summary>
		String ^S_TeamB;
		/// <summary>
		/// 把運算的結果全部丟給 result
		/// <para>要用 result->Add("") 來丟入最後面</para> 
		/// <para>順序自己想辦法</para> 
		/// <para>要額外的 function 請GOOGLE 'C# List' </para>
		/// </summary>

		long long int time = 0;

		List<String^> ^result = gcnew List<String^>();

		void ShowBattleLog();

		void analysisString();

		array<String ^>^ cutString(String^);

		void excute(String ^, Team);

		void set(String ^, Team);

		void fire(String ^, Team);

		void defense(String ^, Team);

		void tag(String ^, Team);

		void move(String ^, Team);

		void vesselMove(vector <Vessel*> vessels, Team T);
		
		void not(String ^, Team);

		void addVesseltoWF(Base* object, Team team);

		void addShelltoWF(Shell* object);

		void removeVesselbyWF(Base* object, Team team);

		void removeShellbyWF(Shell* object);

		void shellMove();

		void showTime();

		void cd(vector <Vessel*> A, vector <Vessel*> B);

		void crash();
		/*------------------------------------方法跟變數定義到這就好---------------------------------------*/
#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器修改
		/// 這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			this->txtTeamA = (gcnew System::Windows::Forms::TextBox());
			this->btnPause = (gcnew System::Windows::Forms::Button());
			this->btnStart = (gcnew System::Windows::Forms::Button());
			this->lblTimes = (gcnew System::Windows::Forms::Label());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->txtTeamB = (gcnew System::Windows::Forms::TextBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->txtLog = (gcnew System::Windows::Forms::TextBox());
			this->TimerStart = (gcnew System::Windows::Forms::Timer(this->components));
			this->groupBox1->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->SuspendLayout();
			// 
			// txtTeamA
			// 
			this->txtTeamA->Location = System::Drawing::Point(6, 26);
			this->txtTeamA->Multiline = true;
			this->txtTeamA->Name = L"txtTeamA";
			this->txtTeamA->Size = System::Drawing::Size(280, 225);
			this->txtTeamA->TabIndex = 0;
			this->txtTeamA->TextChanged += gcnew System::EventHandler(this, &MyForm::txtTeamA_TextChanged);
			// 
			// btnPause
			// 
			this->btnPause->Location = System::Drawing::Point(160, 483);
			this->btnPause->Name = L"btnPause";
			this->btnPause->Size = System::Drawing::Size(93, 39);
			this->btnPause->TabIndex = 1;
			this->btnPause->Text = L"Pause";
			this->btnPause->UseVisualStyleBackColor = true;
			this->btnPause->Click += gcnew System::EventHandler(this, &MyForm::btnPause_Click);
			// 
			// btnStart
			// 
			this->btnStart->Location = System::Drawing::Point(292, 483);
			this->btnStart->Name = L"btnStart";
			this->btnStart->Size = System::Drawing::Size(93, 39);
			this->btnStart->TabIndex = 2;
			this->btnStart->Text = L"Start";
			this->btnStart->UseVisualStyleBackColor = true;
			this->btnStart->Click += gcnew System::EventHandler(this, &MyForm::btnStart_Click);
			// 
			// lblTimes
			// 
			this->lblTimes->AutoSize = true;
			this->lblTimes->Font = (gcnew System::Drawing::Font(L"新細明體", 14));
			this->lblTimes->Location = System::Drawing::Point(48, 492);
			this->lblTimes->Name = L"lblTimes";
			this->lblTimes->Size = System::Drawing::Size(74, 24);
			this->lblTimes->TabIndex = 3;
			this->lblTimes->Text = L"00:00";
			this->lblTimes->Click += gcnew System::EventHandler(this, &MyForm::lblTimes_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->txtTeamB);
			this->groupBox1->Controls->Add(this->txtTeamA);
			this->groupBox1->Location = System::Drawing::Point(433, 12);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(292, 510);
			this->groupBox1->TabIndex = 4;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"commands";
			// 
			// txtTeamB
			// 
			this->txtTeamB->Location = System::Drawing::Point(6, 273);
			this->txtTeamB->Multiline = true;
			this->txtTeamB->Name = L"txtTeamB";
			this->txtTeamB->Size = System::Drawing::Size(280, 231);
			this->txtTeamB->TabIndex = 1;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->txtLog);
			this->groupBox2->Location = System::Drawing::Point(719, 12);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(292, 510);
			this->groupBox2->TabIndex = 5;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Battle log";
			// 
			// txtLog
			// 
			this->txtLog->Location = System::Drawing::Point(12, 28);
			this->txtLog->Multiline = true;
			this->txtLog->Name = L"txtLog";
			this->txtLog->ReadOnly = true;
			this->txtLog->Size = System::Drawing::Size(280, 476);
			this->txtLog->TabIndex = 0;
			this->txtLog->TextChanged += gcnew System::EventHandler(this, &MyForm::txtLog_TextChanged);
			// 
			// TimerStart
			// 
			this->TimerStart->Interval = 66;
			this->TimerStart->Tick += gcnew System::EventHandler(this, &MyForm::TimerStart_Tick);
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(9, 17);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1038, 553);
			this->Controls->Add(this->groupBox2);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->lblTimes);
			this->Controls->Add(this->btnStart);
			this->Controls->Add(this->btnPause);
			this->Font = (gcnew System::Drawing::Font(L"新細明體", 10));
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
		/*--------------------------------這裡全都是視窗物件會看到的東西-----------------------------------*/
		/// <summary>
		/// Load function 開起來的時候先執行這邊
		/// <para>這邊是幫你畫格線</para>
		/// </summary>
	private: System::Void MyForm_Load(System::Object^  sender, System::EventArgs^  e)
	{
		array<Label^>^ labels;
		array<Label^>^ labelV;
		labels = gcnew array<Label^>(21);
		labelV = gcnew array<Label^>(21);
		Label^ DDlabel = gcnew Label();
		Label^ CVlabel = gcnew Label();
		Label^ Shelllabel = gcnew Label();
		int bias = 10;
		for (int i = 0; i < 21; i++)
		{
			labels[i] = gcnew Label();
			labels[i]->BackColor = Color::Black;
			labels[i]->Location = Point(0 + bias, 20 * i + bias);
			labels[i]->Size = Drawing::Size(400, 1);
			labels[i]->AutoSize = false;
		}
		for (int i = 0; i < 21; i++)
		{
			labelV[i] = gcnew Label();
			labelV[i]->BackColor = Color::Black;
			labelV[i]->Location = Point(20 * i + bias, 0 + bias);
			labelV[i]->Size = Drawing::Size(1, 400);
			labelV[i]->AutoSize = false;
		}
		for (int i = 0; i < 21; i++)
		{
			this->Controls->Add(labels[i]);
			this->Controls->Add(labelV[i]);
			this->Controls->Add(labels[i]);

		}
	}

			 /// <summary>
			 /// 點了Start Button 之後會執行這裡
			 /// <para>把兩個輸入框給鎖起來不給輸入</para>
			 /// <para>順變把TeamA跟TeamB的輸入傳去String</para>
			 /// <para>點了之後就會開啟Timer，每秒都會執行後面的function一次</para>
			 /// </summary>
	private: System::Void btnStart_Click(System::Object^  sender, System::EventArgs^  e)
	{
		txtTeamA->ReadOnly = true;
		txtTeamB->ReadOnly = true;
		if (!start)
		{
			start = true;
			TimerStart->Enabled = true;
			S_TeamA = txtTeamA->Text;
			S_TeamB = txtTeamB->Text;
		}
	}

			 /// <summary>
			 /// 點了Pasuse Button 之後會執行這裡
			 /// <para>把兩個輸入框給重新打開</para>
			 /// <para>把Timer關掉</para>
			 /// </summary>
	private: System::Void btnPause_Click(System::Object^  sender, System::EventArgs^  e)
	{
		txtTeamA->ReadOnly = false;
		txtTeamB->ReadOnly = false;
		if (start)
		{
			start = false;
			TimerStart->Enabled = false;
		}
	}
			 /// <summary>
			 /// 這裡是主要的執行的地方
			 /// <para>我這裡先預設好1000ms執行一次</para>
			 /// <para>請把所有實作Function放在 analysisString()</para>
			 /// </summary>
	private: System::Void TimerStart_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		S_TeamA = txtTeamA->Text;
		S_TeamB = txtTeamB->Text;

		txtTeamA->Text = "";
		txtTeamB->Text = "";
		analysisString();
	}
			 /*--------------------------------這裡全都是視窗物件會看到的東西-----------------------------------*/
	private: System::Void txtLog_TextChanged(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void lblTimes_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void txtTeamA_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
};
}
