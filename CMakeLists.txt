# CMakeLists.txt (Final, Simplified Version)
cmake_minimum_required(VERSION 3.16)

project(ClipSyncPro LANGUAGES CXX RC)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 COMPONENTS Core Widgets REQUIRED)

# We removed the 'include_directories' command. It's not needed.

add_executable(ClipSyncPro
    src/main.cpp
    src/core/ClipboardManager.cpp
    src/gui/MainWindow.cpp
    src/storage/HistoryManager.cpp
    resources.qrc
    win32_resource.rc
)

# This is all that's needed for the C++ headers.
target_include_directories(ClipSyncPro PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/src")

target_link_libraries(ClipSyncPro PRIVATE Qt6::Core Qt6::Widgets)