#include "CheckSizeThread.h"
#include "Defines.h"

using System::Windows::Forms::MessageBox;
using System::Windows::Forms::MessageBoxButtons;
using System::Windows::Forms::MessageBoxIcon;
using System::Threading::Thread;

/*Defauld Constructor - check argumrnts*/
CheckSize::CheckSize(System::IO::StreamReader^ config, System::Windows::Forms::Label^ lable)
{
	if (!lable || !config)
		return;
	sizeLable = lable;
	configFile = config;
}

/*Start calculation process*/
void CheckSize::startProcess()
{
	if (!sizeLable || !configFile)
		return;
	counter = 0;

	checkDataSizeThread = gcnew Thread(gcnew System::Threading::ThreadStart(this, &CheckSize::checkDataSize));
	checkDataSizeThread->Start();
}

/*Stop calculation process*/
void CheckSize::stopProcess()
{
	inProgress = false;
	checkDataSizeThread->Abort();
	counter = 0;
}

/*Check if calculation process is running*/
bool CheckSize::isRun()
{
	return inProgress;
}

/*Get count of files*/
unsigned long long int CheckSize::getSize()
{
	return counter;
}

/*Process of calculation*/
void CheckSize::checkDataSize()
{
	inProgress = true;
	System::IO::DirectoryInfo^ dirInfo;
	System::IO::FileInfo^ fileInfo;
	String^ buffPath;
	wchar_t buffType;

	//main cicle of calculation
	while (true)
	{
		buffPath = configFile->ReadLine();
		if (!buffPath || buffPath == EMPTY_STRING)
			break;
		buffType = buffPath[buffPath->Length - 1];
		if (buffType == '\\' || buffType == '/')	//for single folder
		{
			dirInfo = gcnew System::IO::DirectoryInfo(buffPath);
			if (!dirInfo->Exists)
			{
				MessageBox::Show (MESSAGE_TEXT_DIR_NEXIST( buffPath ), MESSAGE_TITLE_ERROR, MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			counter += dirInfo->GetFiles()->Length;
			putLableTextSize();
		}
		else if (buffType == '+')					//for folder with subfolders
		{
			dirInfo = gcnew System::IO::DirectoryInfo(buffPath->Remove(buffPath->Length - 1));
			if (!dirInfo->Exists)
			{
				MessageBox::Show( MESSAGE_TEXT_DIR_NEXIST( dirInfo->ToString() ),
					MESSAGE_TITLE_ERROR, MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			checkSubFolderSize(dirInfo->ToString());
		}
		else										//for files
		{
			fileInfo = gcnew System::IO::FileInfo(buffPath);
			if (!fileInfo->Exists)
			{
				MessageBox::Show( MESSAGE_TEXT_FILE_NEXIST( fileInfo->ToString() ),
					MESSAGE_TITLE_ERROR, MessageBoxButtons::OK, MessageBoxIcon::Error);
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

/*Calculation files in subfolders*/
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

/*Update counter indicator*/
void CheckSize::putLableTextSize()
{
	if (inProgress)
		sizeLable->Text = LABEL_CALCUL( counter.ToString( ) );
	else
		sizeLable->Text = LABEL_CALCUL_RES( counter.ToString( ) );
}