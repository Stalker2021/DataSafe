#pragma once

#include <cliext/vector>

using cliext::vector;

namespace DataSafe {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SettingForm
	/// </summary>
	public ref class SettingForm : public System::Windows::Forms::Form
	{
	public:
		SettingForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SettingForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::ListBox^  listBox_sett_data;
	protected:

	private: System::Windows::Forms::Label^  label_sett_data;
	private: System::Windows::Forms::ListBox^  listBox_sett_safe;
	private: System::Windows::Forms::Label^  label_sett_safe;
	private: System::Windows::Forms::Button^  button_sett_addFile;
	private: System::Windows::Forms::Button^  button_sett_addFolder;
	private: System::Windows::Forms::Button^  button_sett_back;



	private: System::Windows::Forms::Button^  button_sett_delete;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog_sett_select;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog_sett_sellect;
	private: System::Windows::Forms::Panel^  panel_wait;
	private: System::Windows::Forms::Label^  label_wait;

	private: System::ComponentModel::IContainer^  components;




	protected:

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->listBox_sett_data = (gcnew System::Windows::Forms::ListBox());
			this->label_sett_data = (gcnew System::Windows::Forms::Label());
			this->listBox_sett_safe = (gcnew System::Windows::Forms::ListBox());
			this->label_sett_safe = (gcnew System::Windows::Forms::Label());
			this->button_sett_addFile = (gcnew System::Windows::Forms::Button());
			this->button_sett_addFolder = (gcnew System::Windows::Forms::Button());
			this->button_sett_back = (gcnew System::Windows::Forms::Button());
			this->button_sett_delete = (gcnew System::Windows::Forms::Button());
			this->folderBrowserDialog_sett_select = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->openFileDialog_sett_sellect = (gcnew System::Windows::Forms::OpenFileDialog());
			this->panel_wait = (gcnew System::Windows::Forms::Panel());
			this->label_wait = (gcnew System::Windows::Forms::Label());
			this->panel_wait->SuspendLayout();
			this->SuspendLayout();
			// 
			// listBox_sett_data
			// 
			this->listBox_sett_data->FormattingEnabled = true;
			this->listBox_sett_data->Location = System::Drawing::Point(12, 32);
			this->listBox_sett_data->Name = L"listBox_sett_data";
			this->listBox_sett_data->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->listBox_sett_data->Size = System::Drawing::Size(312, 121);
			this->listBox_sett_data->TabIndex = 0;
			this->listBox_sett_data->SelectedValueChanged += gcnew System::EventHandler(this, &SettingForm::listBox_sett_data_SelectedValueChanged);
			this->listBox_sett_data->DoubleClick += gcnew System::EventHandler(this, &SettingForm::listBox_sett_data_DoubleClick);
			// 
			// label_sett_data
			// 
			this->label_sett_data->AutoSize = true;
			this->label_sett_data->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label_sett_data->Location = System::Drawing::Point(12, 9);
			this->label_sett_data->Name = L"label_sett_data";
			this->label_sett_data->Size = System::Drawing::Size(44, 20);
			this->label_sett_data->TabIndex = 1;
			this->label_sett_data->Text = L"Data";
			// 
			// listBox_sett_safe
			// 
			this->listBox_sett_safe->FormattingEnabled = true;
			this->listBox_sett_safe->Location = System::Drawing::Point(12, 179);
			this->listBox_sett_safe->Name = L"listBox_sett_safe";
			this->listBox_sett_safe->Size = System::Drawing::Size(312, 121);
			this->listBox_sett_safe->TabIndex = 0;
			this->listBox_sett_safe->SelectedValueChanged += gcnew System::EventHandler(this, &SettingForm::listBox_sett_safe_SelectedValueChanged);
			this->listBox_sett_safe->DoubleClick += gcnew System::EventHandler(this, &SettingForm::listBox_sett_safe_DoubleClick);
			// 
			// label_sett_safe
			// 
			this->label_sett_safe->AutoSize = true;
			this->label_sett_safe->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label_sett_safe->Location = System::Drawing::Point(12, 156);
			this->label_sett_safe->Name = L"label_sett_safe";
			this->label_sett_safe->Size = System::Drawing::Size(43, 20);
			this->label_sett_safe->TabIndex = 1;
			this->label_sett_safe->Text = L"Safe";
			// 
			// button_sett_addFile
			// 
			this->button_sett_addFile->Location = System::Drawing::Point(12, 306);
			this->button_sett_addFile->Name = L"button_sett_addFile";
			this->button_sett_addFile->Size = System::Drawing::Size(72, 23);
			this->button_sett_addFile->TabIndex = 2;
			this->button_sett_addFile->Text = L"Add File";
			this->button_sett_addFile->UseVisualStyleBackColor = true;
			this->button_sett_addFile->Click += gcnew System::EventHandler(this, &SettingForm::button_sett_addFile_Click);
			// 
			// button_sett_addFolder
			// 
			this->button_sett_addFolder->Location = System::Drawing::Point(90, 306);
			this->button_sett_addFolder->Name = L"button_sett_addFolder";
			this->button_sett_addFolder->Size = System::Drawing::Size(72, 23);
			this->button_sett_addFolder->TabIndex = 2;
			this->button_sett_addFolder->Text = L"Add Folder";
			this->button_sett_addFolder->UseVisualStyleBackColor = true;
			this->button_sett_addFolder->Click += gcnew System::EventHandler(this, &SettingForm::button_sett_addFolder_Click);
			// 
			// button_sett_back
			// 
			this->button_sett_back->Location = System::Drawing::Point(252, 306);
			this->button_sett_back->Name = L"button_sett_back";
			this->button_sett_back->Size = System::Drawing::Size(72, 23);
			this->button_sett_back->TabIndex = 2;
			this->button_sett_back->Text = L"Back";
			this->button_sett_back->UseVisualStyleBackColor = true;
			this->button_sett_back->Click += gcnew System::EventHandler(this, &SettingForm::button_sett_back_Click);
			// 
			// button_sett_delete
			// 
			this->button_sett_delete->Enabled = false;
			this->button_sett_delete->Location = System::Drawing::Point(174, 306);
			this->button_sett_delete->Name = L"button_sett_delete";
			this->button_sett_delete->Size = System::Drawing::Size(72, 23);
			this->button_sett_delete->TabIndex = 2;
			this->button_sett_delete->Text = L"Delete";
			this->button_sett_delete->UseVisualStyleBackColor = true;
			this->button_sett_delete->Click += gcnew System::EventHandler(this, &SettingForm::button_sett_delete_Click);
			// 
			// openFileDialog_sett_sellect
			// 
			this->openFileDialog_sett_sellect->FileName = L"*.*";
			this->openFileDialog_sett_sellect->Multiselect = true;
			// 
			// panel_wait
			// 
			this->panel_wait->Controls->Add(this->label_wait);
			this->panel_wait->Location = System::Drawing::Point(43, 103);
			this->panel_wait->Name = L"panel_wait";
			this->panel_wait->Size = System::Drawing::Size(253, 137);
			this->panel_wait->TabIndex = 3;
			this->panel_wait->Visible = false;
			// 
			// label_wait
			// 
			this->label_wait->AutoSize = true;
			this->label_wait->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label_wait->Location = System::Drawing::Point(31, 51);
			this->label_wait->Name = L"label_wait";
			this->label_wait->Size = System::Drawing::Size(189, 31);
			this->label_wait->TabIndex = 0;
			this->label_wait->Text = L"Please Wait !!!";
			// 
			// SettingForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(336, 335);
			this->Controls->Add(this->panel_wait);
			this->Controls->Add(this->listBox_sett_safe);
			this->Controls->Add(this->listBox_sett_data);
			this->Controls->Add(this->button_sett_back);
			this->Controls->Add(this->button_sett_addFolder);
			this->Controls->Add(this->button_sett_delete);
			this->Controls->Add(this->button_sett_addFile);
			this->Controls->Add(this->label_sett_safe);
			this->Controls->Add(this->label_sett_data);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"SettingForm";
			this->Text = L"DataSafe Settings";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &SettingForm::SettingForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &SettingForm::SettingForm_Load);
			this->panel_wait->ResumeLayout(false);
			this->panel_wait->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	public:
		System::Drawing::Point startPoint;

	private:
		vector<String^> dataStack;
		vector<String^> safeStack;

	private: System::Void SettingForm_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void SettingForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	private: System::Void listBox_sett_data_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void listBox_sett_safe_SelectedValueChanged(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button_sett_back_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void listBox_sett_data_DoubleClick(System::Object^  sender, System::EventArgs^  e);
	private: System::Void listBox_sett_safe_DoubleClick(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button_sett_addFolder_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button_sett_delete_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button_sett_addFile_Click(System::Object^  sender, System::EventArgs^  e);

	private: bool checkStack(System::String^ item, vector<System::String^> stack);
};
}
