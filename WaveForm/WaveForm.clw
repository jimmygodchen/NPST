; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CWaveFormView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "WaveForm.h"
LastPage=0

ClassCount=8
Class1=CWaveFormApp
Class2=CWaveFormDoc
Class3=CWaveFormView
Class4=CMainFrame

ResourceCount=12
Resource1=IDD_ABOUTBOX
Resource2=IDD_WAVEFORM_FORM
Resource3=IDR_PASTE_MENU
Resource7=IDR_CONTEXT_MENU
Resource8=IDR_POPUP_MDITABS
Resource9=IDR_POPUP_DROP_MDITABS
Resource10=IDD_DLG_DISPLAYINFO
Class5=CChildFrame
Class6=CAboutDlg
Resource4=IDR_THEME_MENU
Resource5=IDR_WAVEFOTYPE
Resource6=IDR_WINDOWS_MENU
Class7=CMyDebug
Resource11=IDD_DLG_DEBUG
Class8=CMyDisPlayInfo
Resource12=IDR_MAINFRAME

[CLS:CWaveFormApp]
Type=0
HeaderFile=WaveForm.h
ImplementationFile=WaveForm.cpp
Filter=N

[CLS:CWaveFormDoc]
Type=0
HeaderFile=WaveFormDoc.h
ImplementationFile=WaveFormDoc.cpp
Filter=N

[CLS:CWaveFormView]
Type=0
HeaderFile=WaveFormView.h
ImplementationFile=WaveFormView.cpp
Filter=D
LastObject=IDC_CHART
BaseClass=CFormView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=CMainFrame


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M


[CLS:CAboutDlg]
Type=0
HeaderFile=WaveForm.cpp
ImplementationFile=WaveForm.cpp
Filter=D

[DLG:IDD_ABOUTBOX]
Type=1
Class=?
ControlCount=6
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_COMPANY_URL,button,1073807360
Control6=IDC_STATIC,static,1073872896

[MNU:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_STATUS_BAR
Command7=ID_VIEW_APPLOOK_2000
Command8=ID_VIEW_APPLOOK_XP
Command9=ID_VIEW_APPLOOK_2003
Command10=ID_VIEW_APPLOOK_VS2005
Command11=ID_VIEW_APPLOOK_WIN_XP
Command12=ID_VIEW_APPLOOK_2007
Command13=ID_VIEW_APPLOOK_2007_1
Command14=ID_VIEW_APPLOOK_2007_2
Command15=ID_VIEW_APPLOOK_2007_3
Command16=ID_VIEW_APPLOOK_VS2008
Command17=ID_VIEW_APPLOOK_VS2010
Command18=ID_VIEW_APPLOOK_2010_1
Command19=ID_VIEW_APPLOOK_2010_2
Command20=ID_VIEW_APPLOOK_2010_3
Command21=ID_VIEW_APPLOOK_WIN7
Command22=ID_APP_ABOUT
CommandCount=22

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
CommandCount=8
Command8=ID_APP_ABOUT

[MNU:IDR_WAVEFOTYPE]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=ID_VIEW_STATUS_BAR
Command16=ID_VIEW_APPLOOK_2000
Command17=ID_VIEW_APPLOOK_XP
Command18=ID_VIEW_APPLOOK_2003
Command19=ID_VIEW_APPLOOK_VS2005
Command20=ID_VIEW_APPLOOK_WIN_XP
Command21=ID_VIEW_APPLOOK_2007
Command22=ID_VIEW_APPLOOK_2007_1
Command23=ID_VIEW_APPLOOK_2007_2
Command24=ID_VIEW_APPLOOK_2007_3
Command25=ID_VIEW_APPLOOK_VS2008
Command26=ID_VIEW_APPLOOK_VS2010
Command27=ID_VIEW_APPLOOK_2010_1
Command28=ID_VIEW_APPLOOK_2010_2
Command29=ID_VIEW_APPLOOK_2010_3
Command30=ID_VIEW_APPLOOK_WIN7
Command31=ID_WINDOW_NEW
Command32=ID_WINDOW_CASCADE
Command33=ID_WINDOW_TILE_HORZ
Command34=ID_WINDOW_ARRANGE
Command35=ID_APP_ABOUT
CommandCount=35

[ACL:IDR_MAINFRAME]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[MNU:IDR_CONTEXT_MENU]
Type=1
Class=?
Command1=ID_EDIT_CUT
Command2=ID_EDIT_COPY
Command3=ID_EDIT_PASTE
CommandCount=3

[MNU:IDR_POPUP_MDITABS]
Type=1
Class=?
Command1=ID_FILE_SAVE
Command2=ID_FILE_CLOSE
Command3=ID_MDI_NEW_HORZ_TAB_GROUP
Command4=ID_MDI_NEW_VERT_GROUP
Command5=ID_MDI_MOVE_TO_NEXT_GROUP
Command6=ID_MDI_MOVE_TO_PREV_GROUP
CommandCount=6

[MNU:IDR_POPUP_DROP_MDITABS]
Type=1
Class=?
Command1=ID_MDI_NEW_HORZ_TAB_GROUP
Command2=ID_MDI_NEW_VERT_GROUP
Command3=ID_MDI_MOVE_TO_NEXT_GROUP
Command4=ID_MDI_MOVE_TO_PREV_GROUP
Command5=ID_MDI_CANCEL
CommandCount=5

[MNU:IDR_PASTE_MENU]
Type=1
Class=?
Command1=ID_EDIT_PASTE
Command2=ID_EDIT_PASTE_SPECIAL
CommandCount=2

[MNU:IDR_WINDOWS_MENU]
Type=1
Class=?
Command1=ID_WINDOW_NEW
CommandCount=1

[MNU:IDR_THEME_MENU]
Type=1
Class=?
Command1=ID_VIEW_APPLOOK_2007
Command2=ID_VIEW_APPLOOK_2007_1
Command3=ID_VIEW_APPLOOK_2007_2
Command4=ID_VIEW_APPLOOK_2007_3
Command5=ID_VIEW_APPLOOK_2010_1
Command6=ID_VIEW_APPLOOK_2010_2
Command7=ID_VIEW_APPLOOK_2010_3
Command8=ID_VIEW_APPLOOK_WIN7
CommandCount=8

[DLG:IDD_WAVEFORM_FORM]
Type=1
Class=CWaveFormView
ControlCount=3
Control1=IDC_STATIC_FRAME,button,1342177287
Control2=IDC_STATIC_INFO,static,1342308352
Control3=IDC_CHART,static,1342177285

[DLG:IDD_DLG_DEBUG]
Type=1
Class=CMyDebug
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1073807360
Control3=IDC_STATIC,button,1342177287
Control4=IDC_LIST_SET,SysListView32,1350631681

[CLS:CMyDebug]
Type=0
HeaderFile=CMyDebug.h
ImplementationFile=CMyDebug.cpp
BaseClass=CBCGPDialog
Filter=D
LastObject=CMyDebug
VirtualFilter=dWC

[DLG:IDD_DLG_DISPLAYINFO]
Type=1
Class=CMyDisPlayInfo
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_LIST_SET,SysListView32,1350631681

[CLS:CMyDisPlayInfo]
Type=0
HeaderFile=CMyDisPlayInfo.h
ImplementationFile=CMyDisPlayInfo.cpp
BaseClass=CBCGPDialog
Filter=D
LastObject=IDC_LIST_SET
VirtualFilter=dWC

