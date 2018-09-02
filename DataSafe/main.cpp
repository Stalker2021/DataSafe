#include "MainForm.h"

using DataSafe::MainForm;

[System::STAThread]
int main()
{
	MainForm^ window = gcnew MainForm();
	window->ShowDialog();
	return 0;
}