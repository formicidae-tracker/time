find_package(Doxygen REQUIRED)

set(DOXYGEN_INPUT_FILES ${PROJECT_SOURCE_DIR}/Time.hpp)
set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/api)
set(DOXYFILE_IN ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
set(DOXYFILE_OUT ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/xml/index.xml)
configure_file(${DOXYFILE_IN} ${DOXYFILE_OUT} @ONLY)

file(MAKE_DIRECTORY ${DOXYGEN_OUTPUT_DIR})
add_custom_command(OUTPUT ${DOXYGEN_INDEX_FILE}
                   DEPENDS ${MYRMIDON_API_DOC_FILES}
                   COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile
                   MAIN_DEPENDENCY ${DOXYFILE_IN}
                   COMMENT "Generate doxygen index")

add_custom_target(fort-time-docs DEPENDS ${DOXYGEN_INDEX_FILE})
