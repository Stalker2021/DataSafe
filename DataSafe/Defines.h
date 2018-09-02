#pragma once

#define EMPTY_STRING			""

#define FILE_SOUND_DIFFER_FOUND	"\\difference_found.wav"
#define FILE_SOUND_CHECK_DONE	"\\checking_done.wav"
#define FILE_CONFIG				"\\config.ds"

#define PROCESS_CLEAR			"0 / 0 files"

#define LABEL_CHAPTER_SIZE		"Size: "
#define LABEL_CHAPTER_CHANGE	"Change: "
#define LABEL_CHAPTER_NAME		"Name: "
#define LABEL_ACTION_DEL_SAFE	"Delete from Safe"
#define LABEL_ACTION_DEL_DATA	"Delete from Data"
#define LABEL_ACTION_COPY_SAFE	"Copy from Safe"
#define LABEL_ACTION_COPY_DATA	"Copy from Data"
#define LABEL_PRICESSING		"Processing..."
#define LABEL_BACK_CHECK		"<-- back check"
#define LABEL_CHECK_DONE		"Checking Done!"

#define LABEL_CALCUL( X )		"Calculation: " + X + " files"
#define LABEL_CALCUL_RES( X )	"0 / " + X + " files"

#define BROWSER_DESCR_SELDATAF	"Select Data Files"
#define BROWSER_DESCR_SELDATAD	"Select Data Folder"
#define BROWSER_DESCR_SELSAFE	"Select Safe Folder"

#define MESSAGE_TITLE_ERROR		"Error"
#define MESSAGE_TITLE_ATTENTION	"Attention"
#define MESSAGE_TITLE_QUESTION	"Question"
#define MESSAGE_TITLE_SELECTITM	"Selected Items"

#define MESSAGE_TEXT_DELFNREST	"Deleted file cannot be restored!"
#define MESSAGE_TEXT_ALRINSAFE	"Selected folder already in Safe!"
#define MESSAGE_TEXT_WANTSAVSUB	"You want to save the folders in selected directory?"
#define MESSAGE_TEXT_ONEFOLNUSE	"One folder cannot be used for Data and Safe!"
#define MESSAGE_TEXT_ALRASSAFE	"Selected folder already using as Safe!"
#define MESSAGE_TEXT_WANTDELLNK	"You want delete files in Safe by the link?"
#define MESSAGE_TEXT_FEXISTSAFE	"Some selected files already in Safe!"
#define MESSAGE_TEXT_DIRNFORDS	"One folder cannot be used for Data and Safe!"

#define MESSAGE_TEXT_FILE_NEXIST( X )		"File \"" + X + "\" not exist!"
#define MESSAGE_TEXT_DIR_NEXIST( X )		"Directory \"" + X + "\" not exist!"
#define MESSAGE_TEXT_PROGRESS( NUM, OF )	NUM + " / " + OF + " files"
#define MESSAGE_TEXT_DAT_SAF_SELECT( D, S )	"Data:\n" + D + "\n\nSafe:\n" + S
#define MESSAGE_TEXT_LINK_DEL( D, S )		"Safe link will be deleted:\n\n" + D + "\n" + S