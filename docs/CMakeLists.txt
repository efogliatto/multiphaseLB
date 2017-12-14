# Doxygen

find_package(Doxygen REQUIRED)

add_custom_target(mutiphaseLB_doxydocs ALL ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile" COMMENT "Building documentation with Doxygen")
# add_custom_command(
#   OUTPUT "${CMAKE_CURRENT_SOURCE_DIR}/doxygen.stamp"
#   COMMAND ${DOXYGEN_EXECUTABLE} "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile"
#   COMMAND cmake -E touch "${CMAKE_CURRENT_SOURCE_DIR}/doxygen.stamp"
#   COMMENT "Building documentation with Doxygen"
#   )



# Sphinx

find_package(Sphinx REQUIRED)

add_custom_target(mutiphaseLB_docs ALL
    ${SPHINX_EXECUTABLE}
        -q -b html
        -c "${CMAKE_CURRENT_SOURCE_DIR}/source"
        -d "${CMAKE_CURRENT_BINARY_DIR}/_doctrees"
        "${CMAKE_CURRENT_SOURCE_DIR}/source"
        "${CMAKE_CURRENT_BINARY_DIR}/html"
    COMMENT "Building HTML documentation with Sphinx")
