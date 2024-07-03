cmake_minimum_required(VERSION 3.16)
project(DropAmoeba VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(DropAmoeba WIN32 MACOSX_BUNDLE
    amoebamodel.cpp amoebamodel.h
    amoebapersist.cpp amoebapersist.h
    amoebaview.cpp amoebaview.h
    main.cpp
)
target_link_libraries(DropAmoeba PRIVATE
    Qt::Core
    Qt::Gui
)

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(DropAmoeba PRIVATE
        Qt::Widgets
    )
endif()

install(TARGETS DropAmoeba
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET DropAmoeba
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
