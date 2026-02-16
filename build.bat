
@echo off
REM Compile to object
clang++ -c -std=c++23 -fno-exceptions -fno-rtti main.cpp -o main.obj

REM Link with MSVC linker, custom entry, no CRT
link main.obj ^
    /OUT:minimal.exe ^
    /LIBPATH:"C:\Program Files (x86)\Windows Kits\10\Lib\10.0.26100.0\um\x64" ^
    kernel32.lib ^
    /ENTRY:_start /SUBSYSTEM:CONSOLE


