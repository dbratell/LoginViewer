@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by LOGINVIEWER.HPJ. >"hlp\LoginViewer.hm"
echo. >>"hlp\LoginViewer.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\LoginViewer.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\LoginViewer.hm"
echo. >>"hlp\LoginViewer.hm"
echo // Prompts (IDP_*) >>"hlp\LoginViewer.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\LoginViewer.hm"
echo. >>"hlp\LoginViewer.hm"
echo // Resources (IDR_*) >>"hlp\LoginViewer.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\LoginViewer.hm"
echo. >>"hlp\LoginViewer.hm"
echo // Dialogs (IDD_*) >>"hlp\LoginViewer.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\LoginViewer.hm"
echo. >>"hlp\LoginViewer.hm"
echo // Frame Controls (IDW_*) >>"hlp\LoginViewer.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\LoginViewer.hm"
REM -- Make help for Project LOGINVIEWER


echo Building Win32 Help files
start /wait hcw /C /E /M "hlp\LoginViewer.hpj"
if errorlevel 1 goto :Error
if not exist "hlp\LoginViewer.hlp" goto :Error
if not exist "hlp\LoginViewer.cnt" goto :Error
echo.
if exist Debug\nul copy "hlp\LoginViewer.hlp" Debug
if exist Debug\nul copy "hlp\LoginViewer.cnt" Debug
if exist Release\nul copy "hlp\LoginViewer.hlp" Release
if exist Release\nul copy "hlp\LoginViewer.cnt" Release
echo.
goto :done

:Error
echo hlp\LoginViewer.hpj(1) : error: Problem encountered creating help file

:done
echo.
