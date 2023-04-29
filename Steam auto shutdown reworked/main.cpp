#include "Interface.h"


using namespace System;
using namespace System::Windows::Forms;

[STAThread]
void main(array<String^>^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	Steamautoshutdownreworked::Interface form;
	Application::Run(% form);
}