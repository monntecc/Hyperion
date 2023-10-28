@echo off
xmake f -y -p wasm -m release
xmake -y
IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)