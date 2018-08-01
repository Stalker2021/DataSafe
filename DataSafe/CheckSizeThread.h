#pragma once

using namespace System;

ref class CheckSize
{
public:
	bool isRun();
	void startProcess();
	void stopProcess();
	unsigned long long int getSize();

	CheckSize(System::IO::StreamReader^ config, System::Windows::Forms::Label^ lable);

private:
	System::Threading::Thread^ checkDataSizeThread = nullptr;
	System::Windows::Forms::Label^ sizeLable = nullptr;
	System::IO::StreamReader^ configFile = nullptr;
	bool inProgress = false;
	unsigned long long int counter = 0;

	void checkDataSize();
	void checkSubFolderSize(System::String^ checkPath);
	void putLableTextSize();
};