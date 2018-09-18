#.rst:
# FindAsmJit
# ------------
#
# Locate ASMJIT library
#
# This module defines
#
# ::
#
#   ASMJIT_LIBRARIES, the library to link against
#   ASMJIT_FOUND, the libraries needed to use ASMJIT
#   ASMJIT_INCLUDE_DIRS, where to find headers.
#

find_path(ASMJIT_INCLUDE_DIR
	NAMES asmjit/src/asmjit/asmjit.h
	PATH_SUFFIXES include
)

find_library(ASMJIT_LIBRARY 
	NAMES asmjit
	PATH_SUFFIXES lib
)

include_directories(
  ..
)

set(ASMJIT_INCLUDE_DIRS "${ASMJIT_INCLUDE_DIR}")
set(ASMJIT_LIBRARIES "${ASMJITLIBRARY}")

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(ASMJIT DEFAULT_MSG ASMJIT_LIBRARIES ASMJIT_INCLUDE_DIRS)

mark_as_advanced(ASMJIT_INCLUDE_DIR ASMJIT_LIBRARY)
