#include "CheckSizeThread.h"
#include "Defines.h"

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
		if (!buffPath || buffPath == EMPTY_STRING)
			break;
		buffType = buffPath[buffPath->Length - 1];
		if (buffType == '\\' || buffType == '/')
		{
			dirInfo = gcnew System::IO::DirectoryInfo(buffPath);
			if (!dirInfo->Exists)
			{
				MessageBox::Show (MESSAGE_TEXT_DIR_NEXIST( buffPath ), MESSAGE_TITLE_ERROR,
					System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
				return;
			}

			counter += dirInfo->GetFiles()->Length;
			putLableTextSize();
		}
		else if (buffType == '+')
		{
			dirInfo = gcnew System::IO::DirectoryInfo(buffPath->Remove(buffPath->Length - 1));
			if (!dirInfo->Exists)
			{
				MessageBox::Show( MESSAGE_TEXT_DIR_NEXIST( dirInfo->ToString() ), MESSAGE_TITLE_ERROR,
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
				MessageBox::Show( MESSAGE_TEXT_FILE_NEXIST( fileInfo->ToString() ), MESSAGE_TITLE_ERROR,
					System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
				return;
			}
			counter++;
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
	counter = 0;

	checkDataSizeThread = gcnew Thread(gcnew System::Threading::ThreadStart(this, &CheckSize::checkDataSize));
	checkDataSizeThread->Start();
}

void CheckSize::stopProcess()
{
	inProgress = false;
	checkDataSizeThread->Abort();
	counter = 0;
}

void CheckSize::checkSubFolderSize(System::String^ checkPath)
{
	if (checkPath[checkPath->Length - 1] != '/' && checkPath[checkPath->Length - 1] != '\\')
		checkPath += "\\";

	System::IO::DirectoryInfo dirInfo(checkPath);

	for (int iter = 0; iter < dirInfo.GetDirectories()->Length; iter++)
		checkSubFolderSize(dirInfo.ToString() + dirInfo.GetDirectories()[iter]->ToString() + "\\");

	counter += dirInfo.GetFiles()->Length;
	putLableTextSize();
}

void CheckSize::putLableTextSize()
{
	if (inProgress)
		sizeLable->Text = LABEL_CALCUL( counter.ToString( ) );
	else
		sizeLable->Text = LABEL_CALCUL_RES( counter.ToString( ) );
}

unsigned long long int CheckSize::getSize()
{
	return counter;
}