cmake_minimum_required(VERSION 3.5)

project(GUI VERSION 0.1 LANGUAGES CXX)

# Set CMake policies
if(POLICY CMP0071)
    cmake_policy(SET CMP0071 NEW)
endif()

# Find required Qt components
find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets 3DCore 3DRender 3DLogic 3DExtras 3DAnimation)

# Set project properties
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Define project sources
set(PROJECT_SOURCES
    main.cpp
    mainwindow.cpp
    mainwindow.h
    mainwindow.ui
    atomentity.h
    atomentity.cpp
    bondentity.h
    bondentity.cpp
    graphicsview.h
    graphicsview.cpp
    orbitcameracontroller.h
    orbitcameracontroller.cpp
    moleculeentity.h
    moleculeentity.cpp
    moleculelistmodel.h
    moleculelistmodel.cpp
    atomtablemodel.h
    atomtablemodel.cpp
    datamanager.h
    datamanager.cpp
)

# Create executable target
add_executable(GUI ${PROJECT_SOURCES})

# Link necessary Qt modules
target_link_libraries(GUI PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::3DCore Qt${QT_VERSION_MAJOR}::3DRender Qt${QT_VERSION_MAJOR}::3DLogic Qt${QT_VERSION_MAJOR}::3DExtras Qt${QT_VERSION_MAJOR}::3DAnimation)

# Add the library to link against
# target_link_libraries(GUI PUBLIC qt3dgizmo)ldd

# Set target properties
set_target_properties(GUI PROPERTIES
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
)

# Install target
include(GNUInstallDirs)
install(TARGETS GUI
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
