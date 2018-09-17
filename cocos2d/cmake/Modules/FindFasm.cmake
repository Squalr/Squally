#.rst:
# FindFasm
# ------------
#
# Locate FASM library
#
# This module defines
#
# ::
#
#   FASM_LIBRARIES, the library to link against
#   FASM_FOUND, the libraries needed to use FASM
#   FASM_INCLUDE_DIRS, where to find headers.
#

find_path(FASM_INCLUDE_DIR
	NAMES Fasm/Fasm.h
	PATH_SUFFIXES include
)

find_library(FASM_LIBRARY 
	NAMES Fasm
	PATH_SUFFIXES lib
)

include_directories(
  ..
)

set(FASM_INCLUDE_DIRS "${FASM_INCLUDE_DIR}")
set(FASM_LIBRARIES "${FASM_LIBRARY}")

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(FASM DEFAULT_MSG FASM_LIBRARIES FASM_INCLUDE_DIRS)

mark_as_advanced(FASM_INCLUDE_DIR FASM_LIBRARY)
