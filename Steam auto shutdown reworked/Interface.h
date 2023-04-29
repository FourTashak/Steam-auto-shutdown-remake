#pragma once
#include "Functions.h"

namespace Steamautoshutdownreworked {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	std::string Steampath;
	std::vector<std::string> LibraryPaths;
	std::vector<std::string> AppStateFlags;

	public ref class Interface : public System::Windows::Forms::Form
	{
	public:
		Interface(void)
		{
			InitializeComponent();
			Steampath = GetSteamPath();
			GetLibraryPaths(Steampath,LibraryPaths);
		}

	protected:
		~Interface()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ Enable_btn;
	protected:
	private: System::Windows::Forms::Button^ Cancel_Sch_btn;
	private: System::ComponentModel::BackgroundWorker^ Worker1;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->Enable_btn = (gcnew System::Windows::Forms::Button());
			this->Cancel_Sch_btn = (gcnew System::Windows::Forms::Button());
			this->Worker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->SuspendLayout();
			// 
			// Enable_btn
			// 
			this->Enable_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Enable_btn->Location = System::Drawing::Point(54, 12);
			this->Enable_btn->Name = L"Enable_btn";
			this->Enable_btn->Size = System::Drawing::Size(260, 95);
			this->Enable_btn->TabIndex = 0;
			this->Enable_btn->Text = L"Enable Auto Shutdown";
			this->Enable_btn->UseVisualStyleBackColor = true;
			this->Enable_btn->Click += gcnew System::EventHandler(this, &Interface::Enable_btn_Click);
			// 
			// Cancel_Sch_btn
			// 
			this->Cancel_Sch_btn->Location = System::Drawing::Point(132, 281);
			this->Cancel_Sch_btn->Name = L"Cancel_Sch_btn";
			this->Cancel_Sch_btn->Size = System::Drawing::Size(106, 70);
			this->Cancel_Sch_btn->TabIndex = 1;
			this->Cancel_Sch_btn->Text = L"Cancel Scheduled Shutdown";
			this->Cancel_Sch_btn->UseVisualStyleBackColor = true;
			this->Cancel_Sch_btn->Click += gcnew System::EventHandler(this, &Interface::Cancel_Sch_btn_Click);
			// 
			// Worker1
			// 
			this->Worker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Interface::Worker1_DoWork);
			// 
			// Interface
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(370, 378);
			this->Controls->Add(this->Cancel_Sch_btn);
			this->Controls->Add(this->Enable_btn);
			this->Name = L"Interface";
			this->Text = L"Interface";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Enable_btn_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		StoreStateFlagInfo(LibraryPaths,AppStateFlags);
		Worker1->RunWorkerAsync();
	}
	private: System::Void Cancel_Sch_btn_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		system("shutdown -a");
	}
	private: System::Void Worker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) 
	{
		CheckStateFlags(AppStateFlags);
	}
	};
}
