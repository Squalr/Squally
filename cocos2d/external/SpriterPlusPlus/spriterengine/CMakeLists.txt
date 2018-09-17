project(SPRITER_ENGINE)

file(GLOB_RECURSE SPRITER_ENGINE_SRC "*.cpp" "*.h")

include_directories(
  ..
)

add_library(spriterengine STATIC
  ${SPRITER_ENGINE_SRC}
)

set_target_properties(spriterengine
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
