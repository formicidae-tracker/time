
configure_file(version.hpp.in version.hpp @ONLY)

add_library(fort-time SHARED Time.cpp Time.hpp)

target_link_libraries(fort-time ${Protobuf_LIBRARIES})
if(NEED_RT_LINK)
	target_link_libraries(fort-time "-lrt")
endif(NEED_RT_LINK)

set_target_properties(fort-time PROPERTIES VERSION ${PROJECT_VERSION_API}
                                          SOVERSION ${PROJECT_VERSION_ABI})

if(IS_MAIN)
	add_executable(fort-time-tests TimeUTest.hpp TimeUTest.cpp main-check.cpp)

	target_link_libraries(fort-time-tests fort-time gtest)

	add_test(NAME fort-time-tests COMMAND fort-time-tests)
	add_dependencies(check fort-time-tests)
endif(IS_MAIN)


install(FILES Time.hpp ${CMAKE_CURRENT_BINARY_DIR}/version.hpp DESTINATION ${INCLUDE_INSTALL_DIR})
install(TARGETS fort-time DESTINATION ${LIB_INSTALL_DIR})
