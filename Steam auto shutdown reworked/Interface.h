#pragma once
#include "Functions.h"
#include <msclr/marshal_cppstd.h>

namespace Steamautoshutdownreworked {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	std::string Steampath;
	std::vector<std::string> LibraryPaths;
	std::vector<Games> AppStateFlags;
	bool EnableDis = false;

	public ref class Interface : public System::Windows::Forms::Form
	{
	public:
		Interface(void)
		{
			InitializeComponent();
			Steampath = GetSteamPath();
			Enable_btn->BackColor = Color::Red;
			if(Steampath != "error")
			{
				GetLibraryPaths(Steampath, LibraryPaths);
			}
			else if (Steampath == "error")
			{
				MessageBox::Show("Steam installation path is not valid, please use the select directory button to fix the issue");
			}
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
	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::ComponentModel::BackgroundWorker^ Worker2;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowserDialog1;
	private: System::Windows::Forms::Button^ DirSelect_btn;



	private:
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		void InitializeComponent(void)
		{
			this->Enable_btn = (gcnew System::Windows::Forms::Button());
			this->Cancel_Sch_btn = (gcnew System::Windows::Forms::Button());
			this->Worker1 = (gcnew System::ComponentModel::BackgroundWorker());
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->Worker2 = (gcnew System::ComponentModel::BackgroundWorker());
			this->folderBrowserDialog1 = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->DirSelect_btn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// Enable_btn
			// 
			this->Enable_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 13.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->Enable_btn->Location = System::Drawing::Point(57, 180);
			this->Enable_btn->Name = L"Enable_btn";
			this->Enable_btn->Size = System::Drawing::Size(260, 95);
			this->Enable_btn->TabIndex = 0;
			this->Enable_btn->Text = L"Enable Auto Shutdown";
			this->Enable_btn->UseVisualStyleBackColor = true;
			this->Enable_btn->Click += gcnew System::EventHandler(this, &Interface::Enable_btn_Click);
			// 
			// Cancel_Sch_btn
			// 
			this->Cancel_Sch_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->Cancel_Sch_btn->Location = System::Drawing::Point(57, 296);
			this->Cancel_Sch_btn->Name = L"Cancel_Sch_btn";
			this->Cancel_Sch_btn->Size = System::Drawing::Size(106, 70);
			this->Cancel_Sch_btn->TabIndex = 1;
			this->Cancel_Sch_btn->Text = L"Cancel Scheduled Shutdown";
			this->Cancel_Sch_btn->UseVisualStyleBackColor = true;
			this->Cancel_Sch_btn->Click += gcnew System::EventHandler(this, &Interface::Cancel_Sch_btn_Click);
			// 
			// Worker1
			// 
			this->Worker1->WorkerSupportsCancellation = true;
			this->Worker1->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Interface::Worker1_DoWork);
			// 
			// listBox1
			// 
			this->listBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->listBox1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 24;
			this->listBox1->Location = System::Drawing::Point(12, 27);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(346, 98);
			this->listBox1->TabIndex = 2;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &Interface::listBox1_SelectedIndexChanged);
			// 
			// Worker2
			// 
			this->Worker2->WorkerSupportsCancellation = true;
			this->Worker2->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Interface::Worker2_DoWork);
			// 
			// DirSelect_btn
			// 
			this->DirSelect_btn->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12));
			this->DirSelect_btn->Location = System::Drawing::Point(216, 296);
			this->DirSelect_btn->Name = L"DirSelect_btn";
			this->DirSelect_btn->Size = System::Drawing::Size(101, 70);
			this->DirSelect_btn->TabIndex = 3;
			this->DirSelect_btn->Text = L"Select Directory";
			this->DirSelect_btn->UseVisualStyleBackColor = true;
			this->DirSelect_btn->Click += gcnew System::EventHandler(this, &Interface::DirSelect_btn_Click);
			// 
			// Interface
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(370, 378);
			this->Controls->Add(this->DirSelect_btn);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->Cancel_Sch_btn);
			this->Controls->Add(this->Enable_btn);
			this->Name = L"Interface";
			this->Text = L"Interface";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void Enable_btn_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		AppStateFlags.clear();
		if(Steampath != "error")
		{
			do
			{
				if (EnableDis == false)
				{
					StoreStateFlagInfo(LibraryPaths, AppStateFlags);
					EnableDis = !EnableDis;
					Enable_btn->BackColor = Color::Green;
					Worker1->RunWorkerAsync();
					continue;
				}
				if (EnableDis == true)
				{
					Worker1->CancelAsync();
					Worker2->CancelAsync();
					EnableDis = !EnableDis;
					Enable_btn->BackColor = Color::Red;
					continue;
				}
			} while (false);
		}
		else if (Steampath == "error")
		{
			MessageBox::Show("Please use the select directory button and try again");
		}
	}
	private: System::Void Cancel_Sch_btn_Click(System::Object^ sender, System::EventArgs^ e) 
	{
		system("shutdown -a");
	}
	private: System::Void Worker1_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) 
	{
		Worker2->RunWorkerAsync();
		CheckStateFlags(AppStateFlags, EnableDis);
	}

	private: void UpdateList()
	{
		if(EnableDis == true)
		{
			array<System::Object^>^ NameList = gcnew array<System::Object^>(AppStateFlags.size());
			for (int i = 0; i < NameList->Length; i++)
			{
				NameList[i] = gcnew System::String(AppStateFlags[i].Name.c_str());
			}
			listBox1->Items->Clear();
			listBox1->Items->AddRange(NameList);
		}

		else
		{
			listBox1->Items->Clear();
		}
	}

	private: System::Void Worker2_DoWork(System::Object^ sender, System::ComponentModel::DoWorkEventArgs^ e) 
	{
		while (true)
		{
			if (EnableDis == false)
			{
				this->Invoke(gcnew MethodInvoker(this, &Interface::UpdateList));
				break;
			}

			if (listBox1->InvokeRequired)
				this->Invoke(gcnew MethodInvoker(this, &Interface::UpdateList));
			else
				UpdateList();

			Sleep(50);
		}
	}
	private: std::string SelectFolder()
	{
		FolderBrowserDialog^ FBD = gcnew FolderBrowserDialog();
		FBD->Description = "Steam installation path is not valid, please enter a valid path";
		FBD->RootFolder = Environment::SpecialFolder::MyComputer;
		FBD->ShowNewFolderButton = false;

		System::Windows::Forms::DialogResult result = FBD->ShowDialog();

		if (result == System::Windows::Forms::DialogResult::OK)
		{
			std::string Converted = msclr::interop::marshal_as<std::string>(FBD->SelectedPath);
			return Converted;
		}
		else
		{
			return "error";
		}
	}
	private: System::Void DirSelect_btn_Click(System::Object^ sender, System::EventArgs^ e)
	{
		do
		{
			Steampath = SelectFolder();
			if (Steampath != "error")
			{
				if (!GetLibraryPaths(Steampath, LibraryPaths))
				{
					Steampath = "error";
					MessageBox::Show("Steam installation path is not valid, please enter a valid path");
				}
			}
		} while (Steampath == "error");
	}
	private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) 
	{
	}
};
}
