@echo off
..\tasm32.exe /ml /l /m3  main.asm main.obj
..\tlink32.exe /Tpe /aa  main.obj ,main.exe,,..\import32.lib 
..\makeex
if exist main.obj del main.obj
if exist main.map del main.map
if exist main.LST del main.LST
pause
