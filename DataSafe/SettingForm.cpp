#include "SettingForm.h"

using DataSafe::SettingForm;
using System::IO::StreamReader;
using System::IO::StreamWriter;
using System::Windows::Forms::MessageBox;
using System::Windows::Forms::DialogResult;

System::Void SettingForm::SettingForm_Load(System::Object^  sender, System::EventArgs^  e) {
	SettingForm::Location = startPoint;
	StreamReader^ readFile = gcnew StreamReader(Application::StartupPath + "\\config.ds");
	String^ check;
	while (true)
	{
		check = readFile->ReadLine();
		if (!check || check == "")
			break;
		listBox_sett_data->Items->Add(check);
		dataStack.push_back(check);
		check = readFile->ReadLine();
		listBox_sett_safe->Items->Add(check);
		safeStack.push_back(check);
	}
	readFile->Close();
}

System::Void SettingForm::SettingForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e) {
	startPoint = SettingForm::Location;
}

System::Void SettingForm::listBox_sett_data_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) {
	if (listBox_sett_safe->SelectedIndex != listBox_sett_data->SelectedIndex)
		listBox_sett_safe->SelectedIndex = listBox_sett_data->SelectedIndex;
	if (listBox_sett_data->SelectedIndex == -1)
		button_sett_delete->Enabled = false;
	else
		button_sett_delete->Enabled = true;
}

System::Void SettingForm::listBox_sett_safe_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e) {
	if (listBox_sett_data->SelectedIndex != listBox_sett_safe->SelectedIndex)
		listBox_sett_data->SelectedIndex = listBox_sett_safe->SelectedIndex;
	if (listBox_sett_safe->SelectedIndex == -1)
		button_sett_delete->Enabled = false;
	else
		button_sett_delete->Enabled = true;
}

System::Void SettingForm::button_sett_back_Click(System::Object^  sender, System::EventArgs^  e) {
	SettingForm::Close();
}

System::Void SettingForm::listBox_sett_data_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	if (listBox_sett_data->SelectedIndex >= 0)
		MessageBox::Show("Data:\n" + listBox_sett_data->Items[listBox_sett_data->SelectedIndex] +
			"\n\nSafe:\n" + listBox_sett_safe->Items[listBox_sett_data->SelectedIndex], "Selected Items");
}

System::Void SettingForm::listBox_sett_safe_DoubleClick(System::Object^  sender, System::EventArgs^  e) {
	if (listBox_sett_safe->SelectedIndex >= 0)
		MessageBox::Show("Data:\n" + listBox_sett_data->Items[listBox_sett_safe->SelectedIndex] +
			"\n\nSafe:\n" + listBox_sett_safe->Items[listBox_sett_safe->SelectedIndex], "Selected Items");
}

System::Void SettingForm::button_sett_addFolder_Click(System::Object^  sender, System::EventArgs^  e) {
	String^ dataFolder;
	String^ safeFolder;
	System::Windows::Forms::DialogResult check;
	folderBrowserDialog_sett_select->Description = "Select Data Folder";
	check = folderBrowserDialog_sett_select->ShowDialog();
	if (check == System::Windows::Forms::DialogResult::Cancel)
		return;
	dataFolder = folderBrowserDialog_sett_select->SelectedPath;
	if (dataFolder[dataFolder->Length - 1] != '/' && dataFolder[dataFolder->Length - 1] != '\\')
		dataFolder += "\\";

	if (checkStack(dataFolder, dataStack) || checkStack(dataFolder+"+", dataStack))
	{
		check = MessageBox::Show("Selected folder already in Safe!", "Attention",
			System::Windows::Forms::MessageBoxButtons::OKCancel, System::Windows::Forms::MessageBoxIcon::Warning);
		if (check == System::Windows::Forms::DialogResult::Cancel)
			return;
	}

	check = MessageBox::Show("You want to save the folders in selected directory?", "Question",
		System::Windows::Forms::MessageBoxButtons::YesNo, System::Windows::Forms::MessageBoxIcon::Question);
	if (check == System::Windows::Forms::DialogResult::Cancel)
		return;
	if (check == System::Windows::Forms::DialogResult::Yes)
		dataFolder += "+";

	folderBrowserDialog_sett_select->Description = "Select Safe Folder";
	check = folderBrowserDialog_sett_select->ShowDialog();
	if (check == System::Windows::Forms::DialogResult::Cancel)
		return;
	safeFolder = folderBrowserDialog_sett_select->SelectedPath;
	if (safeFolder[safeFolder->Length - 1] != '/' && safeFolder[safeFolder->Length - 1] != '\\')
		safeFolder += "\\";

	if (dataFolder == safeFolder || dataFolder == safeFolder+"+")
	{
		MessageBox::Show("One folder cannot be used for Data and Safe!", "Error",
			System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
		return;
	}

	if (checkStack(safeFolder, safeStack))
	{
		MessageBox::Show("Selected folder already using as Safe!", "Error",
			System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
		return;
	}

	listBox_sett_data->Items->Add(dataFolder);
	listBox_sett_safe->Items->Add(safeFolder);
	dataStack.push_back(dataFolder);
	safeStack.push_back(safeFolder);
	StreamWriter^ writeFile = gcnew StreamWriter(Application::StartupPath + "\\config.ds", true);
	writeFile->WriteLine(dataFolder);
	writeFile->WriteLine(safeFolder);
	writeFile->Close();
}

System::Void SettingForm::button_sett_delete_Click(System::Object^  sender, System::EventArgs^  e)
{
	System::Windows::Forms::DialogResult check;

	check = MessageBox::Show("Safe link will be deleted:\n\n" + listBox_sett_data->SelectedItem + "\n" + listBox_sett_safe->SelectedItem, "Attention",
		System::Windows::Forms::MessageBoxButtons::OKCancel, System::Windows::Forms::MessageBoxIcon::Warning);
	if (check == System::Windows::Forms::DialogResult::Cancel)
		return;

	check = MessageBox::Show("You want delete files in Safe by the link?", "Question",
	System::Windows::Forms::MessageBoxButtons::YesNo, System::Windows::Forms::MessageBoxIcon::Question);
	if (check == System::Windows::Forms::DialogResult::Yes)
	{
		panel_wait->Visible = true;

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

	StreamWriter^ writeFile = gcnew StreamWriter(Application::StartupPath + "\\config.ds", false);
	for (int iter = 0; iter < listBox_sett_data->Items->Count; iter++)
	{
		writeFile->WriteLine(listBox_sett_data->Items[iter]);
		writeFile->WriteLine(listBox_sett_safe->Items[iter]);
	}
	writeFile->Close();
}

System::Void SettingForm::button_sett_addFile_Click(System::Object^  sender, System::EventArgs^  e)
{
	openFileDialog_sett_sellect->Title = "Select Data Files";

	System::Windows::Forms::DialogResult check;
	check = openFileDialog_sett_sellect->ShowDialog();
	if (check == System::Windows::Forms::DialogResult::Cancel)
		return;
	for (int iter = 0; iter < openFileDialog_sett_sellect->FileNames->Length; iter++)
	{
		if (checkStack(openFileDialog_sett_sellect->FileNames[iter]->ToString(), dataStack))
		{
			check = MessageBox::Show("Some selected files already in Safe!", "Attention",
				System::Windows::Forms::MessageBoxButtons::OKCancel, System::Windows::Forms::MessageBoxIcon::Warning);
			if (check == System::Windows::Forms::DialogResult::Cancel)
				return;
		}
	}

	folderBrowserDialog_sett_select->Description = "Select Safe Folder";
	check = folderBrowserDialog_sett_select->ShowDialog();
	if (check == System::Windows::Forms::DialogResult::Cancel)
		return;
	String^ safeDirect;
	safeDirect = folderBrowserDialog_sett_select->SelectedPath;
	if (safeDirect[safeDirect->Length - 1] != '/' && safeDirect[safeDirect->Length - 1] != '\\')
		safeDirect += "\\";

	if (openFileDialog_sett_sellect->FileNames[0] == safeDirect + openFileDialog_sett_sellect->SafeFileNames[0])
	{
		MessageBox::Show("One folder cannot be used for Data and Safe!", "Error",
			System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
		return;
	}

	if (checkStack(safeDirect, safeStack))
	{
		MessageBox::Show("Selected folder already using as Safe!", "Error",
			System::Windows::Forms::MessageBoxButtons::OK, System::Windows::Forms::MessageBoxIcon::Error);
		return;
	}
	
	StreamWriter^ writeFile = gcnew StreamWriter(Application::StartupPath + "\\config.ds", true);
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

bool SettingForm::checkStack(System::String^ item, vector<System::String^> stack)
{
	for (int iter = 0; iter < stack.size(); iter++)
	{
		if (item == stack.at(iter))
			return true;
	}
	return false;
}