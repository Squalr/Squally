project(RAPIDJSON)

file(GLOB_RECURSE RAPIDJSON_SRC "*.cpp" "*.h")

include_directories(
  ..
)

add_library(rapidjson STATIC
  ${RAPIDJSON_SRC}
)

set_target_properties(rapidjson
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)
