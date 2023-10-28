@echo off
xmake f -y -p windows -m debug -a x64
xmake -y
IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)