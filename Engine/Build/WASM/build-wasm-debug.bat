@echo off
xmake f -y -p wasm -m debug
xmake -y
IF %ERRORLEVEL% NEQ 0 (
  PAUSE
)