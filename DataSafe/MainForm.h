#pragma once

#include "CheckSizeThread.h"
#include "DifferentFinder.h"

namespace DataSafe {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
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
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button_check;
	protected:
	private: System::Windows::Forms::Button^  button_edit;
	private: System::Windows::Forms::ProgressBar^  progressBar;
	private: System::Windows::Forms::Panel^  panel_data;
	private: System::Windows::Forms::Panel^  panel_safe;
	private: System::Windows::Forms::Label^  label_processSize;
	private: System::Windows::Forms::Label^  label_process;
	private: System::Windows::Forms::CheckBox^  checkBox_addAll;
	private: System::Windows::Forms::Button^  button_eventData;
	private: System::Windows::Forms::Button^  button_eventSafe;
	private: System::Windows::Forms::Label^  label_dataName;

	private: System::Windows::Forms::Label^  label_dataSize;
	private: System::Windows::Forms::Label^  label_data;
	private: System::Windows::Forms::Label^  label_safeName;

	private: System::Windows::Forms::Label^  label_safeSize;


	private: System::Windows::Forms::Label^  label_Safe;
	private: System::Windows::Forms::Button^  button_skip;
	private: System::Windows::Forms::Label^  label_dataChanges;
	private: System::Windows::Forms::Label^  label_safeChanges;
	private: System::Windows::Forms::CheckBox^  checkBox_replaceAll;
	private: System::Windows::Forms::CheckBox^  checkBox_recoverAll;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button_check = (gcnew System::Windows::Forms::Button());
			this->button_edit = (gcnew System::Windows::Forms::Button());
			this->progressBar = (gcnew System::Windows::Forms::ProgressBar());
			this->panel_data = (gcnew System::Windows::Forms::Panel());
			this->label_dataName = (gcnew System::Windows::Forms::Label());
			this->label_dataChanges = (gcnew System::Windows::Forms::Label());
			this->label_dataSize = (gcnew System::Windows::Forms::Label());
			this->label_data = (gcnew System::Windows::Forms::Label());
			this->panel_safe = (gcnew System::Windows::Forms::Panel());
			this->label_safeName = (gcnew System::Windows::Forms::Label());
			this->label_safeChanges = (gcnew System::Windows::Forms::Label());
			this->label_safeSize = (gcnew System::Windows::Forms::Label());
			this->label_Safe = (gcnew System::Windows::Forms::Label());
			this->label_processSize = (gcnew System::Windows::Forms::Label());
			this->label_process = (gcnew System::Windows::Forms::Label());
			this->checkBox_addAll = (gcnew System::Windows::Forms::CheckBox());
			this->button_eventData = (gcnew System::Windows::Forms::Button());
			this->button_eventSafe = (gcnew System::Windows::Forms::Button());
			this->button_skip = (gcnew System::Windows::Forms::Button());
			this->checkBox_replaceAll = (gcnew System::Windows::Forms::CheckBox());
			this->checkBox_recoverAll = (gcnew System::Windows::Forms::CheckBox());
			this->panel_data->SuspendLayout();
			this->panel_safe->SuspendLayout();
			this->SuspendLayout();
			// 
			// button_check
			// 
			this->button_check->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button_check->Location = System::Drawing::Point(12, 12);
			this->button_check->Name = L"button_check";
			this->button_check->Size = System::Drawing::Size(152, 29);
			this->button_check->TabIndex = 0;
			this->button_check->Text = L"Check Differences";
			this->button_check->UseVisualStyleBackColor = true;
			this->button_check->Click += gcnew System::EventHandler(this, &MainForm::button_check_Click);
			// 
			// button_edit
			// 
			this->button_edit->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button_edit->Location = System::Drawing::Point(172, 12);
			this->button_edit->Name = L"button_edit";
			this->button_edit->Size = System::Drawing::Size(152, 29);
			this->button_edit->TabIndex = 1;
			this->button_edit->Text = L"Edit Checking";
			this->button_edit->UseVisualStyleBackColor = true;
			this->button_edit->Click += gcnew System::EventHandler(this, &MainForm::button_edit_Click);
			// 
			// progressBar
			// 
			this->progressBar->Location = System::Drawing::Point(11, 102);
			this->progressBar->Name = L"progressBar";
			this->progressBar->Size = System::Drawing::Size(312, 23);
			this->progressBar->TabIndex = 2;
			// 
			// panel_data
			// 
			this->panel_data->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel_data->Controls->Add(this->label_dataName);
			this->panel_data->Controls->Add(this->label_dataChanges);
			this->panel_data->Controls->Add(this->label_dataSize);
			this->panel_data->Controls->Add(this->label_data);
			this->panel_data->Enabled = false;
			this->panel_data->Location = System::Drawing::Point(12, 163);
			this->panel_data->Name = L"panel_data";
			this->panel_data->Size = System::Drawing::Size(152, 131);
			this->panel_data->TabIndex = 3;
			this->panel_data->DoubleClick += gcnew System::EventHandler(this, &MainForm::panel_data_DoubleClick);
			// 
			// label_dataName
			// 
			this->label_dataName->Location = System::Drawing::Point(3, 57);
			this->label_dataName->Name = L"label_dataName";
			this->label_dataName->Size = System::Drawing::Size(142, 70);
			this->label_dataName->TabIndex = 1;
			this->label_dataName->Text = L"Name:";
			this->label_dataName->DoubleClick += gcnew System::EventHandler(this, &MainForm::panel_data_DoubleClick);
			// 
			// label_dataChanges
			// 
			this->label_dataChanges->Location = System::Drawing::Point(3, 43);
			this->label_dataChanges->Name = L"label_dataChanges";
			this->label_dataChanges->Size = System::Drawing::Size(142, 14);
			this->label_dataChanges->TabIndex = 1;
			this->label_dataChanges->Text = L"Change:";
			this->label_dataChanges->DoubleClick += gcnew System::EventHandler(this, &MainForm::panel_data_DoubleClick);
			// 
			// label_dataSize
			// 
			this->label_dataSize->Location = System::Drawing::Point(3, 29);
			this->label_dataSize->Name = L"label_dataSize";
			this->label_dataSize->Size = System::Drawing::Size(142, 14);
			this->label_dataSize->TabIndex = 1;
			this->label_dataSize->Text = L"Size:";
			this->label_dataSize->DoubleClick += gcnew System::EventHandler(this, &MainForm::panel_data_DoubleClick);
			// 
			// label_data
			// 
			this->label_data->AutoSize = true;
			this->label_data->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label_data->Location = System::Drawing::Point(3, 0);
			this->label_data->Name = L"label_data";
			this->label_data->Size = System::Drawing::Size(41, 16);
			this->label_data->TabIndex = 0;
			this->label_data->Text = L"Data";
			this->label_data->DoubleClick += gcnew System::EventHandler(this, &MainForm::panel_data_DoubleClick);
			// 
			// panel_safe
			// 
			this->panel_safe->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->panel_safe->Controls->Add(this->label_safeName);
			this->panel_safe->Controls->Add(this->label_safeChanges);
			this->panel_safe->Controls->Add(this->label_safeSize);
			this->panel_safe->Controls->Add(this->label_Safe);
			this->panel_safe->Enabled = false;
			this->panel_safe->Location = System::Drawing::Point(171, 163);
			this->panel_safe->Name = L"panel_safe";
			this->panel_safe->Size = System::Drawing::Size(152, 131);
			this->panel_safe->TabIndex = 3;
			this->panel_safe->DoubleClick += gcnew System::EventHandler(this, &MainForm::panel_safe_DoubleClick);
			// 
			// label_safeName
			// 
			this->label_safeName->Location = System::Drawing::Point(3, 57);
			this->label_safeName->Name = L"label_safeName";
			this->label_safeName->Size = System::Drawing::Size(142, 70);
			this->label_safeName->TabIndex = 1;
			this->label_safeName->Text = L"Name:";
			this->label_safeName->DoubleClick += gcnew System::EventHandler(this, &MainForm::panel_safe_DoubleClick);
			// 
			// label_safeChanges
			// 
			this->label_safeChanges->Location = System::Drawing::Point(3, 43);
			this->label_safeChanges->Name = L"label_safeChanges";
			this->label_safeChanges->Size = System::Drawing::Size(142, 14);
			this->label_safeChanges->TabIndex = 1;
			this->label_safeChanges->Text = L"Change:";
			this->label_safeChanges->DoubleClick += gcnew System::EventHandler(this, &MainForm::panel_safe_DoubleClick);
			// 
			// label_safeSize
			// 
			this->label_safeSize->Location = System::Drawing::Point(3, 29);
			this->label_safeSize->Name = L"label_safeSize";
			this->label_safeSize->Size = System::Drawing::Size(142, 14);
			this->label_safeSize->TabIndex = 1;
			this->label_safeSize->Text = L"Size:";
			this->label_safeSize->DoubleClick += gcnew System::EventHandler(this, &MainForm::panel_safe_DoubleClick);
			// 
			// label_Safe
			// 
			this->label_Safe->AutoSize = true;
			this->label_Safe->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->label_Safe->Location = System::Drawing::Point(3, 0);
			this->label_Safe->Name = L"label_Safe";
			this->label_Safe->Size = System::Drawing::Size(40, 16);
			this->label_Safe->TabIndex = 0;
			this->label_Safe->Text = L"Safe";
			this->label_Safe->DoubleClick += gcnew System::EventHandler(this, &MainForm::panel_safe_DoubleClick);
			// 
			// label_processSize
			// 
			this->label_processSize->Location = System::Drawing::Point(11, 128);
			this->label_processSize->Name = L"label_processSize";
			this->label_processSize->Size = System::Drawing::Size(312, 13);
			this->label_processSize->TabIndex = 4;
			this->label_processSize->Text = L"0/0 (MB)";
			this->label_processSize->TextAlign = System::Drawing::ContentAlignment::TopRight;
			// 
			// label_process
			// 
			this->label_process->Location = System::Drawing::Point(14, 86);
			this->label_process->Name = L"label_process";
			this->label_process->Size = System::Drawing::Size(306, 13);
			this->label_process->TabIndex = 4;
			this->label_process->Text = L"Waiting...";
			this->label_process->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// checkBox_addAll
			// 
			this->checkBox_addAll->AutoSize = true;
			this->checkBox_addAll->Location = System::Drawing::Point(12, 47);
			this->checkBox_addAll->Name = L"checkBox_addAll";
			this->checkBox_addAll->Size = System::Drawing::Size(113, 17);
			this->checkBox_addAll->TabIndex = 5;
			this->checkBox_addAll->Text = L"add all files to safe";
			this->checkBox_addAll->UseVisualStyleBackColor = true;
			// 
			// button_eventData
			// 
			this->button_eventData->Enabled = false;
			this->button_eventData->Location = System::Drawing::Point(12, 300);
			this->button_eventData->Name = L"button_eventData";
			this->button_eventData->Size = System::Drawing::Size(125, 23);
			this->button_eventData->TabIndex = 7;
			this->button_eventData->Text = L"Copy from Data";
			this->button_eventData->UseVisualStyleBackColor = true;
			this->button_eventData->Click += gcnew System::EventHandler(this, &MainForm::button_eventData_Click);
			// 
			// button_eventSafe
			// 
			this->button_eventSafe->Enabled = false;
			this->button_eventSafe->Location = System::Drawing::Point(200, 300);
			this->button_eventSafe->Name = L"button_eventSafe";
			this->button_eventSafe->Size = System::Drawing::Size(124, 23);
			this->button_eventSafe->TabIndex = 7;
			this->button_eventSafe->Text = L"Copy from Safe";
			this->button_eventSafe->UseVisualStyleBackColor = true;
			this->button_eventSafe->Click += gcnew System::EventHandler(this, &MainForm::button_eventSafe_Click);
			// 
			// button_skip
			// 
			this->button_skip->Enabled = false;
			this->button_skip->Location = System::Drawing::Point(143, 300);
			this->button_skip->Name = L"button_skip";
			this->button_skip->Size = System::Drawing::Size(51, 23);
			this->button_skip->TabIndex = 7;
			this->button_skip->Text = L"Skip";
			this->button_skip->UseVisualStyleBackColor = true;
			this->button_skip->Click += gcnew System::EventHandler(this, &MainForm::button_skip_Click);
			// 
			// checkBox_replaceAll
			// 
			this->checkBox_replaceAll->AutoSize = true;
			this->checkBox_replaceAll->Location = System::Drawing::Point(172, 47);
			this->checkBox_replaceAll->Name = L"checkBox_replaceAll";
			this->checkBox_replaceAll->Size = System::Drawing::Size(136, 17);
			this->checkBox_replaceAll->TabIndex = 8;
			this->checkBox_replaceAll->Text = L"replace all different files";
			this->checkBox_replaceAll->UseVisualStyleBackColor = true;
			// 
			// checkBox_recoverAll
			// 
			this->checkBox_recoverAll->AutoSize = true;
			this->checkBox_recoverAll->Location = System::Drawing::Point(12, 66);
			this->checkBox_recoverAll->Name = L"checkBox_recoverAll";
			this->checkBox_recoverAll->Size = System::Drawing::Size(115, 17);
			this->checkBox_recoverAll->TabIndex = 5;
			this->checkBox_recoverAll->Text = L"recover all lost files";
			this->checkBox_recoverAll->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(336, 335);
			this->Controls->Add(this->checkBox_replaceAll);
			this->Controls->Add(this->button_skip);
			this->Controls->Add(this->button_eventSafe);
			this->Controls->Add(this->button_eventData);
			this->Controls->Add(this->checkBox_recoverAll);
			this->Controls->Add(this->checkBox_addAll);
			this->Controls->Add(this->label_process);
			this->Controls->Add(this->label_processSize);
			this->Controls->Add(this->panel_safe);
			this->Controls->Add(this->panel_data);
			this->Controls->Add(this->progressBar);
			this->Controls->Add(this->button_edit);
			this->Controls->Add(this->button_check);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"DataSafe";
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &MainForm::MainForm_FormClosing);
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->panel_data->ResumeLayout(false);
			this->panel_data->PerformLayout();
			this->panel_safe->ResumeLayout(false);
			this->panel_safe->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}

	private: System::IO::StreamReader^ readFile;
			 CheckSize^ checkSize;
			 System::Threading::Thread^ checkDifferentThread = nullptr;

	private: System::Void MainForm_Load(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button_edit_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button_check_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void MainForm_FormClosing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e);
	private: System::Void button_eventData_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button_eventSafe_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void button_skip_Click(System::Object^  sender, System::EventArgs^  e);
	private: System::Void panel_data_DoubleClick(System::Object^  sender, System::EventArgs^  e);
	private: System::Void panel_safe_DoubleClick(System::Object^  sender, System::EventArgs^  e);
	
	private: System::Void eventButtonsDisable();
	private: System::Void eventButtonsEnable(System::IO::FileInfo^ dataFile, System::String^ safePath);
	private: System::Void eventButtonsEnable(System::String^ dataPath, System::IO::FileInfo^ safeFile);
	private: System::Void eventButtonsEnable(System::IO::FileInfo^ dataFile, System::IO::FileInfo^ safeFile);
	private: System::Void checkDifferences();
	private: System::Void checkSubFolderDifferences(System::String^ dataPath, System::String^ safePath);

};
}
