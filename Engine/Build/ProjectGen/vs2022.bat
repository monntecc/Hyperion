@echo off
xmake project -k vsxmake2022 -m "debug;release" -a x64
IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)