#!/bin/bash

echo "Compilation de l'interface graphique Qt..."
echo

# Vérifier si Qt est installé
if ! command -v qmake &> /dev/null; then
    echo "ERREUR: Qt n'est pas installé"
    echo
    echo "Pour installer Qt sur Ubuntu/Debian:"
    echo "sudo apt-get install qt6-base-dev"
    echo
    echo "Pour installer Qt sur CentOS/RHEL:"
    echo "sudo yum install qt6-qtbase-devel"
    echo
    exit 1
fi

echo "Qt trouvé, compilation en cours..."
echo

# Compiler avec qmake
qmake stock_gui.pro
if [ $? -ne 0 ]; then
    echo "ERREUR: qmake a échoué"
    exit 1
fi

# Compiler avec make
make
if [ $? -ne 0 ]; then
    echo "ERREUR: Compilation échouée"
    exit 1
fi

echo
echo "✅ Compilation réussie!"
echo "L'application est disponible: ./stock_gui"
echo
echo "Pour lancer l'application:"
echo "./stock_gui"
echo 