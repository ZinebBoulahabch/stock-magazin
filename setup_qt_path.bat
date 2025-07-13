@echo off
echo Configuration automatique du PATH pour Qt...
echo.

REM Chercher Qt dans les emplacements typiques
set QT_PATHS=

REM Qt 6.5
if exist "C:\Qt\6.5.2\mingw_64\bin" (
    set QT_PATHS=%QT_PATHS%;C:\Qt\6.5.2\mingw_64\bin
    echo Qt 6.5.2 trouve
)

REM Qt 6.4
if exist "C:\Qt\6.4.3\mingw_64\bin" (
    set QT_PATHS=%QT_PATHS%;C:\Qt\6.4.3\mingw_64\bin
    echo Qt 6.4.3 trouve
)

REM Qt 5.15
if exist "C:\Qt\5.15.2\mingw81_64\bin" (
    set QT_PATHS=%QT_PATHS%;C:\Qt\5.15.2\mingw81_64\bin
    echo Qt 5.15.2 trouve
)

REM MinGW
if exist "C:\Qt\Tools\mingw1120_64\bin" (
    set QT_PATHS=%QT_PATHS%;C:\Qt\Tools\mingw1120_64\bin
    echo MinGW trouve
)

if exist "C:\Qt\Tools\mingw810_64\bin" (
    set QT_PATHS=%QT_PATHS%;C:\Qt\Tools\mingw810_64\bin
    echo MinGW trouve
)

REM Qt Creator
if exist "C:\Qt\Tools\QtCreator\bin" (
    set QT_PATHS=%QT_PATHS%;C:\Qt\Tools\QtCreator\bin
    echo Qt Creator trouve
)

if "%QT_PATHS%"=="" (
    echo ERREUR: Qt n'a pas ete trouve dans les emplacements typiques.
    echo.
    echo Veuillez installer Qt depuis https://www.qt.io/download
    echo Puis relancer ce script.
    pause
    exit /b 1
)

echo.
echo Ajout de Qt au PATH...
echo.

REM Ajouter au PATH utilisateur (plus sûr)
setx PATH "%PATH%%QT_PATHS%"

if %errorlevel% equ 0 (
    echo ✅ Qt ajoute au PATH avec succes!
    echo.
    echo Redemarrez votre terminal PowerShell puis testez:
    echo qmake --version
    echo.
    echo Puis compilez l'interface graphique:
    echo .\compile_gui.bat
) else (
    echo ❌ Erreur lors de l'ajout au PATH
    echo.
    echo Ajoutez manuellement ces chemins au PATH:
    echo %QT_PATHS%
)

echo.
pause 