cmake_policy(SET CMP0048 NEW)

cmake_minimum_required(VERSION 3.11)

project(fort-time VERSION 1.0.0
                  LANGUAGES C CXX)

set(VERSION_API ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR})
if(${PROJECT_VERSION_MAJOR} EQUAL 0)
	set(VERSION_ABI ${VERSION_API})
else(${PROJECT_VERSION_MAJOR} EQUAL 0)
	set(VERSION_ABI ${PROJECT_VERSION_MAJOR})
endif(${PROJECT_VERSION_MAJOR} EQUAL 0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

find_package(Protobuf 3.3.0 REQUIRED)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(FetchGoogleTest)

fetch_google_test(VERSION release-1.10.0)

include(GoogleTest)

enable_testing()

include_directories(${PROTOBUF_INCLUDE_DIRS})

add_library(fort-time Time.cpp Time.hpp)

target_link_libraries(fort-time ${PROTOBUF_LIBRARIES})

set_target_properties(fort-time PROPERTIES VERSION ${VERSION_API}
                                          SOVERSION ${VERSION_ABI})

add_executable(fort-time-tests TimeUTest.hpp TimeUTest.cpp main-check.cpp)

target_link_libraries(fort-time-tests fort-time gtest)

add_test(NAME fort-time-tests COMMAND fort-time-tests)
