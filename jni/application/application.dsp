# Microsoft Developer Studio Project File - Name="application" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Application" 0x0101

CFG=application - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "application.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "application.mak" CFG="application - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "application - Win32 Release" (based on "Win32 (x86) Application")
!MESSAGE "application - Win32 Debug" (based on "Win32 (x86) Application")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "application - Win32 Release"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 0
# PROP BASE Output_Dir "Release"
# PROP BASE Intermediate_Dir "Release"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 0
# PROP Output_Dir "Release"
# PROP Intermediate_Dir "Release"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GR /GX /O2 /I "../cocos2dx" /I "../cocos2dx/include" /I "../cocos2dx/platform/win32" /I "../cocos2dx/kazmath/include" /I "../glew/include" /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib /nologo /subsystem:windows /machine:I386 /libpath:"../pthread"

!ELSEIF  "$(CFG)" == "application - Win32 Debug"

# PROP BASE Use_MFC 0
# PROP BASE Use_Debug_Libraries 1
# PROP BASE Output_Dir "Debug"
# PROP BASE Intermediate_Dir "Debug"
# PROP BASE Target_Dir ""
# PROP Use_MFC 0
# PROP Use_Debug_Libraries 1
# PROP Output_Dir "Debug"
# PROP Intermediate_Dir "Debug"
# PROP Ignore_Export_Lib 0
# PROP Target_Dir ""
# ADD BASE CPP /nologo /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GR /GX /ZI /Od /I "../cocos2dx" /I "../cocos2dx/include" /I "../cocos2dx/platform/win32" /I "../cocos2dx/kazmath/include" /I "../glew/include" /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_UNICODE" /D "UNICODE" /FR /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib opengl32.lib /nologo /subsystem:windows /debug /machine:I386 /pdbtype:sept /libpath:"../pthread"

!ENDIF 

# Begin Target

# Name "application - Win32 Release"
# Name "application - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Source File

SOURCE=.\AppDelegate.cpp
# End Source File
# Begin Source File

SOURCE=.\HelloWorldScene.cpp
# End Source File
# Begin Source File

SOURCE=.\main_android.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\main_win32.cpp
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Source File

SOURCE=.\AppDelegate.h
# End Source File
# Begin Source File

SOURCE=.\AppMacros.h
# End Source File
# Begin Source File

SOURCE=.\HelloWorldScene.h
# End Source File
# Begin Source File

SOURCE=.\main_win32.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# Begin Group "ScriptReader"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\ScriptReader\BackgroundManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\BackgroundManager.h
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\BackgroundMusicManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\BackgroundMusicManager.h
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\CharactorManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\CharactorManager.h
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCBackground.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCBackground.h
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCCharactorSpeak.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCCharactorSpeak.h
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCIf.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCIf.h
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCJump.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCJump.h
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCLeave.cpp

!IF  "$(CFG)" == "application - Win32 Release"

# PROP Exclude_From_Build 1

!ELSEIF  "$(CFG)" == "application - Win32 Debug"

!ENDIF 

# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCLeave.h
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCPlayBGM.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCPlayBGM.h
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCPlaySound.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCPlaySound.h
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\ScriptCommand.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\ScriptCommand.h
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\ScriptReader.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\ScriptReader.h
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCSelect.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCSelect.h
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCSet.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCSet.h
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCStopBGM.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCStopBGM.h
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCStopSound.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SCStopSound.h
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SoundManager.cpp
# End Source File
# Begin Source File

SOURCE=.\ScriptReader\SoundManager.h
# End Source File
# End Group
# Begin Group "src"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\CharLabel.cpp
# End Source File
# Begin Source File

SOURCE=.\CharLabel.h
# End Source File
# Begin Source File

SOURCE=.\GameScene.cpp
# End Source File
# Begin Source File

SOURCE=.\GameScene.h
# End Source File
# Begin Source File

SOURCE=.\GameSystem.cpp
# End Source File
# Begin Source File

SOURCE=.\GameSystem.h
# End Source File
# Begin Source File

SOURCE=.\History.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\History.hpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\HistoryScene.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\HistoryScene.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\LoadScene.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\LoadScene.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MainMenuScene.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\MainMenuScene.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\SaveData.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\SaveData.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\SaveScene.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\SaveScene.h
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\SettingScene.cpp
# PROP Exclude_From_Build 1
# End Source File
# Begin Source File

SOURCE=.\SettingScene.h
# PROP Exclude_From_Build 1
# End Source File
# End Group
# Begin Group "TestFolder"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\TestFolder\TestInFolder.cpp
# End Source File
# Begin Source File

SOURCE=.\TestFolder\TestInFolder.h
# End Source File
# End Group
# Begin Group "Control"

# PROP Default_Filter ""
# Begin Source File

SOURCE=.\Control\EasyButton.cpp
# End Source File
# Begin Source File

SOURCE=.\Control\EasyButton.h
# End Source File
# Begin Source File

SOURCE=.\Control\PopupLayer.cpp
# End Source File
# Begin Source File

SOURCE=.\Control\PopupLayer.hpp
# End Source File
# Begin Source File

SOURCE=.\Control\RadioButton.cpp
# End Source File
# Begin Source File

SOURCE=.\Control\RadioButton.h
# End Source File
# Begin Source File

SOURCE=.\Control\Slidebar.cpp
# End Source File
# Begin Source File

SOURCE=.\Control\Slidebar.h
# End Source File
# End Group
# End Target
# End Project
