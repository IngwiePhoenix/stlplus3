@echo off
setlocal

set bcc_pass=0
set bcc_fail=0
set fail_names=

echo ##################################################

for /d %%a in (*) do (
  if /i %%a neq CVS call :bcc_folder %%a
)

echo Compilations completed: %bcc_pass%
echo Compilations failed: %bcc_fail% (%fail_names% )
echo ##################################################
goto :EOF

:: Execute a bcc compilation script in a subfolder
:: %1 is the name of the folder.
::
:bcc_folder
set original=%cd%
cd %1
call bcc
if ERRORLEVEL 1 (
  echo ERROR in %1.exe
  set /a bcc_fail=bcc_fail+1
  set fail_names=%fail_names% %1
) else (
  set /a bcc_pass=bcc_pass+1
)
echo ##################################################
cd /d %original%
goto :EOF
