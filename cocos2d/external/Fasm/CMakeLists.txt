set(FASM_SRC
  Fasm.cpp
  Fasm.h
)

include_directories(
  ..
)

add_library(fasm STATIC
  ${FASM_SRC}
)

set_target_properties(fasm
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
