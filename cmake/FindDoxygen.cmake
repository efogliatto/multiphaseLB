find_program(DOXYGEN_EXECUTABLE NAMES doxygen DOC "Doxygen documentation generator"  )

if(NOT DOXYGEN_EXECUTABLE)
    message(FATAL_ERROR "Doxygen not found!")
endif()
