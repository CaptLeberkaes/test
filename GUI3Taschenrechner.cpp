#include "stdafx.h"
#include <string>

using namespace System;
using namespace System::Windows::Forms;


//! -- TO DO --
//! Mehrfachberechnungen wie 2+2+3-5 am stueck ermoeglichen
//! zu lange floats abwuergen


// __Features__
// Fortlaufende Berechnung mit dem Ergebnis
// keine 0-Divisionen

ref class DivideByZeroFLOATException : ApplicationException {
public:
	DivideByZeroFLOATException() {}
	DivideByZeroFLOATException(String ^message) : ApplicationException(message)
	{}
};


ref class Taschenrechner : Form {
private:
	const int BUTTON_WIDTH = 40;
	const int BUTTON_HEIGHT = 40;
	const int BUTTON_SPACE = 10;			//Platz zwischen den Buttons

	const int TEXTBOX_WIDTH = ((BUTTON_WIDTH * 4) + (BUTTON_SPACE * 3));		//Breite der Textbox
	const int BUTTON_TOP_SPACE = (BUTTON_HEIGHT + BUTTON_SPACE);				//Abstand von der oberen Kante
	const int BUTTON_TOTAL_DISTANCE = (BUTTON_WIDTH + BUTTON_SPACE);			//Abstand zwischen den Ankerpunkten, total
	const int DRAWSIZE_WIDTH = ((BUTTON_WIDTH * 4) + (BUTTON_SPACE * 7));		//zwecks Optik 
	const int DRAWSIZE_HEIGHT = ((BUTTON_HEIGHT * 6) + (BUTTON_SPACE * 5));		//zwecks Optik

	String^ calculateOutput = "";	//fuer fortfuehrende Berechnungen
	bool flag = true;				//Feintuning, Ruecksetzung des Textfelds

	System::Windows::Forms::Button^ cmd_1;
	System::Windows::Forms::Button^ cmd_2;
	System::Windows::Forms::Button^ cmd_3;
	System::Windows::Forms::Button^ cmd_4;
	System::Windows::Forms::Button^ cmd_5;
	System::Windows::Forms::Button^ cmd_6;
	System::Windows::Forms::Button^ cmd_7;
	System::Windows::Forms::Button^ cmd_8;
	System::Windows::Forms::Button^ cmd_9;
	System::Windows::Forms::Button^ cmd_0;
	System::Windows::Forms::Button^ cmd_Addition;
	System::Windows::Forms::Button^ cmd_Subtraction;
	System::Windows::Forms::Button^ cmd_Multiplication;
	System::Windows::Forms::Button^ cmd_Division;
	System::Windows::Forms::Button^ cmd_Clear;
	System::Windows::Forms::Button^ cmd_Is;
	System::Windows::Forms::TextBox^ txt_Box;

public:
	Taschenrechner()
	{
		this->Size = System::Drawing::Size(DRAWSIZE_WIDTH, DRAWSIZE_HEIGHT);
		this->Text = "KlapperCalc";
	//	this->BackColor = System::Drawing::Color::Snow;

	//	this->KeyPreview = true;	//fuer Tastatureingaben, erstmal aus

		initComponents(); 
		float DivideFloatException(float _a, float _b);
		String^ calculate(String ^_input);
	
		void print();			//fuer interne Checks
		
	}
	
	//Buttondefinition
	void initComponents()	
	{
		// 8 - mittlerer, oberer Anker
		this->cmd_8 = gcnew System::Windows::Forms::Button();
		this->cmd_8->Text = "8";
		this->cmd_8->TabIndex = 8;
		this->cmd_8->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		this->cmd_8->Size = System::Drawing::Size(BUTTON_WIDTH, BUTTON_HEIGHT);
		this->cmd_8->Location = System::Drawing::Point(2*BUTTON_SPACE+BUTTON_WIDTH, BUTTON_TOP_SPACE);
		this->cmd_8->Click += gcnew System::EventHandler(this, &Taschenrechner::cmd_8_Click);
		this->cmd_8->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
		this->Controls->Add(this->cmd_8);

		// Textbox
		this->txt_Box = gcnew System::Windows::Forms::TextBox();
		this->txt_Box->Size = System::Drawing::Size(TEXTBOX_WIDTH, BUTTON_SPACE);
		this->txt_Box->Location = System::Drawing::Point(BUTTON_SPACE, BUTTON_SPACE);
		this->txt_Box->BackColor = System::Drawing::Color::WhiteSmoke;

		this->txt_Box->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14);
		this->txt_Box->Enabled = false;						//zum Verhindern von Eingaben in der Textbox
		this->Controls->Add(this->txt_Box);

		// 7
		this->cmd_7 = gcnew System::Windows::Forms::Button();
		this->cmd_7->Text = "7";
		this->cmd_7->TabIndex = 7;
		this->cmd_7->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		this->cmd_7->Size = System::Drawing::Size(BUTTON_WIDTH, BUTTON_HEIGHT);
		this->cmd_7->Location = System::Drawing::Point(BUTTON_SPACE, BUTTON_TOP_SPACE);
		this->cmd_7->Click += gcnew System::EventHandler(this, &Taschenrechner::cmd_7_Click);
		this->cmd_7->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
		this->Controls->Add(this->cmd_7);

		// 9
		this->cmd_9 = gcnew System::Windows::Forms::Button();
		this->cmd_9->Text = "9";
		this->cmd_9->TabIndex = 9;
		this->cmd_9->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		this->cmd_9->Size = System::Drawing::Size(BUTTON_WIDTH, BUTTON_HEIGHT);
		this->cmd_9->Location = System::Drawing::Point(3 * BUTTON_SPACE + 2*BUTTON_WIDTH, BUTTON_TOP_SPACE);
		this->cmd_9->Click += gcnew System::EventHandler(this, &Taschenrechner::cmd_9_Click);
		this->cmd_9->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
		this->Controls->Add(this->cmd_9);

		// +
		this->cmd_Addition = gcnew System::Windows::Forms::Button();
		this->cmd_Addition->Text = "+";
		this->cmd_Addition->TabIndex = 11;
		this->cmd_Addition->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		this->cmd_Addition->Size = System::Drawing::Size(BUTTON_WIDTH, BUTTON_HEIGHT);
		this->cmd_Addition->Location = System::Drawing::Point(4 * BUTTON_SPACE + 3 * BUTTON_WIDTH, BUTTON_TOP_SPACE);
		this->cmd_Addition->Click += gcnew System::EventHandler(this, &Taschenrechner::cmd_Addition_Click);
		this->cmd_8->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
		this->Controls->Add(this->cmd_Addition);

		// 4
		this->cmd_4 = gcnew System::Windows::Forms::Button();
		this->cmd_4->Text = "4";
		this->cmd_4->TabIndex = 4;
		this->cmd_4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		this->cmd_4->Size = System::Drawing::Size(BUTTON_WIDTH, BUTTON_HEIGHT);
		this->cmd_4->Location = System::Drawing::Point(BUTTON_SPACE, BUTTON_TOP_SPACE +BUTTON_HEIGHT+ BUTTON_SPACE);
		this->cmd_4->Click += gcnew System::EventHandler(this, &Taschenrechner::cmd_4_Click);
		this->cmd_4->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
		this->Controls->Add(this->cmd_4);

		// 5
		this->cmd_5 = gcnew System::Windows::Forms::Button();
		this->cmd_5->Text = "5";
		this->cmd_5->TabIndex = 5;
		this->cmd_5->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		this->cmd_5->Size = System::Drawing::Size(BUTTON_WIDTH, BUTTON_HEIGHT);
		this->cmd_5->Location = System::Drawing::Point(2 * BUTTON_SPACE + BUTTON_WIDTH , BUTTON_TOP_SPACE + BUTTON_HEIGHT + BUTTON_SPACE);
		this->cmd_5->Click += gcnew System::EventHandler(this, &Taschenrechner::cmd_5_Click);
		this->cmd_5->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
		this->Controls->Add(this->cmd_5);

		// 6
		this->cmd_6 = gcnew System::Windows::Forms::Button();
		this->cmd_6->Text = "6";
		this->cmd_6->TabIndex = 6;
		this->cmd_6->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		this->cmd_6->Size = System::Drawing::Size(BUTTON_WIDTH, BUTTON_HEIGHT);
		this->cmd_6->Location = System::Drawing::Point(3 * BUTTON_SPACE + 2 * BUTTON_WIDTH, BUTTON_TOP_SPACE + BUTTON_HEIGHT + BUTTON_SPACE);
		this->cmd_6->Click += gcnew System::EventHandler(this, &Taschenrechner::cmd_6_Click);
		this->cmd_6->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
		this->Controls->Add(this->cmd_6);

		// -
		this->cmd_Subtraction = gcnew System::Windows::Forms::Button();
		this->cmd_Subtraction->Text = "-";
		this->cmd_Subtraction->TabIndex = 12;
		this->cmd_Subtraction->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		this->cmd_Subtraction->Size = System::Drawing::Size(BUTTON_WIDTH, BUTTON_HEIGHT);
		this->cmd_Subtraction->Location = System::Drawing::Point(4 * BUTTON_SPACE + 3 * BUTTON_WIDTH, BUTTON_TOP_SPACE + BUTTON_HEIGHT + BUTTON_SPACE);
		this->cmd_Subtraction->Click += gcnew System::EventHandler(this, &Taschenrechner::cmd_Subtraction_Click);
		this->cmd_Subtraction->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
		this->Controls->Add(this->cmd_Subtraction);

		// 1
		this->cmd_1 = gcnew System::Windows::Forms::Button();
		this->cmd_1->Text = "1";
		this->cmd_1->TabIndex = 1;
		this->cmd_1->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		this->cmd_1->Size = System::Drawing::Size(BUTTON_WIDTH, BUTTON_HEIGHT);
		this->cmd_1->Location = System::Drawing::Point(BUTTON_SPACE, BUTTON_TOP_SPACE + 2 * BUTTON_HEIGHT + 2 * BUTTON_SPACE);
		this->cmd_1->Click += gcnew System::EventHandler(this, &Taschenrechner::cmd_1_Click);
		this->cmd_1->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
		this->Controls->Add(this->cmd_1);

		// 2
		this->cmd_2 = gcnew System::Windows::Forms::Button();
		this->cmd_2->Text = "2";
		this->cmd_2->TabIndex = 2;
		this->cmd_2->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		this->cmd_2->Size = System::Drawing::Size(BUTTON_WIDTH, BUTTON_HEIGHT);
		this->cmd_2->Location = System::Drawing::Point(2 * BUTTON_SPACE + BUTTON_WIDTH, BUTTON_TOP_SPACE + 2 * BUTTON_HEIGHT + 2 * BUTTON_SPACE);
		this->cmd_2->Click += gcnew System::EventHandler(this, &Taschenrechner::cmd_2_Click);
		this->cmd_2->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
		this->Controls->Add(this->cmd_2);

		// 3
		this->cmd_3 = gcnew System::Windows::Forms::Button();
		this->cmd_3->Text = "3";
		this->cmd_3->TabIndex = 3;
		this->cmd_3->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		this->cmd_3->Size = System::Drawing::Size(BUTTON_WIDTH, BUTTON_HEIGHT);
		this->cmd_3->Location = System::Drawing::Point(3 * BUTTON_SPACE + 2 * BUTTON_WIDTH, BUTTON_TOP_SPACE + 2 * BUTTON_HEIGHT + 2 * BUTTON_SPACE);
		this->cmd_3->Click += gcnew System::EventHandler(this, &Taschenrechner::cmd_3_Click);
		this->cmd_3->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
		this->Controls->Add(this->cmd_3);

		// *
		this->cmd_Multiplication = gcnew System::Windows::Forms::Button();
		this->cmd_Multiplication->Text = "*";
		this->cmd_Multiplication->TabIndex = 13;
		this->cmd_Multiplication->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		this->cmd_Multiplication->Size = System::Drawing::Size(BUTTON_WIDTH, BUTTON_HEIGHT);
		this->cmd_Multiplication->Location = System::Drawing::Point(4 * BUTTON_SPACE + 3 * BUTTON_WIDTH, BUTTON_TOP_SPACE + 2*BUTTON_HEIGHT + 2*BUTTON_SPACE);
		this->cmd_Multiplication->Click += gcnew System::EventHandler(this, &Taschenrechner::cmd_Multiplication_Click);
		this->cmd_Multiplication->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
		this->Controls->Add(this->cmd_Multiplication);

		//? MouseEnter/Leave - hier waere ein Verweis auf eine einzige globale Einfaerbeaktion geil, geht das?
		// Clear
		this->cmd_Clear = gcnew System::Windows::Forms::Button();
		this->cmd_Clear->Text = "C";
		this->cmd_Clear->TabIndex = 16;
		this->cmd_Clear->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		this->cmd_Clear->Size = System::Drawing::Size(BUTTON_WIDTH, BUTTON_HEIGHT);
		this->cmd_Clear->Location = System::Drawing::Point(BUTTON_SPACE, BUTTON_TOP_SPACE + 3 * BUTTON_HEIGHT + 3 * BUTTON_SPACE);
		this->cmd_Clear->Click += gcnew System::EventHandler(this, &Taschenrechner::cmd_Clear_Click);
		this->cmd_Clear->MouseLeave += gcnew System::EventHandler(this, &Taschenrechner::cmd_Clear_MouseLeave);
		this->cmd_Clear->MouseEnter += gcnew System::EventHandler(this, &Taschenrechner::cmd_Clear_MouseEnter);
		this->cmd_Clear->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
		this->Controls->Add(this->cmd_Clear);

		// 0
		this->cmd_0 = gcnew System::Windows::Forms::Button();
		this->cmd_0->Text = "0";
		this->cmd_0->TabIndex = 10;
		this->cmd_0->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		this->cmd_0->Size = System::Drawing::Size(BUTTON_WIDTH, BUTTON_HEIGHT);
		this->cmd_0->Location = System::Drawing::Point(2 * BUTTON_SPACE + BUTTON_WIDTH, BUTTON_TOP_SPACE + 3 * BUTTON_HEIGHT + 3 * BUTTON_SPACE);
		this->cmd_0->Click += gcnew System::EventHandler(this, &Taschenrechner::cmd_0_Click);
		this->cmd_0->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
		this->Controls->Add(this->cmd_0);

		// =
		this->cmd_Is = gcnew System::Windows::Forms::Button();
		this->cmd_Is->Text = "=";
		this->cmd_Is->TabIndex = 15;
		this->cmd_Is->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		this->cmd_Is->Size = System::Drawing::Size(BUTTON_WIDTH, BUTTON_HEIGHT);
		this->cmd_Is->Location = System::Drawing::Point(3 * BUTTON_SPACE + 2*BUTTON_WIDTH, BUTTON_TOP_SPACE + 3 * BUTTON_HEIGHT + 3 * BUTTON_SPACE);
		this->cmd_Is->Click += gcnew System::EventHandler(this, &Taschenrechner::cmd_Is_Click);
		this->cmd_Is->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
		this->Controls->Add(this->cmd_Is);

		// /
		this->cmd_Division = gcnew System::Windows::Forms::Button();
		this->cmd_Division->Text = "/";
		this->cmd_Division->TabIndex = 14;
		this->cmd_Division->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
		this->cmd_Division->Size = System::Drawing::Size(BUTTON_WIDTH, BUTTON_HEIGHT);
		this->cmd_Division->Location = System::Drawing::Point(4 * BUTTON_SPACE + 3*BUTTON_WIDTH, BUTTON_TOP_SPACE + 3 * BUTTON_HEIGHT + 3 * BUTTON_SPACE);
		this->cmd_Division->Click += gcnew System::EventHandler(this, &Taschenrechner::cmd_Division_Click);
		this->cmd_Division->Font = gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12);
		this->Controls->Add(this->cmd_Division);

	}
	
#pragma region Eventhandler


	//1
		System::Void cmd_1_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (flag == false) {		// setze textfeld zurueck wenn berechnet wurde
				this->txt_Box->Clear();
				flag = true;
			}
			Console::WriteLine(this->cmd_1->Text);			//Kontrolle
			this->txt_Box->Text += this->cmd_1->Text;
		}

	//2
		System::Void cmd_2_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (flag == false) {		// setze textfeld zurueck wenn berechnet wurde
				this->txt_Box->Clear();
				flag = true;
			}
			Console::WriteLine(this->cmd_2->Text);			//Kontrolle
			this->txt_Box->Text += this->cmd_2->Text;
		}

	//3
		System::Void cmd_3_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (flag == false) {		// setze textfeld zurueck wenn berechnet wurde
				this->txt_Box->Clear();
				flag = true;
			}
			Console::WriteLine(this->cmd_3->Text);			//Kontrolle
			this->txt_Box->Text += this->cmd_3->Text;
		}

	//4
		System::Void cmd_4_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (flag == false) {		// setze textfeld zurueck wenn berechnet wurde
				this->txt_Box->Clear();
				flag = true;
			}
			Console::WriteLine(this->cmd_4->Text);			//Kontrolle
			this->txt_Box->Text += this->cmd_4->Text;
		}

	//5
		System::Void cmd_5_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (flag == false) {		// setze textfeld zurueck wenn berechnet wurde
				this->txt_Box->Clear();
				flag = true;
			}
			Console::WriteLine(this->cmd_5->Text);			//Kontrolle
			this->txt_Box->Text += this->cmd_5->Text;
		}

	//6
		System::Void cmd_6_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (flag == false) {		// setze textfeld zurueck wenn berechnet wurde
				this->txt_Box->Clear();
				flag = true;
			}
			Console::WriteLine(this->cmd_6->Text);			//Kontrolle
			this->txt_Box->Text += this->cmd_6->Text;
		}

	//7
		System::Void cmd_7_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (flag == false) {		// setze textfeld zurueck wenn berechnet wurde
				this->txt_Box->Clear();
				flag = true;
			}
			Console::WriteLine(this->cmd_7->Text);
			this->txt_Box->Text += this->cmd_7->Text;	//Text des Buttons ins Textfeld schieben
		}

	//8
		System::Void cmd_8_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (flag == false) {		// setze textfeld zurueck wenn berechnet wurde
				this->txt_Box->Clear();
				flag = true;
			}
			Console::WriteLine(this->cmd_8->Text);			//Kontrolle
			this->txt_Box->Text += this->cmd_8->Text;
		}

	//9
		System::Void cmd_9_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (flag == false) {		// setze textfeld zurueck wenn berechnet wurde
				this->txt_Box->Clear();
				flag = true;
			}
			Console::WriteLine(this->cmd_9->Text);			//Kontrolle
			this->txt_Box->Text += this->cmd_9->Text;
		}

	//0
		System::Void cmd_0_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (flag == false) {		// setze textfeld zurueck wenn berechnet wurde
				this->txt_Box->Clear();
				flag = true;
			}
			Console::WriteLine(this->cmd_0->Text);			//Kontrolle
			this->txt_Box->Text += this->cmd_0->Text;
		}

	//+
		System::Void cmd_Addition_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (flag == false) {		//! fahre mit ergebnis der letzten berechnung fort
				this->txt_Box->Text = calculateOutput;	
				this->txt_Box->Text += this->cmd_Addition->Text;
				flag = true;
			}
			else {
				Console::WriteLine(this->cmd_Addition->Text);			//Kontrolle
				this->txt_Box->Text += this->cmd_Addition->Text;
				flag = true;
			}
		}

	//-
		System::Void cmd_Subtraction_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (flag == false) {		//! fahre mit ergebnis der letzten berechnung fort
				this->txt_Box->Text = calculateOutput;
				this->txt_Box->Text += this->cmd_Subtraction->Text;
				flag = true;
			}
			else {
				Console::WriteLine(this->cmd_Subtraction->Text);			//Kontrolle
				this->txt_Box->Text += this->cmd_Subtraction->Text;
			}
		}

	//*
		System::Void cmd_Multiplication_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (flag == false) {		//! fahre mit ergebnis der letzten berechnung fort
				this->txt_Box->Text = calculateOutput;
				this->txt_Box->Text += this->cmd_Multiplication->Text;
				flag = true;
			}
			else {
				Console::WriteLine(this->cmd_Multiplication->Text);			//Kontrolle
				this->txt_Box->Text += this->cmd_Multiplication->Text;
			}
		}

	// /
		System::Void cmd_Division_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (flag == false) {		//! fahre mit ergebnis der letzten berechnung fort
				this->txt_Box->Text = calculateOutput;
				this->txt_Box->Text += this->cmd_Division->Text;
				flag = true;
			}
			else {
				Console::WriteLine(this->cmd_Division->Text);			//Kontrolle
				this->txt_Box->Text += this->cmd_Division->Text;
			}
		}

	// =
		System::Void cmd_Is_Click(System::Object^ sender, System::EventArgs^ e)
		{
			calculateOutput = this->calculate(this->txt_Box->Text);							//inhalt des textfeldes in den String schieben
			Console::WriteLine("calculateOutput {0}, flag {1}", calculateOutput, flag);		//Kontrolle
			Console::WriteLine(this->txt_Box->Text);										//Kontrolle
			flag = false;
		}

	// Clear  -  Mehrere Events
		System::Void cmd_Clear_Click(System::Object^ sender, System::EventArgs^ e)
		{
			this->txt_Box->Clear();								//Textfeld leeren
			this->cmd_Clear->BackColor = System::Drawing::Color::Transparent;
			this->txt_Box->BackColor = System::Drawing::Color::WhiteSmoke;

			printCoordinates();									//gib koordinaten und werte der buttons aus
			Console::WriteLine(this->cmd_Clear->Text);			//Kontrolle
		}

		System::Void cmd_Clear_MouseEnter(System::Object^ sender, System::EventArgs^ e)
		{
			this->cmd_Clear->BackColor = System::Drawing::Color::LightBlue;
			Console::WriteLine(this->cmd_Clear->BackColor);
		}

		System::Void cmd_Clear_MouseLeave(System::Object^ sender, System::EventArgs^ e)
		{
			this->cmd_Clear->BackColor = System::Drawing::Color::Transparent;
		}




#pragma endregion
	
	//Division durch Null bei float
	float DivideFloatException(float _a, float _b) {
		if (_b != 0) {
			return _a / _b;
		}
		else {
			throw gcnew DivideByZeroFLOATException();
		}
	}
	

	//String des Textfeldes wird nach erstem Operanden durchsucht, aktion je nach dem
	String^ Taschenrechner::calculate(String ^_input) {
		
		bool ifAllFails = true;						//abfangen von mehrfachoperanden
		bool booladdition = _input->Contains("+"); 
		bool boolsubtraction = _input->Contains("-");
		bool boolmultiplication = _input->Contains("*");
		bool booldivision = _input->Contains("/"); 

		if (booladdition) {
			Console::WriteLine("enter booladdition");
			float position1 = _input->IndexOf('+');	//gehe zur position des +
			String^ addString1 = _input->Substring(0, position1);
			String^ addString2 = _input->Substring(position1 + 1);
			float a, b;
			if ((float::TryParse(addString1, a)) && float::TryParse(addString2, b)){
				Console::WriteLine("Addition: {0}", a + b);
				float result = a + b;
				this->txt_Box->Text = _input + " = " + result.ToString();
				Console::WriteLine("Addition: {0}", flag);
				return result.ToString();		//wird von fortfuehrendem berechnen aufgegriffen
				ifAllFails = false;
				}
			else {
				Console::WriteLine("enter booladdition else");
				this->txt_Box->Clear();
				ifAllFails = false;
			}
		}

		if (boolsubtraction) {
			Console::WriteLine("enter boolsubtraction");
			float position1 = _input->IndexOf('-');	//gehe zur position des -
			String^ addString1 = _input->Substring(0, position1);
			String^ addString2 = _input->Substring(position1 + 1);
			float a, b;
			if ((float::TryParse(addString1, a)) && float::TryParse(addString2, b)) {
				Console::WriteLine("Subtraction: {0}", a - b);
				float result = a - b;
				this->txt_Box->Text = _input + " = " + result.ToString();
				Console::WriteLine("Subtraction: {0}", flag);
				return result.ToString();		//wird von fortfuehrendem berechnen aufgegriffen
				ifAllFails = false;
			}
			else {
				Console::WriteLine("enter boolsubtraction else");
				this->txt_Box->Clear();
				ifAllFails = false;
			}
		}

		if (boolmultiplication) {
			Console::WriteLine("enter boolmultiplication");
			float position1 = _input->IndexOf('*');	//gehe zur position des *
			String^ addString1 = _input->Substring(0, position1);
			String^ addString2 = _input->Substring(position1 + 1);
			float a, b;
			if ((float::TryParse(addString1, a)) && float::TryParse(addString2, b)) {
				Console::WriteLine("Multiplication: {0}", a * b);
				float result = a * b;
				this->txt_Box->Text = _input + " = " + result.ToString();
				Console::WriteLine("Multiplication: {0}", flag);
				return result.ToString();		//wird von fortfuehrendem berechnen aufgegriffen
				ifAllFails = false;
			}
			else {
				Console::WriteLine("enter boolmultiplication else");
				this->txt_Box->Clear();
				ifAllFails = false;

			}
		}

		if (booldivision) {
			Console::WriteLine("enter booldivision");
			float position1 = _input->IndexOf('/');	//gehe zur position des /
			String^ addString1 = _input->Substring(0, position1);
			String^ addString2 = _input->Substring(position1 + 1);
			float a, b;
			if ((float::TryParse(addString1, a)) && float::TryParse(addString2, b)) {
				try {
					Console::WriteLine("Division: {0}", a / b);
					float result = DivideFloatException(a, b);		//hier funktionsaufruf der eigenen exception
					this->txt_Box->Text = _input + " = " + result.ToString();
					Console::WriteLine("Division: {0}", flag);
					return result.ToString();						//wird von fortfuehrendem berechnen aufgegriffen
				}
				catch (DivideByZeroFLOATException ^e) {				//normale int-pruefung ueberfluessig
					this->txt_Box->Text = "Nein.  /0";
		//			this->txt_Box->BackColor = System::Drawing::Color::Red;
					this->cmd_Clear->BackColor = System::Drawing::Color::Green;
					ifAllFails = false;
				}
				catch (Exception ^e) {
					this->txt_Box->Text = "Was auch immer.";
					this->cmd_Clear->BackColor = System::Drawing::Color::Green;
					ifAllFails = false;
				}
			}
			else {
				Console::WriteLine("enter booldivision else");
				this->txt_Box->Clear();
				ifAllFails = false;
			}
		}

		if (booladdition == false && booldivision == false && boolmultiplication == false && booldivision == false) {
			Console::WriteLine("keine Rechenoperation, flag {0}", flag);
			String^ addString1 = _input;
				return _input;					//wird von fortfuehrendem berechnen aufgegriffen
				this->txt_Box->Text = _input;
				ifAllFails = false;
		}
		if (ifAllFails) {		//abfangen von mehrfachoperanden
			this->txt_Box->Text = "alles kaputt.";
			this->cmd_Clear->BackColor = System::Drawing::Color::Green;
			Console::WriteLine("allFailed: {0}", flag);
			Console::WriteLine();
		}
	}

	//Positionscheck 
	void Taschenrechner::printCoordinates() {
		Console::WriteLine();
		Console::WriteLine("BUTTON_WIDTH {0}", BUTTON_WIDTH);
		Console::WriteLine("BUTTON_HEIGHT {0}", BUTTON_HEIGHT);
		Console::WriteLine("BUTTON_SPACE {0}", BUTTON_SPACE);
		Console::WriteLine("TEXTBOX_WIDTH {0}", TEXTBOX_WIDTH);
		Console::WriteLine("BUTTON_TOP_SPACE {0}", BUTTON_TOP_SPACE);
		Console::WriteLine("BUTTON_TOTAL_DISTANCE {0}", BUTTON_TOTAL_DISTANCE);
		Console::WriteLine("DRAWSIZE_WIDTH {0}", DRAWSIZE_WIDTH);
		Console::WriteLine("DRAWSIZE_HEIGHT {0}", DRAWSIZE_HEIGHT);
		Console::WriteLine("Ankerpunkt der 8: {0}", (DRAWSIZE_WIDTH - BUTTON_WIDTH) / 2);
		Console::WriteLine();
	}
};


int main(array<System::String ^> ^args)
{
	Application::Run(gcnew Taschenrechner());
	return 0;
}
