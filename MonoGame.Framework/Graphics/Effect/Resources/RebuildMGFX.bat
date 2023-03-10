@echo off
setlocal

SET TWOMGFX="..\..\..\..\Tools\2MGFX\bin\Windows\AnyCPU\Debug\2mgfx.exe"

@for /f %%f IN ('dir /b *.fx') do (

  call %TWOMGFX% %%~nf.fx %%~nf.ps4.mgfxo /Profile:PlayStation4

)

endlocal
