include(SelectLibraryConfigurations)
include(FindPackageHandleStandardArgs)

if(NOT UDIS86_INCLUDE_DIR)
    FIND_PATH(UDIS86_INCLUDE_DIR NAMES udis86.h)
endif()

if(NOT UDIS86_LIBRARY)
    find_library(UDIS86_LIBRARY_RELEASE NAMES libudis86 )
    find_library(UDIS86_LIBRARY_DEBUG NAMES debug/lib/libudis86 )
    select_library_configurations(UDIS86)
endif()

set(UDIS86_LIBRARIES ${UDIS86_LIBRARY})
set(UDIS86_INCLUDE_DIRS ${UDIS86_INCLUDE_DIR})

find_package_handle_standard_args(UDIS86 REQUIRED_VARS UDIS86_LIBRARY UDIS86_INCLUDE_DIR)

add_library(udis86::udis86 UNKNOWN IMPORTED)
set_target_properties(udis86::udis86 PROPERTIES
    IMPORTED_LOCATION ${UDIS86_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${UDIS86_INCLUDE_DIR}
)


