cmake_minimum_required(VERSION 3.5)

project(DS_Project VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets Xml)


set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        CompressionSystem.cpp
        CompressionSystem.h
        DecompressSystem.cpp
        DecompressSystem.h

        HuffmanComp.cpp
        HuffmanComp.h
        HuffmanDec.cpp
        HuffmanDec.h
        HuffmanTree.cpp
        HuffmanTree.h
        HuffmanTreeNode.h

        ClearClosingTagsComp.cpp
        ClearClosingTagsComp.h
        ClearClosingTagsDec.cpp
        ClearClosingTagsDec.h
        Tree.cpp
        Tree.h
        TreeNode.cpp
        TreeNode.h

        MinifyingXML.cpp
        MinifyingXML.h

        TagsMapComp.cpp
        TagsMapComp.h
        TagsMapDec.cpp
        TagsMapDec.h
        Map.cpp
        Map.h

        XmlToJson_interface.cpp
        XmlToJson_interface.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(DS_Project
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        images/resources.qrc
        tabmanager.h tabmanager.cpp
        texteditmanager.h texteditmanager.cpp
        XmlToJson_private.h
        post.cpp post.h user.cpp user.h xmlparser.cpp xmlparser.h
        error_detect.cpp error_detect.h
        searchtopicwindow.cpp searchtopicwindow.h searchtopicwindow.ui
        edge.h graph.h graphicswidget.h
        edge.cpp graphicswidget.cpp node.cpp
        graph.cpp

    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET DS_Project APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(DS_Project SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(DS_Project
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(DS_Project PRIVATE Qt${QT_VERSION_MAJOR}::Widgets Qt${QT_VERSION_MAJOR}::Xml)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.DS_Project)
endif()
set_target_properties(DS_Project PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS DS_Project
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(DS_Project)
endif()
