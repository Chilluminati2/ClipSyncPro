# CMakeLists.txt
cmake_minimum_required(VERSION 3.16)

project(ClipSyncPro LANGUAGES CXX RC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)


add_executable(ClipSyncPro
    src/main.cpp
    src/core/ClipboardManager.cpp
    src/storage/HistoryManager.cpp
    src/gui/MainWindow.cpp
    src/gui/SystemTray.cpp
    src/gui/SnippetDelegate.cpp
    # CustomTitleBar.cpp is now DELETED from this list
    src/platform/GlobalHotkey.cpp
    win32_resource.rc
)

# This includes the src directory for the RC compiler
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/src")

target_include_directories(ClipSyncPro PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(ClipSyncPro PRIVATE Qt6::Core Qt6::Widgets)

# If we are not using resources.qrc, this section is not needed.
# If you are, then uncomment the set() and add 'src/resources.qrc' to add_executable().
# set(CMAKE_AUTORCC_OPTIONS "src/resources.qrc")