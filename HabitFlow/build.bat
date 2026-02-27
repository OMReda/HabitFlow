@echo off
echo Building HabitFlow...
"C:\Users\r3d4\scoop\apps\gcc\current\bin\gcc.exe" -Wall -Wextra -Iinclude src\main.c src\habit.c src\storage.c src\stats.c -o habitflow.exe
if %ERRORLEVEL% equ 0 (
    echo Build successful!
    echo Run it using: .\habitflow.exe
) else (
    echo Build failed.
)
