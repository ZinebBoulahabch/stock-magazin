QT += core widgets

CONFIG += c++17 moc

TARGET = stock_gui
TEMPLATE = app

SOURCES += stock_gui.cpp

# Configuration pour Windows
win32 {
    # RC_ICONS = icon.ico
}

# Configuration pour Linux
unix {
    TARGET = stock_gui
}

# Configuration pour macOS
macx {
    TARGET = stock_gui
    ICON = icon.icns
} 