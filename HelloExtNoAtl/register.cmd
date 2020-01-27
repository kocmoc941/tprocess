@echo off

set MYDIR=%~dp0

regsvr32 %MYDIR%HelloExtNoAtl.dll

