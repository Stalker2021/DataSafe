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

System::Void MainForm::MainForm_Load(System::Object^  sender, System::EventArgs^  e) {
	label_processSize->CheckForIllegalCrossThreadCalls = false;

	if (File::Exists(Application::StartupPath + FILE_SOUND_DIFFER_FOUND))
		sound_differenceFound = gcnew SoundPlayer(Application::StartupPath + FILE_SOUND_DIFFER_FOUND);

	if (File::Exists(Application::StartupPath + FILE_SOUND_CHECK_DONE))
		sound_checkingDone = gcnew SoundPlayer(Application::StartupPath + FILE_SOUND_CHECK_DONE);

	if (!File::Exists(Application::StartupPath + FILE_CONFIG))
	{
		StreamWriter^ writeFile = gcnew StreamWriter(Application::StartupPath + FILE_CONFIG);
		writeFile->Close();
	}
	readFile = gcnew StreamReader(Application::StartupPath + FILE_CONFIG);

	checkSize = gcnew CheckSize(readFile, label_processSize);
	checkSize->startProcess();
}

System::Void MainForm::button_edit_Click(System::Object^  sender, System::EventArgs^  e)
{
	SettingForm^ settingWindow = gcnew SettingForm();
	settingWindow->startPoint = MainForm::Location;
	if (checkSize->isRun())
		checkSize->stopProcess();
	readFile->Close();
	MainForm::Visible = false;
	settingWindow->ShowDialog();

	MainForm::Location = settingWindow->startPoint;
	label_process->Text = LABEL_READY;
	progressBar->Value = 0;
	readFile = gcnew StreamReader(Application::StartupPath + FILE_CONFIG);
	checkSize = gcnew CheckSize(readFile, label_processSize);
	checkSize->startProcess();
	MainForm::Visible = true;
}

System::Void MainForm::button_check_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (checkSize->isRun())
	{
		checkSize->stopProcess();
		label_processSize->Text = PROCESS_CLEAR;
	}

	progressBar->Maximum = (int)( checkSize->getSize() );
	progressBar->Value = 0;

	readFile->Close();

	checkDifferentThread = gcnew System::Threading::Thread(gcnew System::Threading::ThreadStart(this, &MainForm::checkDifferences));
	checkDifferentThread->Start();
}

System::Void MainForm::MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
{
	if (checkSize->isRun())
		checkSize->stopProcess();

	if (checkDifferentThread)
		checkDifferentThread->Abort();
}

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

// #UPADATE_1.1: Back Checking (from Safe to Data)
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

System::Void MainForm::checkDifferences()
{
	label_process->Text = LABEL_PRICESSING;
	button_edit->Enabled = false;
	button_check->Enabled = false;

	eventButtonsDisable();

	System::IO::DirectoryInfo^ dataDirInfo;
	System::IO::FileInfo^ dataFileInfo;
	System::IO::DirectoryInfo^ safeDirInfo;
	System::IO::FileInfo^ safeFileInfo;
	String^ buffPath;
	wchar_t buffType;

	readFile = gcnew StreamReader(Application::StartupPath + FILE_CONFIG);

	while (true)
	{
		buffPath = readFile->ReadLine();
		if (!buffPath || buffPath == EMPTY_STRING)
			break;
		buffType = buffPath[buffPath->Length - 1];
		if (buffType == '\\' || buffType == '/')
		{
			dataDirInfo = gcnew System::IO::DirectoryInfo(buffPath);
			if (!dataDirInfo->Exists)
			{
				MessageBox::Show( MESSAGE_TEXT_DIR_NEXIST( buffPath ), MESSAGE_TITLE_ERROR,
					System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
				return;
			}

			safeDirInfo = gcnew System::IO::DirectoryInfo(readFile->ReadLine());

			for (int iter = 0; iter < dataDirInfo->GetFiles()->Length; iter++)
			{
				if (System::IO::File::Exists(safeDirInfo->ToString() + dataDirInfo->GetFiles()[iter]->ToString()))
				{
					safeFileInfo = gcnew System::IO::FileInfo(safeDirInfo->ToString() + dataDirInfo->GetFiles()[iter]->ToString());
					if (dataDirInfo->GetFiles()[iter]->Length != safeFileInfo->Length ||
						dataDirInfo->GetFiles()[iter]->LastWriteTime != safeFileInfo->LastWriteTime)
					{
						if (checkBox_replaceAll->Checked)
						{
							File::Copy(dataDirInfo->GetFiles()[iter]->FullName, safeFileInfo->FullName, true);
						}
						else
						{
							eventButtonsEnable(dataDirInfo->GetFiles()[iter], safeFileInfo);
							while (button_skip->Enabled)
								checkDifferentThread->Sleep(250);
						}
					}
				}
				else
				{
					if (checkBox_addAll->Checked)
					{
						File::Copy(dataDirInfo->GetFiles()[iter]->FullName, safeDirInfo->ToString() + dataDirInfo->GetFiles()[iter]->Name);
					}
					else
					{
						int checkDel = (int)(dataDirInfo->GetFiles()->Length);
						eventButtonsEnable(dataDirInfo->GetFiles()[iter], safeDirInfo->ToString());
						while (button_skip->Enabled)
							checkDifferentThread->Sleep(250);
						if (checkDel - 1 == dataDirInfo->GetFiles()->Length)
						{
							iter--;
							continue;
						}
					}
				}

				if (checkSize->getSize())
				{
					if (progressBar->Maximum < progressBar->Value + 1)
						progressBar->Maximum++;
					progressBar->Value++;
					label_processSize->Text = MESSAGE_TEXT_PROGRESS( progressBar->Value.ToString(), progressBar->Maximum.ToString() );
				}
			}

			// #UPADATE_1.1: Back Checking (from Safe to Data)
			label_back_check->Text = LABEL_BACK_CHECK;
			for (int iter = 0; iter < safeDirInfo->GetFiles()->Length; iter++)
			{
				label_file_names->Text = safeDirInfo->GetFiles()[iter]->ToString( );

				if (!System::IO::File::Exists(dataDirInfo->ToString() + safeDirInfo->GetFiles()[iter]))
				{
					if (checkBox_recoverAll->Checked)
					{
						File::Copy(safeDirInfo->GetFiles()[iter]->FullName, dataDirInfo->ToString() + safeDirInfo->GetFiles()[iter]->Name);
					}
					else
					{
						int checkDel = (int)(safeDirInfo->GetFiles()->Length);
						eventButtonsEnable(dataDirInfo->ToString(), safeDirInfo->GetFiles()[iter]);
						while (button_skip->Enabled)
							checkDifferentThread->Sleep(250);
						if (checkDel - 1 == safeDirInfo->GetFiles()->Length)
							iter--;
					}

					//MessageBox::Show("#UPDATE_1" + "\n" + dataDirInfo->ToString() + safeDirInfo->GetFiles()[iter] + "\n" + safeDirInfo->ToString() + safeDirInfo->GetFiles()[iter]);
				}
			}
			label_file_names->Text = EMPTY_STRING;
			label_back_check->Text = EMPTY_STRING;
		}
		else if (buffType == '+')
		{
			dataDirInfo = gcnew System::IO::DirectoryInfo(buffPath->Remove(buffPath->Length - 1));
			if (!dataDirInfo->Exists)
			{
				MessageBox::Show(MESSAGE_TEXT_DIR_NEXIST( dataDirInfo->ToString() ), MESSAGE_TITLE_ERROR,
					System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
				return;
			}

			checkSubFolderDifferences(dataDirInfo->ToString(), readFile->ReadLine());
		}
		else
		{
			dataFileInfo = gcnew System::IO::FileInfo(buffPath);
			if (!dataFileInfo->Exists)
			{
				MessageBox::Show(MESSAGE_TEXT_FILE_NEXIST( dataFileInfo->ToString() ), MESSAGE_TITLE_ERROR,
					System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
				return;
			}

			safeFileInfo = gcnew System::IO::FileInfo(readFile->ReadLine());
			if (safeFileInfo->Exists)
			{
				if (dataFileInfo->Length != safeFileInfo->Length ||
					dataFileInfo->LastWriteTime != safeFileInfo->LastWriteTime)
				{
					if (checkBox_replaceAll->Checked)
					{
						File::Copy(dataFileInfo->FullName, safeFileInfo->FullName, true);
					}
					else
					{
						eventButtonsEnable(dataFileInfo, safeFileInfo);
						while (button_skip->Enabled)
							checkDifferentThread->Sleep(250);
					}
				}
			}
			else
			{
				if (checkBox_addAll->Checked)
				{
					File::Copy(dataFileInfo->FullName, safeFileInfo->Directory->ToString() + "\\" + dataFileInfo->Name);
				}
				else
				{
					eventButtonsEnable(dataFileInfo, safeFileInfo->Directory->ToString() + "\\");
					while (button_skip->Enabled)
						checkDifferentThread->Sleep(250);
				}
			}

			if (checkSize->getSize())
			{
				if (progressBar->Maximum < progressBar->Value + 1)
					progressBar->Maximum++;
				progressBar->Value++;
				label_processSize->Text = MESSAGE_TEXT_PROGRESS( progressBar->Value.ToString(), progressBar->Maximum.ToString() );
			}
		}
	}

	readFile->Close();
	readFile = gcnew StreamReader(Application::StartupPath + FILE_CONFIG);

	label_process->Text = LABEL_CHECK_DONE;
	progressBar->Value = progressBar->Maximum;
	label_processSize->Text = MESSAGE_TEXT_PROGRESS( progressBar->Value.ToString( ), progressBar->Maximum.ToString( ) );
	button_edit->Enabled = true;
	button_check->Enabled = true;

	if(nullptr != sound_checkingDone)
		sound_checkingDone->Play();
}

System::Void MainForm::checkSubFolderDifferences(System::String^ dataPath, System::String^ safePath)
{
	if (dataPath[dataPath->Length - 1] != '/' && dataPath[dataPath->Length - 1] != '\\')
		dataPath += "\\";

	if (safePath[safePath->Length - 1] != '/' && safePath[safePath->Length - 1] != '\\')
		safePath += "\\";

	System::IO::DirectoryInfo dataDirInfo(dataPath);

	for (int iter = 0; iter < dataDirInfo.GetDirectories()->Length; iter++)
	{
		if (!System::IO::Directory::Exists(safePath + dataDirInfo.GetDirectories()[iter]->ToString() + "\\"))
			System::IO::Directory::CreateDirectory(safePath + dataDirInfo.GetDirectories()[iter]->ToString() + "\\");

		checkSubFolderDifferences(dataDirInfo.ToString() + dataDirInfo.GetDirectories()[iter]->ToString() + "\\", safePath + dataDirInfo.GetDirectories()[iter]->ToString() + "\\");
	}

	System::IO::FileInfo^ safeFileInfo;

	for (int iter = 0; iter < dataDirInfo.GetFiles()->Length; iter++)
	{
		if (System::IO::File::Exists(safePath + dataDirInfo.GetFiles()[iter]->ToString()))
		{
			safeFileInfo = gcnew System::IO::FileInfo(safePath + dataDirInfo.GetFiles()[iter]->ToString());
			if (dataDirInfo.GetFiles()[iter]->Length != safeFileInfo->Length ||
				dataDirInfo.GetFiles()[iter]->LastWriteTime != safeFileInfo->LastWriteTime)
			{
				if (checkBox_replaceAll->Checked)
				{
					File::Copy(dataDirInfo.GetFiles()[iter]->FullName, safeFileInfo->FullName, true);
				}
				else
				{
					eventButtonsEnable(dataDirInfo.GetFiles()[iter], safeFileInfo);
					while (button_skip->Enabled)
						checkDifferentThread->Sleep(250);
				}
			}
		}
		else
		{
			if (checkBox_addAll->Checked)
			{
				File::Copy(dataDirInfo.GetFiles()[iter]->FullName, safePath + dataDirInfo.GetFiles()[iter]->Name);
			}
			else
			{
				int checkDel = (int)(dataDirInfo.GetFiles()->Length);
				eventButtonsEnable(dataDirInfo.GetFiles()[iter], safePath);
				while (button_skip->Enabled)
					checkDifferentThread->Sleep(250);
				if (checkDel - 1 == dataDirInfo.GetFiles()->Length)
				{
					iter--;
					continue;
				}
			}
		}

		if (checkSize->getSize())
		{
			if (progressBar->Maximum < progressBar->Value + 1)
				progressBar->Maximum++;
			progressBar->Value++;
			label_processSize->Text = MESSAGE_TEXT_PROGRESS( progressBar->Value.ToString(), progressBar->Maximum.ToString() );
		}
	}

	// #UPADATE_1.1: Back Checking (from Safe to Data)
	label_back_check->Text = LABEL_BACK_CHECK;
	System::IO::DirectoryInfo safeDirInfo(safePath);
	for (int iter = 0; iter < safeDirInfo.GetFiles()->Length; iter++)
	{
		label_file_names->Text = safeDirInfo.GetFiles()[iter]->ToString();
		if (!System::IO::File::Exists(dataDirInfo.ToString() + safeDirInfo.GetFiles()[iter]))
		{
			if (checkBox_recoverAll->Checked)
			{
				File::Copy(safeDirInfo.GetFiles()[iter]->FullName, dataDirInfo.ToString() + safeDirInfo.GetFiles()[iter]->Name);
			}
			else
			{
				int checkDel = (int)(safeDirInfo.GetFiles()->Length);
				eventButtonsEnable(dataPath, safeDirInfo.GetFiles()[iter]);
				while (button_skip->Enabled)
					checkDifferentThread->Sleep(250);
				if (checkDel - 1 == safeDirInfo.GetFiles()->Length)
					iter--;
			}

			//MessageBox::Show("#UPDATE_2" + "\n" + dataDirInfo.ToString() + safeDirInfo.GetFiles()[iter]->Name + "\n" + safeDirInfo.GetFiles()[iter]->FullName);
		}
	}
	label_file_names->Text = EMPTY_STRING;
	label_back_check->Text = EMPTY_STRING;
}

System::Void MainForm::label_processSize_MouseDoubleClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e)
{
	if (LABEL_PRICESSING == label_process->Text)
		return;

	if (checkSize->isRun())
		checkSize->stopProcess();

	readFile->Close();
	readFile = gcnew StreamReader(Application::StartupPath + FILE_CONFIG);
	checkSize = gcnew CheckSize(readFile, label_processSize);

	checkSize->startProcess();
}

System::Void MainForm::button_eventData_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ safeFile = label_safeName->Text->ToString()->Remove(0, 6);

	if (button_eventData->Text == LABEL_ACTION_COPY_DATA)
	{
		String^ dataFile = label_dataName->Text->ToString()->Remove(0, 6);
		File::Copy(dataFile, safeFile, true);
	}
	// #UPADATE_1.1: Back Checking (from Safe to Data)
	else if (button_eventData->Text == LABEL_ACTION_DEL_SAFE)
	{
		System::Windows::Forms::DialogResult check;
		check = MessageBox::Show (MESSAGE_TEXT_DELFNREST, MESSAGE_TITLE_ATTENTION,
			System::Windows::Forms::MessageBoxButtons::OKCancel, System::Windows::Forms::MessageBoxIcon::Warning);
		if (check == System::Windows::Forms::DialogResult::Cancel)
			return;

		File::Delete(safeFile);
	}

	eventButtonsDisable();
}

System::Void MainForm::button_eventSafe_Click(System::Object^  sender, System::EventArgs^  e)
{
	String^ dataFile = label_dataName->Text->ToString()->Remove(0, 6);

	if (button_eventSafe->Text == LABEL_ACTION_COPY_SAFE)
	{
		String^ safeFile = label_safeName->Text->ToString()->Remove(0, 6);
		File::Copy(safeFile, dataFile, true);
	}
	else if (button_eventSafe->Text == LABEL_ACTION_DEL_DATA)
	{
		System::Windows::Forms::DialogResult check;
		check = MessageBox::Show( MESSAGE_TEXT_DELFNREST, MESSAGE_TITLE_ATTENTION,
			System::Windows::Forms::MessageBoxButtons::OKCancel, System::Windows::Forms::MessageBoxIcon::Warning);
		if (check == System::Windows::Forms::DialogResult::Cancel)
			return;

		File::Delete(dataFile);
	}

	eventButtonsDisable();
}

System::Void MainForm::button_skip_Click(System::Object^  sender, System::EventArgs^  e)
{
	eventButtonsDisable();
}

System::Void MainForm::panel_data_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	System::Diagnostics::Process ^app = gcnew System::Diagnostics::Process();
	app->Start(label_dataName->Text->ToString()->Remove(0, 6));
	app->Close();
}

System::Void MainForm::panel_safe_DoubleClick(System::Object^  sender, System::EventArgs^  e)
{
	System::Diagnostics::Process ^app = gcnew System::Diagnostics::Process();
	app->Start(label_safeName->Text->ToString()->Remove(0, 6));
	app->Close();
}