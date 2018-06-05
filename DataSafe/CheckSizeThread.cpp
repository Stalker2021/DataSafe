#include "CheckSizeThread.h"

using System::Windows::Forms::MessageBox;
using System::Threading::Thread;

CheckSize::CheckSize(System::IO::StreamReader^ config, System::Windows::Forms::Label^ lable)
{
	if (!lable || !config)
		return;
	sizeLable = lable;
	configFile = config;
}

void CheckSize::checkDataSize()
{
	inProgress = true;
	System::IO::DirectoryInfo^ dirInfo;
	System::IO::FileInfo^ fileInfo;
	String^ buffPath;
	wchar_t buffType;
	while (true)
	{
		buffPath = configFile->ReadLine();
		if (!buffPath || buffPath == "")
			break;
		buffType = buffPath[buffPath->Length - 1];
		if (buffType == '\\' || buffType == '/')
		{
			dirInfo = gcnew System::IO::DirectoryInfo(buffPath);
			if (!dirInfo->Exists)
			{
				MessageBox::Show("Directory \"" + buffPath + "\" not exist!", "Error",
					System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
				return;
			}
			for (int iter = 0; iter < dirInfo->GetFiles()->Length; iter++)
			{
				size += double(dirInfo->GetFiles()[iter]->Length) / 1024.0 / 1024.0;
				putLableTextSize();
			}
		}
		else if (buffType == '+')
		{
			dirInfo = gcnew System::IO::DirectoryInfo(buffPath->Remove(buffPath->Length - 1));
			if (!dirInfo->Exists)
			{
				MessageBox::Show("Directory \"" + dirInfo->ToString() + "\" not exist!", "Error",
					System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
				return;
			}

			checkSubFolderSize(dirInfo->ToString());
		}
		else
		{
			fileInfo = gcnew System::IO::FileInfo(buffPath);
			if (!fileInfo->Exists)
			{
				MessageBox::Show("File \"" + fileInfo->ToString() + "\" not exist!", "Error",
					System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
				return;
			}
			size += double(fileInfo->Length) / 1024.0 / 1024.0;
			putLableTextSize();
		}
		configFile->ReadLine();
	}

	inProgress = false;
	putLableTextSize();
}

bool CheckSize::isRun()
{
	return inProgress;
}

void CheckSize::startProcess()
{
	if (!sizeLable || !configFile)
		return;
	size = 0.0;

	checkDataSizeThread = gcnew Thread(gcnew System::Threading::ThreadStart(this, &CheckSize::checkDataSize));
	checkDataSizeThread->Start();
}

void CheckSize::stopProcess()
{
	inProgress = false;
	checkDataSizeThread->Abort();
	size = 0.0;
}

void CheckSize::checkSubFolderSize(System::String^ checkPath)
{
	if (checkPath[checkPath->Length - 1] != '/' && checkPath[checkPath->Length - 1] != '\\')
		checkPath += "\\";

	System::IO::DirectoryInfo dirInfo(checkPath);

	for (int iter = 0; iter < dirInfo.GetDirectories()->Length; iter++)
		checkSubFolderSize(dirInfo.ToString() + dirInfo.GetDirectories()[iter]->ToString() + "\\");

	for (int iter = 0; iter < dirInfo.GetFiles()->Length; iter++)
	{
		size += double(dirInfo.GetFiles()[iter]->Length) / 1024.0 / 1024.0;
		putLableTextSize();
	}
}

void CheckSize::putLableTextSize()
{
	if (inProgress)
		sizeLable->Text = "Calculation: " + size.ToString("F2") + " (MB)";
	else
		sizeLable->Text = "0,00 / " + size.ToString("F2") + " (MB)";
}

double CheckSize::getSize()
{
	return size;
}