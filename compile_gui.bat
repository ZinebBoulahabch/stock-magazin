@echo off
echo Compilation de l'interface graphique Qt...
echo.

REM Vérifier si Qt est installé
where qmake >nul 2>&1
if %errorlevel% neq 0 (
    echo ERREUR: Qt n'est pas installé ou pas dans le PATH
    echo.
    echo Pour installer Qt:
    echo 1. Télécharger Qt depuis https://www.qt.io/download
    echo 2. Installer Qt avec Qt Creator
    echo 3. Ajouter Qt au PATH système
    echo.
    pause
    exit /b 1
)

echo Qt trouvé, compilation en cours...
echo.

REM Compiler avec qmake
qmake stock_gui.pro
if %errorlevel% neq 0 (
    echo ERREUR: qmake a échoué
    pause
    exit /b 1
)

REM Compiler avec make
make
if %errorlevel% neq 0 (
    echo ERREUR: Compilation échouée
    pause
    exit /b 1
)

echo.
echo ✅ Compilation réussie!
echo L'application est disponible: stock_gui.exe
echo.
echo Pour lancer l'application:
echo stock_gui.exe
echo.
pause 