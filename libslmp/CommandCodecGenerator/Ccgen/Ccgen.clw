; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CCcgenApp
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "ccgen.h"
LastPage=0

ClassCount=11
Class1=CCcgenApp
Class2=CAboutDlg
Class3=CCcgenDoc
Class4=CCcgenView
Class5=CGlobalPropsView
Class6=CLeftView
Class7=CMainFrame

ResourceCount=9
Resource1=IDD_CCGEN_FORM (English (U.S.))
Resource2=IDD_NEW_CMDELEM (English (U.S.))
Resource3=IDD_ABOUTBOX (English (U.S.))
Resource4=IDR_TREE_IMAGE_LIST (English (U.S.))
Class8=CGenCodeView
Resource5=IDD_GLOBALPROPS_FORM (English (U.S.))
Class9=CCommandView
Resource6=IDR_CMDTREE_IMAGE_LIST (English (U.S.))
Resource7=IDD_NEW_COMMAND (English (U.S.))
Class10=CNewCmdDlg
Resource8=IDR_MAINFRAME (English (U.S.))
Class11=CNewCmdElemDlg
Resource9=IDD_COMMAND_FORM (English (U.S.))

[CLS:CCcgenApp]
Type=0
BaseClass=CWinApp
HeaderFile=Ccgen.h
ImplementationFile=Ccgen.cpp
LastObject=CCcgenApp

[CLS:CAboutDlg]
Type=0
BaseClass=CDialog
HeaderFile=Ccgen.cpp
ImplementationFile=Ccgen.cpp
LastObject=CAboutDlg

[CLS:CCcgenDoc]
Type=0
BaseClass=CDocument
HeaderFile=CcgenDoc.h
ImplementationFile=CcgenDoc.cpp
Filter=N
VirtualFilter=DC
LastObject=ID_GENERATE_EXPDEF

[CLS:CCcgenView]
Type=0
BaseClass=CFormView
HeaderFile=CcgenView.h
ImplementationFile=CcgenView.cpp
LastObject=CCcgenView
Filter=D
VirtualFilter=VWC

[CLS:CGlobalPropsView]
Type=0
BaseClass=CFormView
HeaderFile=GlobalPropsView.h
ImplementationFile=GlobalPropsView.cpp
LastObject=IDC_INCLUDING_ORDINAL
Filter=D
VirtualFilter=VWC

[CLS:CLeftView]
Type=0
BaseClass=CTreeView
HeaderFile=LeftView.h
ImplementationFile=LeftView.cpp
LastObject=ID_MOVE_UP
Filter=C
VirtualFilter=VWC

[CLS:CMainFrame]
Type=0
BaseClass=CFrameWnd
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
VirtualFilter=fWC
LastObject=CMainFrame

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg

[DLG:IDD_CCGEN_FORM]
Type=1
Class=CCcgenView

[TB:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_NEW_COMMAND
Command5=ID_EDIT_CLEAR
Command6=ID_MOVE_UP
Command7=ID_MOVE_DOWN
Command8=ID_GENERATE_TYPEDEF
Command9=ID_GENERATE_HEADER
Command10=ID_GENERATE_SOURCE
Command11=ID_GENERATE_EXPDEF
Command12=ID_APP_ABOUT
CommandCount=12

[MNU:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_SAVE_AS
Command5=ID_FILE_MRU_FILE1
Command6=ID_APP_EXIT
Command7=ID_NEW_COMMAND
Command8=ID_EDIT_CLEAR
Command9=ID_MOVE_UP
Command10=ID_MOVE_DOWN
Command11=ID_VIEW_TOOLBAR
Command12=ID_VIEW_STATUS_BAR
Command13=ID_GENERATE_TYPEDEF
Command14=ID_GENERATE_HEADER
Command15=ID_GENERATE_SOURCE
Command16=ID_GENERATE_EXPDEF
Command17=ID_APP_ABOUT
CommandCount=17

[DLG:IDD_ABOUTBOX (English (U.S.))]
Type=1
Class=?
ControlCount=4
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889

[DLG:IDD_CCGEN_FORM (English (U.S.))]
Type=1
Class=?
ControlCount=0

[ACL:IDR_MAINFRAME (English (U.S.))]
Type=1
Class=?
Command1=ID_EDIT_CLEAR
Command2=ID_FILE_NEW
Command3=ID_NEW_COMMAND
Command4=ID_FILE_OPEN
Command5=ID_FILE_SAVE
Command6=ID_NEXT_PANE
Command7=ID_PREV_PANE
CommandCount=7

[CLS:CGenCodeView]
Type=0
HeaderFile=GenCodeView.h
ImplementationFile=GenCodeView.cpp
BaseClass=CEditView
Filter=C
VirtualFilter=VWC
LastObject=CGenCodeView

[CLS:CCommandView]
Type=0
HeaderFile=CommandView.h
ImplementationFile=CommandView.cpp
BaseClass=CFormView
Filter=W
LastObject=IDC_ENABLE_SIZE_FIELD
VirtualFilter=VWC

[TB:IDR_CMDTREE_IMAGE_LIST (English (U.S.))]
Type=1
Class=?
Command1=ID_BUTTON32777
Command2=ID_BUTTON32776
Command3=ID_BUTTON32778
CommandCount=3

[DLG:IDD_NEW_COMMAND (English (U.S.))]
Type=1
Class=CNewCmdDlg
ControlCount=4
Control1=IDC_COMMAND_NAME,edit,1350631552
Control2=IDOK,button,1342242817
Control3=IDCANCEL,button,1342242816
Control4=IDC_STATIC,static,1342308352

[CLS:CNewCmdDlg]
Type=0
HeaderFile=NewCmdDlg.h
ImplementationFile=NewCmdDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=CNewCmdDlg
VirtualFilter=dWC

[DLG:IDD_GLOBALPROPS_FORM (English (U.S.))]
Type=1
Class=CGlobalPropsView
ControlCount=13
Control1=IDC_EDIT_DESCRIPTION,edit,1353781508
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT_COMMAND_HEADER,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_STATIC,static,1342308352
Control7=IDC_EDIT_CODEC_HEADER,edit,1350631552
Control8=IDC_EDIT_CODEC_SOURCE,edit,1350631552
Control9=IDC_STATIC,button,1342177287
Control10=IDC_STATIC,button,1342177287
Control11=IDC_INCLUDING_ORDINAL,button,1342242819
Control12=IDC_STATIC,static,1342308352
Control13=IDC_ORDINAL_BEGIN,edit,1350631552

[TB:IDR_TREE_IMAGE_LIST (English (U.S.))]
Type=1
Class=?
Command1=ID_BUTTON32772
Command2=ID_BUTTON32773
Command3=ID_BUTTON32775
Command4=ID_BUTTON32782
CommandCount=4

[DLG:IDD_NEW_CMDELEM (English (U.S.))]
Type=1
Class=CNewCmdElemDlg
ControlCount=8
Control1=IDC_NAME,edit,1350631552
Control2=IDC_TYPE,button,1342308361
Control3=IDC_FIELD,button,1342177289
Control4=IDC_FIELD_ROOT,button,1342177289
Control5=IDOK,button,1342242817
Control6=IDCANCEL,button,1342242816
Control7=IDC_STATIC,button,1342177287
Control8=IDC_STATIC,static,1342308352

[CLS:CNewCmdElemDlg]
Type=0
HeaderFile=NewCmdElemDlg.h
ImplementationFile=NewCmdElemDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_NAME
VirtualFilter=dWC

[DLG:IDD_COMMAND_FORM (English (U.S.))]
Type=1
Class=CCommandView
ControlCount=45
Control1=IDC_COMMAND_NAME,edit,1350631552
Control2=IDC_STRUCT_TYPE,edit,1350631552
Control3=IDC_AUTO_STRUCT_TYPE,button,1342242816
Control4=IDC_COMMAND_BRIEF,edit,1353781252
Control5=IDC_ADDR_LEN_DEP,button,1342242819
Control6=IDC_STREAM_TYPE_SUPPORTED,combobox,1344339971
Control7=IDC_CMD_TREE,SysTreeView32,1350631459
Control8=IDC_NEW,button,1342242816
Control9=IDC_DELETE,button,1342242816
Control10=IDC_MOVE_UP,button,1342242816
Control11=IDC_MOVE_DOWN,button,1342242816
Control12=IDC_FIELD_NAME,edit,1350631552
Control13=IDC_FIELD_BRIEF,edit,1350631552
Control14=IDC_VARIABLE_SIZE,button,1342242819
Control15=IDC_STRING_FIELD_VAR_SIZE,button,1342242819
Control16=IDC_ENABLE_SIZE_FIELD,button,1342242819
Control17=IDC_SIZE_FIELD,edit,1350631552
Control18=IDC_SIZE_BIN_16B,edit,1350639744
Control19=IDC_STRING_FIELD_BIN_16B,button,1342242819
Control20=IDC_SIZE_ASC_16B,edit,1350639744
Control21=IDC_STRING_FIELD_ASC_16B,button,1342242819
Control22=IDC_SIZE_BIN_32B,edit,1350639744
Control23=IDC_STRING_FIELD_BIN_32B,button,1342242819
Control24=IDC_SIZE_ASC_32B,edit,1350639744
Control25=IDC_STRING_FIELD_ASC_32B,button,1342242819
Control26=IDC_AVAIL_BIN,button,1342308361
Control27=IDC_AVAIL_ASC,button,1342177289
Control28=IDC_AVAIL_BOTH,button,1342177289
Control29=IDC_STATIC,static,1342308352
Control30=IDC_STATIC,static,1342308352
Control31=IDC_STATIC,static,1342308352
Control32=IDC_STATIC,button,1342177287
Control33=IDC_STATIC,button,1342177287
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,button,1342177287
Control37=IDC_STATIC,static,1342308352
Control38=IDC_STATIC,static,1342308352
Control39=IDC_STATIC,button,1342177287
Control40=IDC_STATIC,button,1342177287
Control41=IDC_STATIC,static,1342308352
Control42=IDC_STATIC,static,1342308352
Control43=IDC_STATIC,button,1342177287
Control44=IDC_STATIC,static,1342308352
Control45=IDC_STATIC,static,1342181383

