cmake_minimum_required(VERSION 3.16)
project(haslo4 VERSION 1.0 LANGUAGES C CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOUIC ON)

find_package(QT NAMES Qt5 Qt6 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Gui Sql)
find_package(Qt${QT_VERSION_MAJOR} OPTIONAL_COMPONENTS Widgets)

qt_standard_project_setup()

qt_add_executable(haslo4 WIN32 MACOSX_BUNDLE
    addpassword.cpp addpassword.h addpassword.ui
    main.cpp
    mainwindow.cpp mainwindow.h mainwindow.ui
    mypopup.cpp mypopup.h mypopup.ui
    database.h database.cpp
    newdatabase.h newdatabase.cpp newdatabase.ui

)

target_link_libraries(haslo4 PRIVATE
    Qt${QT_VERSION_MAJOR}::Sql
    Qt::Core
    Qt::Gui
)

if((QT_VERSION_MAJOR GREATER 4))
    target_link_libraries(haslo4 PRIVATE
        Qt::Widgets
    )
endif()

install(TARGETS haslo4
    BUNDLE DESTINATION .
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

qt_generate_deploy_app_script(
    TARGET haslo4
    FILENAME_VARIABLE deploy_script
    NO_UNSUPPORTED_PLATFORM_ERROR
)
install(SCRIPT ${deploy_script})
