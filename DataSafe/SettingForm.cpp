#include "SettingForm.h"
#include "Defines.h"

using DataSafe::SettingForm;
using System::IO::StreamReader;
using System::IO::StreamWriter;
using System::Windows::Forms::MessageBox;
using System::Windows::Forms::DialogResult;

#define APP_START_DIR Application::StartupPath

/*Form_Setting Load - load config*/
System::Void SettingForm::SettingForm_Load(System::Object^  sender, System::EventArgs^  e) {
	SettingForm::Location = startPoint;

	//fill list boxes from config
	StreamReader^ readFile = gcnew StreamReader(APP_START_DIR + FILE_CONFIG);
	String^ check;
	while (true)
	{
		check = readFile->ReadLine();
		if (!check || check == EMPTY_STRING)
			break;
		listBox_sett_data->Items->Add(check);
		dataStack.push_back(check);
		check = readFile->ReadLine();
		listBox_sett_safe->Items->Add(check);
		safeStack.push_back(check);
	}
	readFile->Close();
}

/*Form_Setting Closing - update position of form*/
System::Void SettingForm::SettingForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
	startPoint = SettingForm::Location;
}

/*ListBox_Data SelectItem - select equal item on ListBox_Safe*/
System::Void SettingForm::listBox_sett_data_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) {
	if (listBox_sett_safe->SelectedIndex != listBox_sett_data->SelectedIndex)
		listBox_sett_safe->SelectedIndex = listBox_sett_data->SelectedIndex;
	if (listBox_sett_data->SelectedIndex == -1)
		button_sett_delete->Enabled = false;
	else
		button_sett_delete->Enabled = true;
}

/*ListBox_Safe SelectItem - select equal item on ListBox_Data*/
System::Void SettingForm::listBox_sett_safe_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) {
	if (listBox_sett_data->SelectedIndex != listBox_sett_safe->SelectedIndex)
		listBox_sett_data->SelectedIndex = listBox_sett_safe->SelectedIndex;
	if (listBox_sett_safe->SelectedIndex == -1)
		button_sett_delete->Enabled = false;
	else
		button_sett_delete->Enabled = true;
}

/*ListBox_Data DoubleClick - show message with equal selected items from ListBoxes*/
System::Void SettingForm::listBox_sett_data_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	if (listBox_sett_data->SelectedIndex >= 0)
		MessageBox::Show( MESSAGE_TEXT_DAT_SAF_SELECT( listBox_sett_data->Items[listBox_sett_data->SelectedIndex],
			listBox_sett_safe->Items[listBox_sett_data->SelectedIndex] ), MESSAGE_TITLE_SELECTITM );
}

/*ListBox_Safe DoubleClick - show message with equal selected items from ListBoxes*/
System::Void SettingForm::listBox_sett_safe_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	if (listBox_sett_safe->SelectedIndex >= 0)
		MessageBox::Show(MESSAGE_TEXT_DAT_SAF_SELECT( listBox_sett_data->Items[listBox_sett_safe->SelectedIndex],
			listBox_sett_safe->Items[listBox_sett_safe->SelectedIndex] ), MESSAGE_TITLE_SELECTITM );
}

/*Button_AddFile Click - add file to list of checking process*/
System::Void SettingForm::button_sett_addFile_Click(System::Object^  sender, System::EventArgs^  e)
{
	//select file of Data
	openFileDialog_sett_sellect->Title = BROWSER_DESCR_SELDATAF;
	System::Windows::Forms::DialogResult check;
	check = openFileDialog_sett_sellect->ShowDialog();
	if (check == System::Windows::Forms::DialogResult::Cancel)
		return;

	//check if some files already in Safe
	for (int iter = 0; iter < openFileDialog_sett_sellect->FileNames->Length; iter++)
	{
		if (checkStack(openFileDialog_sett_sellect->FileNames[iter]->ToString(), dataStack))
		{
			check = MessageBox::Show(MESSAGE_TEXT_FEXISTSAFE, MESSAGE_TITLE_ATTENTION, MessageBoxButtons::OKCancel, MessageBoxIcon::Warning);
			if (check == System::Windows::Forms::DialogResult::Cancel)
				return;
		}
	}

	//select folder for Safe
	folderBrowserDialog_sett_select->Description = BROWSER_DESCR_SELSAFE;
	check = folderBrowserDialog_sett_select->ShowDialog();
	if (check == System::Windows::Forms::DialogResult::Cancel)
		return;
	String^ safeDirect;
	safeDirect = folderBrowserDialog_sett_select->SelectedPath;
	if (safeDirect[safeDirect->Length - 1] != '/' && safeDirect[safeDirect->Length - 1] != '\\')
		safeDirect += "\\";

	//check of using selected folder
	if (openFileDialog_sett_sellect->FileNames[0] == safeDirect + openFileDialog_sett_sellect->SafeFileNames[0])
	{
		MessageBox::Show(MESSAGE_TEXT_DIRNFORDS, MESSAGE_TITLE_ERROR, MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	if (checkStack(safeDirect, safeStack))
	{
		MessageBox::Show(MESSAGE_TEXT_ALRASSAFE, MESSAGE_TITLE_ERROR, MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	//add selected files to config
	StreamWriter^ writeFile = gcnew StreamWriter(APP_START_DIR + FILE_CONFIG, true);
	for (int iter = 0; iter < openFileDialog_sett_sellect->FileNames->Length; iter++)
	{
		listBox_sett_data->Items->Add(openFileDialog_sett_sellect->FileNames[iter]->ToString());
		listBox_sett_safe->Items->Add(safeDirect + openFileDialog_sett_sellect->SafeFileNames[iter]);
		dataStack.push_back(openFileDialog_sett_sellect->FileNames[iter]->ToString());
		safeStack.push_back(safeDirect + openFileDialog_sett_sellect->SafeFileNames[iter]);
		writeFile->WriteLine(openFileDialog_sett_sellect->FileNames[iter]->ToString());
		writeFile->WriteLine(safeDirect + openFileDialog_sett_sellect->SafeFileNames[iter]);
	}
	writeFile->Close();
}

/*Button_AddFolder Click - add folder to list of checking process*/
System::Void SettingForm::button_sett_addFolder_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ dataFolder;
	String^ safeFolder;

	//select Data folder
	System::Windows::Forms::DialogResult check;
	folderBrowserDialog_sett_select->Description = BROWSER_DESCR_SELDATAD;
	check = folderBrowserDialog_sett_select->ShowDialog();
	if (check == System::Windows::Forms::DialogResult::Cancel)
		return;
	dataFolder = folderBrowserDialog_sett_select->SelectedPath;
	if (dataFolder[dataFolder->Length - 1] != '/' && dataFolder[dataFolder->Length - 1] != '\\')
		dataFolder += "\\";

	//check of using selected folder
	if (checkStack(dataFolder, dataStack) || checkStack(dataFolder+"+", dataStack))
	{
		check = MessageBox::Show( MESSAGE_TEXT_ALRINSAFE, MESSAGE_TITLE_ATTENTION, MessageBoxButtons::OKCancel, MessageBoxIcon::Warning);
		if (check == System::Windows::Forms::DialogResult::Cancel)
			return;
	}

	//should it use subfolders?
	check = MessageBox::Show( MESSAGE_TEXT_WANTSAVSUB, MESSAGE_TITLE_QUESTION, MessageBoxButtons::YesNo, MessageBoxIcon::Question);
	if (check == System::Windows::Forms::DialogResult::Cancel)
		return;
	if (check == System::Windows::Forms::DialogResult::Yes)
		dataFolder += "+";

	//select Safe folder
	folderBrowserDialog_sett_select->Description = BROWSER_DESCR_SELSAFE;
	check = folderBrowserDialog_sett_select->ShowDialog();
	if (check == System::Windows::Forms::DialogResult::Cancel)
		return;
	safeFolder = folderBrowserDialog_sett_select->SelectedPath;
	if (safeFolder[safeFolder->Length - 1] != '/' && safeFolder[safeFolder->Length - 1] != '\\')
		safeFolder += "\\";

	//check of using selected folder
	if (dataFolder == safeFolder || dataFolder == safeFolder+"+")
	{
		MessageBox::Show( MESSAGE_TEXT_ONEFOLNUSE, MESSAGE_TITLE_ERROR, MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	if (checkStack(safeFolder, safeStack))
	{
		MessageBox::Show( MESSAGE_TEXT_ALRASSAFE, MESSAGE_TITLE_ERROR, MessageBoxButtons::OK, MessageBoxIcon::Error);
		return;
	}

	listBox_sett_data->Items->Add(dataFolder);
	listBox_sett_safe->Items->Add(safeFolder);
	dataStack.push_back(dataFolder);
	safeStack.push_back(safeFolder);

	//save changes to config
	StreamWriter^ writeFile = gcnew StreamWriter(APP_START_DIR + FILE_CONFIG, true);
	writeFile->WriteLine(dataFolder);
	writeFile->WriteLine(safeFolder);
	writeFile->Close();
}

/*Button_Delete Click - delete file or folder from checking process*/
System::Void SettingForm::button_sett_delete_Click(System::Object^  sender, System::EventArgs^  e)
{
	System::Windows::Forms::DialogResult check;

	check = MessageBox::Show( MESSAGE_TEXT_LINK_DEL( listBox_sett_data->SelectedItem, listBox_sett_safe->SelectedItem ),
		MESSAGE_TITLE_ATTENTION, MessageBoxButtons::OKCancel, MessageBoxIcon::Warning);
	if (check == System::Windows::Forms::DialogResult::Cancel)
		return;

	//does user want to delete Safe folder?
	check = MessageBox::Show( MESSAGE_TEXT_WANTDELLNK, MESSAGE_TITLE_QUESTION, MessageBoxButtons::YesNo, MessageBoxIcon::Question);
	if (check == System::Windows::Forms::DialogResult::Yes)
	{
		panel_wait->Visible = true;

		//deletion
		wchar_t delType = listBox_sett_data->SelectedItem->ToString()[listBox_sett_data->SelectedItem->ToString()->Length - 1];
		if (delType == '+' || delType == '\\' || delType == '/')
		{
			System::IO::DirectoryInfo dirInfo(listBox_sett_safe->SelectedItem->ToString());
			if (dirInfo.Exists)
			{
				dirInfo.Delete(true);
			}
		}
		else
		{
			System::IO::FileInfo fileInfo(listBox_sett_safe->SelectedItem->ToString());
			if(fileInfo.Exists)
			{
				fileInfo.Delete();
			}
		}
		panel_wait->Visible = false;
	}

	int buffIndex = listBox_sett_data->SelectedIndex;
	listBox_sett_data->Items->RemoveAt(buffIndex);
	listBox_sett_safe->Items->RemoveAt(buffIndex);

	dataStack.erase(dataStack.begin() + buffIndex);
	safeStack.erase(safeStack.begin() + buffIndex);

	//rewrite config
	StreamWriter^ writeFile = gcnew StreamWriter(APP_START_DIR + FILE_CONFIG, false);
	for (int iter = 0; iter < listBox_sett_data->Items->Count; iter++)
	{
		writeFile->WriteLine(listBox_sett_data->Items[iter]);
		writeFile->WriteLine(listBox_sett_safe->Items[iter]);
	}
	writeFile->Close();
}

/*Button_Done Click - close Form_Setting*/
System::Void SettingForm::button_sett_back_Click(System::Object^  sender, System::EventArgs^  e) {
	SettingForm::Close();
}

//============= support methods =============//

/*Check if item in stack*/
bool SettingForm::checkStack(System::String^ item, vector<System::String^> stack)
{
	for (int iter = 0; iter < stack.size(); iter++)
	{
		if (item == stack.at(iter))
			return true;
	}
	return false;
}