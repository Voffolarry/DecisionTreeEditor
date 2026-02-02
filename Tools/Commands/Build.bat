@echo off
setlocal enabledelayedexpansion

if /i "%1" neq "build" (
    echo Usage: %0 build [compilateur] [debug^|release] [clean]
    exit /b 1
)

set "COMPILER=%~2"
if "%COMPILER%"=="" set "COMPILER=clang++"

set "MODE=%~3"
if /i "!MODE!"=="debug" (
    set "CFLAGS=-g -O0 -std=c++20"
) else (
    set "CFLAGS=-O2 -std=c++20"
    set "MODE=release"
)

echo Building with %COMPILER% in %MODE% mode...

if /i "%4"=="clean" (
    if exist ".\Build\Obj" rmdir /s /q ".\Build\Obj"
    echo Mode clean active.
)

set "INCLUDE_DIR=C:\msys64\ucrt64\include"
set "LIB_DIR=C:\msys64\ucrt64\lib"
set "SRC_DIR=.\Sources"
set "OBJ_DIR=.\Build\Obj"
set "BIN_DIR=.\Build\Bin"
set "RES_DIR=.\Resources"
set "OUT=RihenNatural.exe"

if not exist "%SRC_DIR%" (
    echo Error: Directory %SRC_DIR% does not exist.
    exit /b 1
)

if not exist "%OBJ_DIR%" mkdir "%OBJ_DIR%"
if not exist "%BIN_DIR%" mkdir "%BIN_DIR%"

set "OBJ_FILES="
for /r "%SRC_DIR%" %%f in (*.cpp) do (
    set "cpp_full=%%~ff"
    set "base=%%~nf"
    set "o=%OBJ_DIR%\!base!.o"

    echo Compiling !base!.cpp
    "%COMPILER%" -c "!cpp_full!" -I "%SRC_DIR%" -I "%INCLUDE_DIR%" !CFLAGS! -o "!o!"
    if errorlevel 1 (
        echo Error compiling !base!.cpp
        exit /b 1
    )
    
    set "OBJ_FILES=!OBJ_FILES! "!o!""
)

if "!OBJ_FILES!"=="" (
    echo Error: No object files generated.
    exit /b 1
)

echo Linking...
"%COMPILER%" !OBJ_FILES! -L "%LIB_DIR%" -lSDL3 -luser32 -lgdi32 -lwinmm -limm32 -lole32 -loleaut32 -lversion -luuid -ladvapi32 -lshell32 !CFLAGS! -o "%BIN_DIR%\%OUT%"
if errorlevel 1 (
    echo Error during linking
    exit /b 1
)

if exist "%RES_DIR%" (
    echo Copying resources...
    xcopy /E /I /Y "%RES_DIR%\*" "%BIN_DIR%\" >nul
)

echo Build completed: %BIN_DIR%\%OUT%