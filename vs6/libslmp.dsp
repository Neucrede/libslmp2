# Microsoft Developer Studio Project File - Name="libslmp" - Package Owner=<4>
# Microsoft Developer Studio Generated Build File, Format Version 6.00
# ** DO NOT EDIT **

# TARGTYPE "Win32 (x86) Dynamic-Link Library" 0x0102

CFG=libslmp - Win32 Debug
!MESSAGE This is not a valid makefile. To build this project using NMAKE,
!MESSAGE use the Export Makefile command and run
!MESSAGE 
!MESSAGE NMAKE /f "libslmp.mak".
!MESSAGE 
!MESSAGE You can specify a configuration when running NMAKE
!MESSAGE by defining the macro CFG on the command line. For example:
!MESSAGE 
!MESSAGE NMAKE /f "libslmp.mak" CFG="libslmp - Win32 Debug"
!MESSAGE 
!MESSAGE Possible choices for configuration are:
!MESSAGE 
!MESSAGE "libslmp - Win32 Release" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE "libslmp - Win32 Debug" (based on "Win32 (x86) Dynamic-Link Library")
!MESSAGE 

# Begin Project
# PROP AllowPerConfigDependencies 0
# PROP Scc_ProjName ""
# PROP Scc_LocalPath ""
CPP=cl.exe
MTL=midl.exe
RSC=rc.exe

!IF  "$(CFG)" == "libslmp - Win32 Release"

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
# ADD BASE CPP /nologo /MT /W3 /GX /O2 /D "WIN32" /D "NDEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBSLMP_EXPORTS" /D "__NATIVE_FUNCTION_MACRO_NOT_DEFINED__" /YX /FD /c
# ADD CPP /nologo /MT /W3 /GX /O2 /I ".\\" /I ".\libslmp" /I "..\libslmp\include" /D "NDEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBSLMP_EXPORTS" /D "__NATIVE_FUNCTION_MACRO_NOT_DEFINED__" /YX /FD /c
# ADD BASE MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "NDEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "NDEBUG"
# ADD RSC /l 0x804 /d "NDEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /machine:I386
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /debug /machine:I386

!ELSEIF  "$(CFG)" == "libslmp - Win32 Debug"

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
# ADD BASE CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /D "WIN32" /D "_DEBUG" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBSLMP_EXPORTS" /D "__NATIVE_FUNCTION_MACRO_NOT_DEFINED__" /YX /FD /GZ /c
# ADD CPP /nologo /MTd /W3 /Gm /GX /ZI /Od /I ".\\" /I ".\libslmp" /I "..\libslmp\include" /D "_DEBUG" /D "WIN32" /D "_WINDOWS" /D "_MBCS" /D "_USRDLL" /D "LIBSLMP_EXPORTS" /D "__NATIVE_FUNCTION_MACRO_NOT_DEFINED__" /YX /FD /GZ /c
# ADD BASE MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD MTL /nologo /D "_DEBUG" /mktyplib203 /win32
# ADD BASE RSC /l 0x804 /d "_DEBUG"
# ADD RSC /l 0x804 /d "_DEBUG"
BSC32=bscmake.exe
# ADD BASE BSC32 /nologo
# ADD BSC32 /nologo
LINK32=link.exe
# ADD BASE LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept
# ADD LINK32 kernel32.lib user32.lib gdi32.lib winspool.lib comdlg32.lib advapi32.lib shell32.lib ole32.lib oleaut32.lib uuid.lib odbc32.lib odbccp32.lib ws2_32.lib /nologo /dll /debug /machine:I386 /pdbtype:sept

!ENDIF 

# Begin Target

# Name "libslmp - Win32 Release"
# Name "libslmp - Win32 Debug"
# Begin Group "Source Files"

# PROP Default_Filter "cpp;c;cxx;rc;def;r;odl;idl;hpj;bat"
# Begin Group "codec_"

# PROP Default_Filter ""
# Begin Group "command_"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\codec\command\clearerr_codec.c
# End Source File
# Begin Source File

SOURCE=..\libslmp\codec\command\dpmem_codec.c
# End Source File
# Begin Source File

SOURCE=..\libslmp\codec\command\extunit_codec.c
# End Source File
# Begin Source File

SOURCE=..\libslmp\codec\command\filecmd_codec.c
# End Source File
# Begin Source File

SOURCE=..\libslmp\codec\command\intmem_codec.c
# End Source File
# Begin Source File

SOURCE=..\libslmp\codec\command\nodeconn_codec.c
# End Source File
# Begin Source File

SOURCE=..\libslmp\codec\command\nodemon_codec.c
# End Source File
# Begin Source File

SOURCE=..\libslmp\codec\command\paramset_codec.c
# End Source File
# Begin Source File

SOURCE=..\libslmp\codec\command\remctrl_codec.c
# End Source File
# Begin Source File

SOURCE=..\libslmp\codec\command\rempswd_codec.c
# End Source File
# Begin Source File

SOURCE=..\libslmp\codec\command\selftest_codec.c
# End Source File
# End Group
# Begin Group "frame_"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\codec\frame\framecodec.c
# End Source File
# End Group
# Begin Group "word_"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\codec\word\wordcodec.c
# End Source File
# End Group
# End Group
# Begin Group "tsd_"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\tsd\tsd.c
# End Source File
# End Group
# Begin Group "memory_"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\memory\memory.c
# End Source File
# End Group
# Begin Group "glthread_"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\glthread\lock.c
# End Source File
# Begin Source File

SOURCE=..\libslmp\glthread\threadlib.c
# End Source File
# End Group
# Begin Group "packetio_"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\packetio\pktio.c
# End Source File
# Begin Source File

SOURCE=..\libslmp\packetio\tcpip.c
# End Source File
# Begin Source File

SOURCE=..\libslmp\packetio\udpip.c
# End Source File
# End Group
# Begin Group "frameio_"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\frameio\frameio.c
# End Source File
# End Group
# Begin Group "server_"

# PROP Default_Filter "*.c"
# Begin Source File

SOURCE=..\libslmp\server\server.c
# End Source File
# End Group
# Begin Source File

SOURCE=..\libslmp\errmsg.c
# End Source File
# Begin Source File

SOURCE=..\libslmp\libslmp.c
# End Source File
# Begin Source File

SOURCE=..\libslmp\libslmp.def
# End Source File
# Begin Source File

SOURCE=..\libslmp\strlcpy.c
# End Source File
# End Group
# Begin Group "Header Files"

# PROP Default_Filter "h;hpp;hxx;hm;inl"
# Begin Group "public"

# PROP Default_Filter ""
# Begin Group "command"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\include\slmp\command\clearerr.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\command\cmdcode.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\command\cmdhdr.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\command\dpmem.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\command\extunit.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\command\filecmd.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\command\intmem.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\command\nodeconn.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\command\nodemon.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\command\paramset.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\command\remctrl.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\command\rempswd.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\command\selftest.h
# End Source File
# End Group
# Begin Group "codec"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\include\slmp\codec\clearerr_codec.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\codec\cmdcodec.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\codec\dpmem_codec.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\codec\extunit_codec.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\codec\filecmd_codec.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\codec\intmem_codec.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\codec\nodeconn_codec.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\codec\nodemon_codec.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\codec\paramset_codec.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\codec\remctrl_codec.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\codec\rempswd_codec.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\codec\selftest_codec.h
# End Source File
# End Group
# Begin Group "packetio"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\include\slmp\packetio\tcpip.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\packetio\udpip.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\libslmp\include\slmp\_poppack.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\_pushpack4.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\slmp.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\slmpapi.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\slmpcodec.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\slmpdef.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\slmperr.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\slmpframe.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\slmpfrmio.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\slmpinit.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\slmpmem.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\slmppktio.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\include\slmp\slmpserver.h
# End Source File
# End Group
# Begin Group "internal"

# PROP Default_Filter ""
# Begin Group "codec__"

# PROP Default_Filter ""
# Begin Group "command__"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\codec\command\cmdcodec_priv.h
# End Source File
# End Group
# Begin Group "word__"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\codec\word\wordcodec.h
# End Source File
# End Group
# Begin Group "frame__"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\codec\frame\framecodec.h
# End Source File
# End Group
# End Group
# Begin Group "tsd__"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\tsd\tsd.h
# End Source File
# End Group
# Begin Group "memory__"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\memory\memory_intl.h
# End Source File
# End Group
# Begin Group "glthread__"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\glthread\lock.h
# End Source File
# End Group
# Begin Group "packetio__"

# PROP Default_Filter ""
# Begin Source File

SOURCE=..\libslmp\packetio\pktio_priv.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\packetio\tcpip_priv.h
# End Source File
# Begin Source File

SOURCE=..\libslmp\packetio\udpip_priv.h
# End Source File
# End Group
# Begin Group "server__"

# PROP Default_Filter "*.h"
# Begin Source File

SOURCE=..\libslmp\server\server_priv.h
# End Source File
# End Group
# Begin Source File

SOURCE=..\libslmp\slmp_intl.h
# End Source File
# End Group
# Begin Source File

SOURCE=.\libslmp\config.h
# End Source File
# End Group
# Begin Group "Resource Files"

# PROP Default_Filter "ico;cur;bmp;dlg;rc2;rct;bin;rgs;gif;jpg;jpeg;jpe"
# End Group
# End Target
# End Project
