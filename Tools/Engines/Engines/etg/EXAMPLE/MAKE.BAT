@echo off
del example.exe
tasm32.exe /ml /m /z example.asm
tlink32.exe -x -c -Tpe -B:0x10000000 example.obj,,,import32.lib
del example.obj
