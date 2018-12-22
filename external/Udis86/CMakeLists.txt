set(UDIS86_SRC
  libudis86/decode.c
  libudis86/decode.h
  libudis86/extern.h
  libudis86/itab.c
  libudis86/itab.h
  libudis86/syn-att.c
  libudis86/syn-intel.c
  libudis86/syn.c
  libudis86/syn.h
  libudis86/types.h
  libudis86/udint.h
  libudis86/udis86.c
)

include_directories(
  ..
)

add_library(udis86 STATIC
  ${UDIS86_SRC}
)

set_target_properties(udis86
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
