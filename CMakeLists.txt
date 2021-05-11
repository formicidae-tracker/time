cmake_policy(SET CMP0048 NEW)

cmake_minimum_required(VERSION 3.11)

project(fort-time LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)


list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
include(VersionFromGit)
version_from_git()

find_package(Protobuf 3.3.0 REQUIRED)

include(FetchGoogleTest)

fetch_google_test(VERSION release-1.10.0)

include(GoogleTest)

enable_testing()
set(MAKE_CHECK_TEST_COMMAND ${CMAKE_CTEST_COMMAND} -V)
add_custom_target(check COMMAND ${MAKE_CHECK_TEST_COMMAND})

option(ENABLE_COVERAGE Off "Enables code coverage")

if(ENABLE_COVERAGE)
include(CodeCoverage)
enable_coverage()
setup_target_for_coverage(NAME fort-time-coverage
                          DEPENDENCIES check
						  GCOVR_OPTIONS -f ${PROJECT_SOURCE_DIR}/Time.hpp
						                -f ${PROJECT_SOURCE_DIR}/Time.cpp)
endif(ENABLE_COVERAGE)

include_directories(${Protobuf_INCLUDE_DIRS})

add_library(fort-time SHARED Time.cpp Time.hpp)

target_link_libraries(fort-time ${Protobuf_LIBRARIES})

set_target_properties(fort-time PROPERTIES VERSION ${PROJECT_VERSION_API}
                                          SOVERSION ${PROJECT_VERSION_ABI})


add_executable(fort-time-tests TimeUTest.hpp TimeUTest.cpp main-check.cpp)

target_link_libraries(fort-time-tests fort-time gtest)

add_test(NAME fort-time-tests COMMAND fort-time-tests)
add_dependencies(check fort-time-tests)


set(INCLUDE_PATH include)
set(INCLUDE_INSTALL_DIR ${INCLUDE_PATH}/fort/time)
set(LIB_INSTALL_DIR lib)

install(FILES Time.hpp DESTINATION ${INCLUDE_INSTALL_DIR})
install(TARGETS fort-time DESTINATION ${LIB_INSTALL_DIR})


include(CMakePackageConfigHelpers)
configure_package_config_file(FortTimeConfig.cmake.in
                              ${CMAKE_CURRENT_BINARY_DIR}/FortTimeConfig.cmake
							  INSTALL_DESTINATION ${LIB_INSTALL_DIR}/FortTime/cmake
							  PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR INCLUDE_PATH)

write_basic_package_version_file(${CMAKE_CURRENT_BINARY_DIR}/FortTimeConfigVersion.cmake
                                 VERSION ${PROJECT_VERSION}
								 COMPATIBILITY SameMajorVersion)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/FortTimeConfig.cmake
              ${CMAKE_CURRENT_BINARY_DIR}/FortTimeConfigVersion.cmake
			  DESTINATION ${LIB_INSTALL_DIR}/FortTime/cmake )
