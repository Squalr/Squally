project (cereal)

file(GLOB_RECURSE CEREAL_SRC "*.cpp" "*.h" ".hpp")

include_directories(
  ..
)

add_library(cereal STATIC
  ${CEREAL_SRC}
)

set_target_properties(cereal
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
