@echo off
setlocal enabledelayedexpansion

set PERL=C:\Perl64\bin\perl.exe
set PERLScript=mkProj.pl

echo.
echo.
echo ########################################################################
echo ####
echo #### STARTING PERL CONFIGURATION BUILD (%PERL%, %PERLScript%)
echo ####
echo ########################################################################
echo.
echo.
echo The following configurations will be built:

set PROJECT_FILE=F:\source\RSTestRunner\AppUI
%PERL% -wi %PERLScript% -n !PROJECT_FILE!

echo ------------------------------------------------------------------------
echo ---- Done building [!PROJECT_FILE!]
echo ------------------------------------------------------------------------

set PROJECT_FILE=F:\source\RSTestRunner\rsyncEvaluation
%PERL% -wi %PERLScript% -n !PROJECT_FILE!

echo ------------------------------------------------------------------------
echo ---- Done building [!PROJECT_FILE!]
echo ------------------------------------------------------------------------

set PROJECT_FILE=F:\source\RSTestRunner\UKEYMonitor
%PERL% -wi %PERLScript% -n !PROJECT_FILE!

echo ------------------------------------------------------------------------
echo ---- Done building [!PROJECT_FILE!]
echo ------------------------------------------------------------------------

echo.
echo ------------------------------------------------------------------------
echo ------------------------------------------------------------------------
echo ---- Build completed.
echo ------------------------------------------------------------------------
echo ------------------------------------------------------------------------
echo.

endlocal
