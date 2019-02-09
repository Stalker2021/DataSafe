#include "MainForm.h"

using DataSafe::MainForm;

[System::STAThread]
int WinMain()
{
	MainForm^ window = gcnew MainForm();
	window->ShowDialog();
	return 0;
}