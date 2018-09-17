#.rst:
# FindSpriterPlusPlus
# ------------
#
# Locate SPRITER_PLUS_PLUS library
#
# This module defines
#
# ::
#
#   SPRITER_PLUS_PLUS_LIBRARIES, the library to link against
#   SPRITER_PLUS_PLUS_FOUND, the libraries needed to use SPRITER_PLUS_PLUS
#   SPRITER_PLUS_PLUS_INCLUDE_DIRS, where to find headers.
#

find_path(SPRITER_PLUS_PLUS_INCLUDE_DIR
	NAMES SPRITER_PLUS_PLUS/spriterengine/spriterengine.h
	PATH_SUFFIXES include
)

find_library(SPRITER_PLUS_PLUS_LIBRARY 
	NAMES SPRITER_PLUS_PLUS
	PATH_SUFFIXES lib
)

set(SPRITER_PLUS_PLUS_INCLUDE_DIRS "${SPRITER_PLUS_PLUS_INCLUDE_DIR}")
set(SPRITER_PLUS_PLUS_LIBRARIES "${SPRITER_PLUS_PLUS_LIBRARY}")

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(SPRITER_PLUS_PLUS DEFAULT_MSG SPRITER_PLUS_PLUS_LIBRARIES SPRITER_PLUS_PLUS_INCLUDE_DIRS)

mark_as_advanced(SPRITER_PLUS_PLUS_INCLUDE_DIR SPRITER_PLUS_PLUS_LIBRARY)
