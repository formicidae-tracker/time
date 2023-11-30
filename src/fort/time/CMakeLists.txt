configure_file(version.hpp.in version.hpp @ONLY)

add_library(fort-time SHARED Time.cpp Time.hpp)

target_link_libraries(fort-time protobuf::libprotobuf)
if(NEED_RT_LINK)
	target_link_libraries(fort-time "-lrt")
endif(NEED_RT_LINK)

set_target_properties(
	fort-time PROPERTIES VERSION ${PROJECT_VERSION_API} SOVERSION
														${PROJECT_VERSION_ABI}
)

if(NOT FORT_TIME_IMPORTED)
	add_executable(fort-time-tests main-check.cpp TimeUTest.cpp TimeUTest.hpp)
	target_link_libraries(fort-time-tests fort-time GTest::gtest_main)

	if(TARGET check)
		add_test(NAME fort-time-tests COMMAND fort-time-tests)
		add_dependencies(check fort-time-tests)
	endif(TARGET check)

else(NOT FORT_TIME_IMPORTED)
	add_library(fort-time::time INTERFACE IMPORTED GLOBAL)
	target_include_directories(
		fort-time::time INTERFACE ${PROJECT_SOURCE_DIR}/src
								  ${PROJECT_BINARY_DIR}/src
	)
	target_link_libraries(fort-time::time INTERFACE fort-time)
endif(NOT FORT_TIME_IMPORTED)

install(FILES Time.hpp ${CMAKE_CURRENT_BINARY_DIR}/version.hpp
		DESTINATION ${INCLUDE_INSTALL_DIR}
)
install(TARGETS fort-time DESTINATION ${LIB_INSTALL_DIR})
