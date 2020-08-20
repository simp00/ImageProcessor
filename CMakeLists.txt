cmake_minimum_required(VERSION 3.5)

project(ImageProcessor LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (APPLE)
set(CMAKE_PREFIX_PATH /Volumes/data/Qt5.14.2/5.14.2/clang_64/lib/cmake)
endif ()

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check http://doc.qt.io/qt-5/deployment-android.html for more information.
# They need to be set before the find_package(Qt5 ...) call.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5PrintSupport REQUIRED)

if(ANDROID)
  add_library(ImageProcessor SHARED
    main.cpp
    imageprocessor.cpp
    imageprocessor.h
          showwidget.cpp
          showwidget.h
  )
else()
  add_executable(ImageProcessor
    main.cpp
    imageprocessor.cpp
    imageprocessor.h
          showwidget.cpp
          showwidget.h
  )
endif()

target_link_libraries(ImageProcessor PRIVATE Qt5::Widgets Qt5::PrintSupport)
