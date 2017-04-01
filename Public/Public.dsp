# Microsoft Developer Studio Project File - Name="Public" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=Public - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "Public.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "Public.mak" CFG="Public - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "Public - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "Public - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "Public - Win32 Release"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /c
# ADD CPP /nologo /MD /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /Yu"stdafx.h" /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "NDEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /machine:I386
# ADD LINK32 /nologo /subsystem:windows /dll /machine:I386

!ELSEIF  "$(CFG)" == "Public - Win32 Debug"

# PROP BASE Use_MFC 6
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 6
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "..\Pub"
# PROP Intermediate_Dir "..\Debug\Public"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /Yu"stdafx.h" /FD /GZ /c
# ADD CPP /nologo /MDd /W3 /Gm /GX /ZI /Od /I "..\Pub\inc" /I ".\\" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_WINDLL" /D "_AFXDLL" /D "_MBCS" /D "_AFXEXT" /D "_PUBLIC_IMPL" /YX"stdafx.h" /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
# ADD RSC /l 0x804 /d "_DEBUG" /d "_AFXDLL"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 /nologo /subsystem:windows /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 winmm.lib /nologo /subsystem:windows /dll /debug /machine:I386 /out:"..\bin/Public.dll" /pdbtype:sept

!ENDIF 

# Begin Target

# Name "Public - Win32 Release"
# Name "Public - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=..\Pub\src\CMyData.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyDataBin.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyDataFloat.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyDataMem.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyDataOperate.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyDataString.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyDataVector.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyDataView.cpp
# End Source File
# Begin Source File

SOURCE=.\CMyDlgRTWave.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyEnumSCI.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyEventMng.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyFactory.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyObj.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyPort.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyPortMng.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyRTWave.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyUnit.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyVector.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\CMyWaveInfo.cpp
# End Source File
# Begin Source File

SOURCE=..\Pub\src\Pub.cpp
# End Source File
# Begin Source File

SOURCE=.\Public.cpp
# End Source File
# Begin Source File

SOURCE=.\Public.def
# End Source File
# Begin Source File

SOURCE=.\Public.rc
# End Source File
# Begin Source File

SOURCE=.\StdAfx.cpp
# ADD CPP /Yc"stdafx.h"
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=..\Pub\inc\CMyData.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyDataBin.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyDataFloat.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyDataMem.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyDataOperate.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyDataString.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyDataVector.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyDataView.h
# End Source File
# Begin Source File

SOURCE=.\CMyDlgRTWave.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyEnumSCI.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyEventMng.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyFactory.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyObj.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyPort.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyPortMng.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyRTWave.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyUnit.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyVector.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\CMyWaveInfo.h
# End Source File
# Begin Source File

SOURCE=..\Pub\inc\Pub.h
# End Source File
# Begin Source File

SOURCE=.\Resource.h
# End Source File
# Begin Source File

SOURCE=.\StdAfx.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# Begin Source File

SOURCE=.\res\Public.rc2
# End Source File
# End Group
# Begin Source File

SOURCE=.\ReadMe.txt
# End Source File
# End Target
# End Project
