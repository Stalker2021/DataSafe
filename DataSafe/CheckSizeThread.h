#pragma once

using namespace System;

// TODO: should be renamed to Calculation or something
ref class CheckSize
{
public:
	CheckSize(System::IO::StreamReader^ config, System::Windows::Forms::Label^ lable);

	void startProcess();
	void stopProcess();
	bool isRun();
	unsigned long long int getSize();

private:
	void checkDataSize();
	void checkSubFolderSize(System::String^ checkPath);
	void putLableTextSize();

private:
	System::Threading::Thread^ checkDataSizeThread = nullptr;
	System::Windows::Forms::Label^ sizeLable = nullptr;			//for indicate count of calculated files
	System::IO::StreamReader^ configFile = nullptr;
	bool inProgress = false;
	unsigned long long int counter = 0;
};