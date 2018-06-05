// RELEASE_1.0:	27.02.2016
//
// UPDATE_1.1:	19.12.2016
//				-add Back Checking (from Safe to Data)
//				-fixed Deleting Files
//
// Need Fix:	-add sound signals
//				-add indication of file on checking
//
#include "MainForm.h"

using DataSafe::MainForm;

[System::STAThread]
int main()
{
	MainForm^ window = gcnew MainForm();
	window->ShowDialog();
	return 0;
}