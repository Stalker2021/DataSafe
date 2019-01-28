#include "MainForm.h"
#include "SettingForm.h"
#include "Defines.h"

using DataSafe::MainForm;
using DataSafe::SettingForm;
using System::Windows::Forms::MessageBox;
using System::IO::StreamReader;
using System::IO::StreamWriter;
using System::IO::File;
using System::Media::SoundPlayer;

#define APP_START_DIR Application::StartupPath

/*Main_Form Load - preload*/
System::Void MainForm::MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
	//for using with multithread
	label_processSize->CheckForIllegalCrossThreadCalls = false;

	//load sounds
	if (File::Exists(APP_START_DIR + FILE_SOUND_DIFFER_FOUND))
		sound_differenceFound = gcnew SoundPlayer(APP_START_DIR + FILE_SOUND_DIFFER_FOUND);

	if (File::Exists(APP_START_DIR + FILE_SOUND_CHECK_DONE))
		sound_checkingDone = gcnew SoundPlayer(APP_START_DIR + FILE_SOUND_CHECK_DONE);

	//load config file, create if absent
	if (!File::Exists(APP_START_DIR + FILE_CONFIG))
	{
		StreamWriter^ writeFile = gcnew StreamWriter(APP_START_DIR + FILE_CONFIG);
		writeFile->Close();
	}
	readFile = gcnew StreamReader(APP_START_DIR + FILE_CONFIG);

	//start calculate files for Save
	checkSize = gcnew CheckSize(readFile, label_processSize);
	checkSize->startProcess();
}

/*Main_Form Closing - stop threads and processes*/
System::Void MainForm::MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	if (checkSize->isRun())
		checkSize->stopProcess();

	if (checkDifferentThread)
		checkDifferentThread->Abort();
}

/*Label_ProcessSize DoubleClick - restart calculation*/
System::Void MainForm::label_processSize_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (LABEL_PROCESSING == label_process->Text)
		return;

	if (checkSize->isRun())
	{
		checkSize->stopProcess();
		label_processSize->Text = PROCESS_CLEAR;
	}

	progressBar->Maximum = 100;
	progressBar->Value = 0;

	readFile->Close();
	readFile = gcnew StreamReader(APP_START_DIR + FILE_CONFIG);
	checkSize = gcnew CheckSize(readFile, label_processSize);

	checkSize->startProcess();
}

/*Button_Settings Click - open settings*/
System::Void MainForm::button_edit_Click(System::Object^  sender, System::EventArgs^  e)
{
	//open Settings form, stop calculating if running
	SettingForm^ settingWindow = gcnew SettingForm();
	settingWindow->startPoint = MainForm::Location;
	if (checkSize->isRun())
		checkSize->stopProcess();
	readFile->Close();
	MainForm::Visible = false;
	settingWindow->ShowDialog();

	//show main window and start calculating
	MainForm::Location = settingWindow->startPoint;
	label_process->Text = LABEL_READY;
	progressBar->Value = 0;
	readFile = gcnew StreamReader(APP_START_DIR + FILE_CONFIG);
	checkSize = gcnew CheckSize(readFile, label_processSize);
	checkSize->startProcess();
	MainForm::Visible = true;
}

/*Button_Check Click - start checking*/
System::Void MainForm::button_check_Click(System::Object^  sender, System::EventArgs^  e)
{
	//stop calculating if running
	if (checkSize->isRun())
	{
		checkSize->stopProcess();
		label_processSize->Text = PROCESS_CLEAR;
	}

	progressBar->Maximum = (int)( checkSize->getSize() );
	progressBar->Value = 0;

	readFile->Close();

	//start Checking process
	checkDifferentThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &MainForm::checkDifferences));
	checkDifferentThread->Start();
}

/*Panel_Data DoubleClick - try to open Data file*/
System::Void MainForm::panel_data_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	System::Diagnostics::Process ^app = gcnew System::Diagnostics::Process();
	app->Start(label_dataName->Text->ToString()->Remove(0, 6));
	app->Close();
}

/*Panel_Safe DoubleClick - try to open Safe file*/
System::Void MainForm::panel_safe_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	System::Diagnostics::Process ^app = gcnew System::Diagnostics::Process();
	app->Start(label_safeName->Text->ToString()->Remove(0, 6));
	app->Close();
}

/*Button_EventData Click*/
System::Void MainForm::button_eventData_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ safeFile = label_safeName->Text->ToString()->Remove(0, 6);

	if (button_eventData->Text == LABEL_ACTION_COPY_DATA)		// for copy Data to Safe
	{
		String^ dataFile = label_dataName->Text->ToString()->Remove(0, 6);
		File::Copy(dataFile, safeFile, true);
	}
	else if (button_eventData->Text == LABEL_ACTION_DEL_SAFE)	// for delete from Safe
	{
		System::Windows::Forms::DialogResult check;
		check = MessageBox::Show(MESSAGE_TEXT_DELFNREST, MESSAGE_TITLE_ATTENTION, MessageBoxButtons::OKCancel, MessageBoxIcon::Warning);
		if (check == System::Windows::Forms::DialogResult::Cancel)
			return;

		File::Delete(safeFile);
	}

	eventButtonsDisable();
}

/*Button_EventSafe Click*/
System::Void MainForm::button_eventSafe_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ dataFile = label_dataName->Text->ToString()->Remove(0, 6);

	if (button_eventSafe->Text == LABEL_ACTION_COPY_SAFE)		// for copy Safe to Data
	{
		String^ safeFile = label_safeName->Text->ToString()->Remove(0, 6);
		File::Copy(safeFile, dataFile, true);
	}
	else if (button_eventSafe->Text == LABEL_ACTION_DEL_DATA)	// for delete from Data
	{
		System::Windows::Forms::DialogResult check;
		check = MessageBox::Show(MESSAGE_TEXT_DELFNREST, MESSAGE_TITLE_ATTENTION, MessageBoxButtons::OKCancel, MessageBoxIcon::Warning);
		if (check == System::Windows::Forms::DialogResult::Cancel)
			return;

		File::Delete(dataFile);
	}

	eventButtonsDisable();
}

/*Button_EventSkip Click*/
System::Void MainForm::button_skip_Click(System::Object^  sender, System::EventArgs^  e)
{
	eventButtonsDisable();
}

//============= support methods =============//

/*Disable choose buttons and clean info-labels*/
System::Void MainForm::eventButtonsDisable()
{
	button_eventData->Enabled = false;
	button_skip->Enabled = false;
	button_eventSafe->Enabled = false;
	panel_data->Enabled = false;
	panel_safe->Enabled = false;

	label_dataSize->Text = LABEL_CHAPTER_SIZE;
	label_dataChanges->Text = LABEL_CHAPTER_CHANGE ;
	label_dataName->Text = LABEL_CHAPTER_NAME;

	label_safeSize->Text = LABEL_CHAPTER_SIZE;
	label_safeChanges->Text = LABEL_CHAPTER_CHANGE;
	label_safeName->Text = LABEL_CHAPTER_NAME;
}

/*Enable choose buttons and fill info-labels for Save is absent*/
System::Void MainForm::eventButtonsEnable(System::IO::FileInfo^ dataFile, System::String^ safePath)
{
	button_eventData->Text = LABEL_ACTION_COPY_DATA;
	button_eventData->Enabled = true;
	button_skip->Enabled = true;
	button_eventSafe->Text = LABEL_ACTION_DEL_DATA;
	button_eventSafe->Enabled = true;
	panel_data->Enabled = true;

	label_dataSize->Text = LABEL_CHAPTER_SIZE + dataFile->Length.ToString();
	label_dataChanges->Text = LABEL_CHAPTER_CHANGE + dataFile->LastWriteTime.ToString();
	label_dataName->Text = LABEL_CHAPTER_NAME + dataFile->FullName;

	label_safeSize->Text = LABEL_CHAPTER_SIZE;
	label_safeChanges->Text = LABEL_CHAPTER_CHANGE;
	label_safeName->Text = LABEL_CHAPTER_NAME + safePath + dataFile->Name;

	if(nullptr != sound_differenceFound)
		sound_differenceFound->Play();
}

/*Enable choose buttons and fill info-labels for Data is absent*/
System::Void MainForm::eventButtonsEnable(System::String^ dataPath, System::IO::FileInfo^ safeFile)
{
	button_eventData->Text = LABEL_ACTION_DEL_SAFE;
	button_eventData->Enabled = true;
	button_skip->Enabled = true;
	button_eventSafe->Text = LABEL_ACTION_COPY_SAFE;
	button_eventSafe->Enabled = true;
	panel_safe->Enabled = true;

	label_dataSize->Text = LABEL_CHAPTER_SIZE;
	label_dataChanges->Text = LABEL_CHAPTER_CHANGE;
	label_dataName->Text = LABEL_CHAPTER_NAME + dataPath + safeFile->Name;

	label_safeSize->Text = LABEL_CHAPTER_SIZE + safeFile->Length.ToString();
	label_safeChanges->Text = LABEL_CHAPTER_CHANGE + safeFile->LastWriteTime.ToString();
	label_safeName->Text = LABEL_CHAPTER_NAME + safeFile->FullName;

	if (nullptr != sound_differenceFound)
		sound_differenceFound->Play();
}

/*Enable choose buttons and fill info-labels for difference is found*/
System::Void MainForm::eventButtonsEnable(System::IO::FileInfo^ dataFile, System::IO::FileInfo^ safeFile)
{
	button_eventData->Text = LABEL_ACTION_COPY_DATA;
	button_eventData->Enabled = true;
	button_skip->Enabled = true;
	button_eventSafe->Text = LABEL_ACTION_COPY_SAFE;
	button_eventSafe->Enabled = true;
	panel_data->Enabled = true;
	panel_safe->Enabled = true;

	label_dataSize->Text = LABEL_CHAPTER_SIZE + dataFile->Length.ToString();
	label_dataChanges->Text = LABEL_CHAPTER_CHANGE + dataFile->LastWriteTime.ToString();
	label_dataName->Text = LABEL_CHAPTER_NAME + dataFile->FullName;

	label_safeSize->Text = LABEL_CHAPTER_SIZE + safeFile->Length.ToString();
	label_safeChanges->Text = LABEL_CHAPTER_CHANGE + safeFile->LastWriteTime.ToString();
	label_safeName->Text = LABEL_CHAPTER_NAME + safeFile->FullName;

	if (nullptr != sound_differenceFound)
		sound_differenceFound->Play();
}

/*Chacking Process*/
System::Void MainForm::checkDifferences()
{
	//disable buttons
	label_process->Text = LABEL_PROCESSING;
	button_edit->Enabled = false;
	button_check->Enabled = false;

	eventButtonsDisable();

	System::IO::DirectoryInfo^ dataDirInfo;
	System::IO::FileInfo^ dataFileInfo;
	System::IO::DirectoryInfo^ safeDirInfo;
	System::IO::FileInfo^ safeFileInfo;
	String^ buffPath;
	wchar_t buffType;

	readFile = gcnew StreamReader(APP_START_DIR + FILE_CONFIG);

	//Checking cicle
	while (true)
	{
		buffPath = readFile->ReadLine();
		if (!buffPath || buffPath == EMPTY_STRING)	//check end of config file
			break;

		buffType = buffPath[buffPath->Length - 1];
		if (buffType == '/' || buffType == '\\')		//if Checking single folder
		{
			dataDirInfo = gcnew System::IO::DirectoryInfo(buffPath);
			if (!dataDirInfo->Exists)
			{
				MessageBox::Show(MESSAGE_TEXT_DIR_NEXIST(buffPath), MESSAGE_TITLE_ERROR, MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			safeDirInfo = gcnew System::IO::DirectoryInfo(readFile->ReadLine());
			checkFoldersDifferences(dataDirInfo, safeDirInfo);
			backChecking(safeDirInfo, dataDirInfo);
		}
		else if (buffType == '+')	//if Checking folder with subfolders
		{
			dataDirInfo = gcnew System::IO::DirectoryInfo(buffPath->Remove(buffPath->Length - 1));
			if (!dataDirInfo->Exists)
			{
				MessageBox::Show(MESSAGE_TEXT_DIR_NEXIST(dataDirInfo->ToString()),
					MESSAGE_TITLE_ERROR, MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			checkSubFolderDifferences(dataDirInfo->ToString(), readFile->ReadLine());
		}
		else	//if Checking file
		{
			dataFileInfo = gcnew System::IO::FileInfo(buffPath);
			if (!dataFileInfo->Exists)
			{
				MessageBox::Show(MESSAGE_TEXT_FILE_NEXIST( dataFileInfo->ToString() ),
					MESSAGE_TITLE_ERROR, MessageBoxButtons::OK, MessageBoxIcon::Error);
				return;
			}

			safeFileInfo = gcnew System::IO::FileInfo(readFile->ReadLine());
			checkFilesDifferences(dataFileInfo, safeFileInfo);

			progressBarCkeckingUpdate();
		}
	}

	//reload config file
	readFile->Close();
	readFile = gcnew StreamReader(APP_START_DIR + FILE_CONFIG);

	label_process->Text = LABEL_CHECK_DONE;
	progressBar->Value = progressBar->Maximum;
	label_processSize->Text = MESSAGE_TEXT_PROGRESS( progressBar->Value.ToString( ), progressBar->Maximum.ToString( ) );
	button_edit->Enabled = true;
	button_check->Enabled = true;

	if(nullptr != sound_checkingDone)
		sound_checkingDone->Play();
}

/*Checking process of subfolders*/
System::Void MainForm::checkSubFolderDifferences(System::String^ dataPath, System::String^ safePath)
{
	if (dataPath[dataPath->Length - 1] != '/' && dataPath[dataPath->Length - 1] != '\\')
		dataPath += "\\";

	if (safePath[safePath->Length - 1] != '/' && safePath[safePath->Length - 1] != '\\')
		safePath += "\\";

	System::IO::DirectoryInfo^ dataDirInfo = gcnew System::IO::DirectoryInfo(dataPath);

	//Checking subfolders in current folder
	for (int iter = 0; iter < dataDirInfo->GetDirectories()->Length; iter++)
	{
		if (!System::IO::Directory::Exists(safePath + dataDirInfo->GetDirectories()[iter]->ToString() + "\\"))
			System::IO::Directory::CreateDirectory(safePath + dataDirInfo->GetDirectories()[iter]->ToString() + "\\");

		checkSubFolderDifferences(	dataDirInfo->ToString() + dataDirInfo->GetDirectories()[iter]->ToString() +"\\",
									safePath + dataDirInfo->GetDirectories()[iter]->ToString() + "\\");
	}

	//Checking curren folder
	System::IO::DirectoryInfo^ safeDirInfo = gcnew System::IO::DirectoryInfo(safePath);
	checkFoldersDifferences(dataDirInfo, safeDirInfo);
	backChecking(dataDirInfo, safeDirInfo);
}

/*Checking process of folders*/
System::Void MainForm::checkFoldersDifferences(System::IO::DirectoryInfo^ dataDir, System::IO::DirectoryInfo^ safeDir)
{
	int checkDel;
	System::IO::FileInfo^ safeFile;

	for (int iter = 0; iter < dataDir->GetFiles()->Length; iter++)
	{
		checkDel = (int)(dataDir->GetFiles()->Length);
		safeFile = gcnew System::IO::FileInfo(safeDir->ToString() + dataDir->GetFiles()[iter]->ToString());
		checkFilesDifferences(dataDir->GetFiles()[iter], safeFile);

		if (checkDel - 1 == dataDir->GetFiles()->Length)
			iter--;

		progressBarCkeckingUpdate();
	}
}

/*Checking process of files*/
System::Void MainForm::checkFilesDifferences(System::IO::FileInfo^ dataFile, System::IO::FileInfo^ safeFile)
{
	if (safeFile->Exists)
	{
		if (!isSameFiles(dataFile, safeFile))
		{
			if (checkBox_replaceAll->Checked)
			{
				File::Copy(dataFile->FullName, safeFile->FullName, true);
			}
			else
			{
				eventButtonsEnable(dataFile, safeFile);
				waitForDecision();
			}
		}
	}
	else
	{
		if (checkBox_addAll->Checked)
		{
			File::Copy(dataFile->FullName, safeFile->Directory->ToString() + "\\" + dataFile->Name);
		}
		else
		{
			eventButtonsEnable(dataFile, safeFile->Directory->ToString() + "\\");
			waitForDecision();
		}
	}
}

/*Checking existing files from SaveDir to DataDir*/
System::Void MainForm::backChecking(System::IO::DirectoryInfo^ dataDir, System::IO::DirectoryInfo^ safeDir)
{
	label_back_check->Text = LABEL_BACK_CHECK;
	for (int iter = 0; iter < safeDir->GetFiles()->Length; iter++)
	{
		label_file_names->Text = safeDir->GetFiles()[iter]->ToString();

		if (!System::IO::File::Exists(dataDir->ToString() + safeDir->GetFiles()[iter]))
		{
			if (checkBox_recoverAll->Checked)
			{
				File::Copy(safeDir->GetFiles()[iter]->FullName, dataDir->ToString() + safeDir->GetFiles()[iter]->Name);
			}
			else
			{
				int checkDel = (int)(safeDir->GetFiles()->Length);
				eventButtonsEnable(dataDir->ToString(), safeDir->GetFiles()[iter]);
				waitForDecision();

				if (checkDel - 1 == safeDir->GetFiles()->Length)
					iter--;
			}
		}
	}
	label_file_names->Text = EMPTY_STRING;
	label_back_check->Text = EMPTY_STRING;
}

/*Wait for decision of user*/
System::Void MainForm::waitForDecision()
{
	while (button_skip->Enabled)
		checkDifferentThread->Sleep(250);
}

/*Continue indication of checking on progressBar*/
System::Void MainForm::progressBarCkeckingUpdate()
{
	if (checkSize->getSize())
	{
		if (progressBar->Maximum < progressBar->Value + 1)
			progressBar->Maximum++;
		progressBar->Value++;
		label_processSize->Text = MESSAGE_TEXT_PROGRESS(progressBar->Value.ToString(), progressBar->Maximum.ToString());
	}
}

/*Checking files similarity*/
System::Boolean MainForm::isSameFiles(System::IO::FileInfo^ file1, System::IO::FileInfo^ file2)
{
	return file1->Length == file2->Length && file1->LastWriteTime == file2->LastWriteTime;
}