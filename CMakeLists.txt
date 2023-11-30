cmake_policy(SET CMP0048 NEW)

cmake_minimum_required(VERSION 3.11)

project(fort-time LANGUAGES C CXX)

if(NOT CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)
	set(FORT_TIME_IMPORTED 1)
endif(NOT CMAKE_SOURCE_DIR STREQUAL PROJECT_SOURCE_DIR)

list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

if(NOT FORT_TIME_IMPORTED)
	option(ENABLE_COVERAGE "Enable code coverage" Off)
	option(BUILD_DOCS "Build documentation" Off)
endif(NOT FORT_TIME_IMPORTED)

include(VersionFromGit)
version_from_git()

find_package(Protobuf 3.3.0 REQUIRED)

include(CheckCSourceCompiles)
check_c_source_compiles(
	"#include <time.h>
int main() {
  struct timespec wall;
  clock_gettime(CLOCK_REALTIME,&wall);
  return 0;
}"
	NEED_NO_RT_LINK
)
if(NOT NEED_NO_RT_LINK)
	set(CMAKE_REQUIRED_LIBRARIES "-lrt")
	check_c_source_compiles(
		"#include <time.h>
int main() {
  struct timespec wall;
  clock_gettime(CLOCK_REALTIME,&wall);
  return 0;
}"
		NEED_RT_LINK
	)
	if(NOT NEED_RT_LINK)
		message(FATAL_ERROR "Could not clock_gettime()")
	endif(NOT NEED_RT_LINK)
endif(NOT NEED_NO_RT_LINK)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_C_STANDARD 11)

if(NOT FORT_TIME_IMPORTED)
	include(FetchContent)

	FetchContent_Declare(
		googletest
		GIT_REPOSITORY https://github.com/google/googletest.git
		GIT_TAG 76bb2afb8b522d24496ad1c757a49784fbfa2e42
	)
	# For Windows: Prevent overriding the parent project's compiler/linker
	# settings
	set(gtest_force_shared_crt
		ON
		CACHE BOOL "" FORCE
	)
	FetchContent_MakeAvailable(googletest)

	include(GoogleTest)

	enable_testing()
	set(MAKE_CHECK_TEST_COMMAND ${CMAKE_CTEST_COMMAND} -V)
	add_custom_target(check COMMAND ${MAKE_CHECK_TEST_COMMAND})
endif(NOT FORT_TIME_IMPORTED)

if((NOT FORT_TIME_IMPORTED) AND ENABLE_COVERAGE)
	set(ENABLE_TESTS On)

	include(CodeCoverage)
	enable_coverage()
	setup_target_for_coverage(
		NAME
		coverage
		DEPENDENCIES
		check
		LCOV_OPTIONS
		--include
		${PROJECT_SOURCE_DIR}/src/fort/time/Time.hpp
		--include
		${PROJECT_SOURCE_DIR}/src/fort/time/Time.cpp
	)
endif((NOT FORT_TIME_IMPORTED) AND ENABLE_COVERAGE)

set(INCLUDE_PATH include)
set(INCLUDE_INSTALL_DIR ${INCLUDE_PATH}/fort/time)
set(LIB_INSTALL_DIR lib)

include(CMakePackageConfigHelpers)
configure_package_config_file(
	FortTimeConfig.cmake.in ${CMAKE_CURRENT_BINARY_DIR}/FortTimeConfig.cmake
	INSTALL_DESTINATION ${LIB_INSTALL_DIR}/FortTime/cmake
	PATH_VARS INCLUDE_INSTALL_DIR LIB_INSTALL_DIR INCLUDE_PATH
)

write_basic_package_version_file(
	${CMAKE_CURRENT_BINARY_DIR}/FortTimeConfigVersion.cmake
	VERSION ${PROJECT_VERSION}
	COMPATIBILITY SameMajorVersion
)

install(FILES ${CMAKE_CURRENT_BINARY_DIR}/FortTimeConfig.cmake
			  ${CMAKE_CURRENT_BINARY_DIR}/FortTimeConfigVersion.cmake
		DESTINATION ${LIB_INSTALL_DIR}/FortTime/cmake
)

add_subdirectory(src/fort/time)

if(BUILD_DOCS)
	add_subdirectory(docs)
endif(BUILD_DOCS)
