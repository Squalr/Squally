#.rst:
# FindRapidJson
# ------------
#
# Locate RAPIDJSON library
#
# This module defines
#
# ::
#
#   RAPIDJSON_LIBRARIES, the library to link against
#   RAPIDJSON_FOUND, the libraries needed to use RAPIDJSON
#   RAPIDJSON_INCLUDE_DIRS, where to find headers.
#

find_path(RAPIDJSON_INCLUDE_DIR
	NAMES RAPIDJSON/rapidjson.h
	PATH_SUFFIXES include
)

find_library(RAPIDJSON_LIBRARY
	NAMES RAPIDJSON
	PATH_SUFFIXES lib
)

set(RAPIDJSON_INCLUDE_DIRS "${RAPIDJSON_INCLUDE_DIR}")
set(RAPIDJSON_LIBRARIES "${RAPIDJSON_LIBRARY}")

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(RAPIDJSON DEFAULT_MSG RAPIDJSON_LIBRARIES RAPIDJSON_INCLUDE_DIRS)

mark_as_advanced(RAPIDJSON_INCLUDE_DIR RAPIDJSON_LIBRARY)
