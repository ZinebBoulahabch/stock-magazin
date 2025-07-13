cmake_minimum_required(VERSION 3.16)
project(StockMagazinGUI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Trouver Qt6 (ou Qt5 si Qt6 n'est pas disponible)
find_package(Qt6 COMPONENTS Core Widgets REQUIRED)
if(NOT Qt6_FOUND)
    find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
endif()

# Fichiers sources
set(SOURCES
    stock_gui.cpp
)

# Créer l'exécutable
add_executable(stock_gui ${SOURCES})

# Lier avec Qt
target_link_libraries(stock_gui Qt::Core Qt::Widgets)

# Activer l'automatique MOC
set_target_properties(stock_gui PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)

# Configuration pour Windows
if(WIN32)
    set_target_properties(stock_gui PROPERTIES
        WIN32_EXECUTABLE TRUE
    )
endif()

# Installation
install(TARGETS stock_gui
    RUNTIME DESTINATION bin
) 