cmake_policy(SET CMP0048 NEW)

cmake_minimum_required(VERSION 3.11)

project(fort-time LANGUAGES C CXX)


if(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	set(IS_MAIN TRUE)
else(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	set(IS_MAIN FALSE)
endif(CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)


list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

option(ENABLE_COVERAGE "Enable code coverage" Off)
option(BUILD_DOCS "Build documentation" Off)


include(VersionFromGit)
version_from_git()

find_package(Protobuf 3.3.0 REQUIRED)

include(CheckCSourceCompiles)
check_c_source_compiles("#include <time.h>
int main() {
  struct timespec wall;
  clock_gettime(CLOCK_REALTIME,&wall);
  return 0;
}" NEED_NO_RT_LINK)
if(NOT NEED_NO_RT_LINK)
	set(CMAKE_REQUIRED_LIBRARIES "-lrt")
	check_c_source_compiles("#include <time.h>
int main() {
  struct timespec wall;
  clock_gettime(CLOCK_REALTIME,&wall);
  return 0;
}" NEED_RT_LINK)
	if(NOT NEED_RT_LINK)
		message(FATAL_ERROR "Could not clock_gettime()")
	endif(NOT NEED_RT_LINK)
endif(NOT NEED_NO_RT_LINK)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)


if(IS_MAIN)
	include(FetchGoogleTest)
	fetch_google_test(VERSION release-1.12.1)
	include(GoogleTest)

	enable_testing()
	set(MAKE_CHECK_TEST_COMMAND ${CMAKE_CTEST_COMMAND} -V)
	add_custom_target(check COMMAND ${MAKE_CHECK_TEST_COMMAND})
endif(IS_MAIN)

if(IS_MAIN AND ENABLE_COVERAGE)
	set(ENABLE_TESTS On)

	include(CodeCoverage)
	enable_coverage()
	setup_target_for_coverage(NAME coverage
                              DEPENDENCIES check
                              LCOV_OPTIONS --include ${PROJECT_SOURCE_DIR}/src/fort/time/Time.hpp
                                           --include ${PROJECT_SOURCE_DIR}/src/fort/time/Time.cpp
                                           )
endif(IS_MAIN AND ENABLE_COVERAGE)

include_directories(${Protobuf_INCLUDE_DIRS})

set(INCLUDE_PATH include)
set(INCLUDE_INSTALL_DIR ${INCLUDE_PATH}/fort/time)
set(LIB_INSTALL_DIR lib)


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


add_subdirectory(src/fort/time)

if(BUILD_DOCS)
	add_subdirectory(docs)
endif(BUILD_DOCS)
