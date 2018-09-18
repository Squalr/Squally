#.rst:
# FindUdis86
# ------------
#
# Locate UDIS86 library
#
# This module defines
#
# ::
#
#   UDIS86_LIBRARIES, the library to link against
#   UDIS86_FOUND, the libraries needed to use UDIS86
#   UDIS86_INCLUDE_DIRS, where to find headers.
#

find_path(UDIS86_INCLUDE_DIR
	NAMES Udis86/udis86.h
	PATH_SUFFIXES include
)

find_library(UDIS86_LIBRARY 
	NAMES Udis86
	PATH_SUFFIXES lib
)

include_directories(
  ..
)

set(UDIS86_INCLUDE_DIRS "${UDIS86_INCLUDE_DIR}")
set(UDIS86_LIBRARIES "${UDIS86_LIBRARY}")

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(UDIS86 DEFAULT_MSG UDIS86_LIBRARIES UDIS86_INCLUDE_DIRS)

mark_as_advanced(UDIS86_INCLUDE_DIR UDIS86_LIBRARY)
