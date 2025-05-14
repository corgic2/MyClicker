@ECHO OFF
set CURDIR=%~dp0
md build
cd build
cmake -DCMAKE_CONFIGURATION_TYPES=Release .. -G "Visual Studio 17 2022"
cmake --build . --config Release

@REM windeployqt
if defined QT_DIR (
    set QTDIR=%QT_DIR%
) else (
    set QTDIR=D:/Qt/5.15.2/msvc2019_64
)
cd %CURDIR%
pause
