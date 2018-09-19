#.rst:
# FindCereal
# ------------
#
# Locate CEREAL library
#
# This module defines
#
# ::
#
#   CEREAL_LIBRARIES, the library to link against
#   CEREAL_FOUND, the libraries needed to use CEREAL
#   CEREAL_INCLUDE_DIRS, where to find headers.
#

find_path(CEREAL_INCLUDE_DIR
	NAMES CEREAL/cereal.hpp
	PATH_SUFFIXES include
)

find_library(CEREAL_LIBRARY
	NAMES CEREAL
	PATH_SUFFIXES lib
)

set(CEREAL_INCLUDE_DIRS "${CEREAL_INCLUDE_DIR}")
set(CEREAL_LIBRARIES "${CEREAL_LIBRARY}")

include(${CMAKE_CURRENT_LIST_DIR}/FindPackageHandleStandardArgs.cmake)
find_package_handle_standard_args(CEREAL DEFAULT_MSG CEREAL_LIBRARIES CEREAL_INCLUDE_DIRS)

mark_as_advanced(CEREAL_INCLUDE_DIR CEREAL_LIBRARY)
