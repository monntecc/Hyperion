@echo off
xmake f -y -p windows -m release -a x64
xmake -y
IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)