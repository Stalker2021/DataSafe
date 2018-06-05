#pragma once

using namespace System;

ref class CheckSize
{
public:
	bool isRun();
	void startProcess();
	void stopProcess();
	double getSize();

	CheckSize(System::IO::StreamReader^ config, System::Windows::Forms::Label^ lable);

private:
	System::Threading::Thread^ checkDataSizeThread = nullptr;
	System::Windows::Forms::Label^ sizeLable = nullptr;
	System::IO::StreamReader^ configFile = nullptr;
	bool inProgress = false;
	double size = 0.0;

	void checkDataSize();
	void checkSubFolderSize(System::String^ checkPath);
	void putLableTextSize();
};