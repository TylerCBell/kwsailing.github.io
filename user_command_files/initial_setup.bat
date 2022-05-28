@echo off
setlocal

echo ---------- Setting temporary path to python scripts ----------
set PATH=%PATH%;C:\Users\%USERNAME%\AppData\Local\Programs\Python\Python310\Scripts
:: sets a temporary path to the python scripts so that the required python modules can
:: be installed using "pip install" command

echo ---------- Downloading required python modules ----------
pip install behave

:EXIT
endlocal
:: timeout /t -1
exit /b 0
:: the timeout forces the command window to stay open until the user decides to close it
:: and should be used in order to debug the batch file