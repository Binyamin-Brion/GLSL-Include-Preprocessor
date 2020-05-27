cmake_minimum_required(VERSION 3.15)
project(GLSL_Include_Preprocessor)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

if(WIN32)
    set(CMAKE_PREFIX_PATH C:\\Qt\\Qt5.9.9\\5.9.9\\mingw53_32)
endif(WIN32)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Test REQUIRED)

include_directories(${Qt5Widgets_INCLUDES})

add_executable(GLSL_Include_Preprocessor main.cpp Tests/TestSuite.cpp Tests/TestSuite.h Tests/TestNoIncludes.cpp Tests/TestNoIncludes.h Tests/TestSingleInclude.cpp Tests/TestSingleInclude.h Tests/TestRecursiveInclude.cpp Tests/TestRecursiveInclude.h PreprocessorInclude/RecursiveInclude.cpp PreprocessorInclude/RecursiveInclude.h Tests/TestErrors.cpp Tests/TestErrors.h)


target_link_libraries(GLSL_Include_Preprocessor ${Qt5Widgets_LIBRARIES} ${Qt5Test_LIBRARIES})