include(SelectLibraryConfigurations)
include(FindPackageHandleStandardArgs)

if(NOT ASMJIT_INCLUDE_DIR)
    FIND_PATH(ASMJIT_INCLUDE_DIR NAMES asmjit/asmjit.h)
endif()

if(NOT ASMJIT_LIBRARY)
    find_library(ASMJIT_LIBRARY_RELEASE NAMES asmjit )
    find_library(ASMJIT_LIBRARY_DEBUG NAMES debug/lib/asmjit )
    select_library_configurations(ASMJIT)
endif()

set(ASMJIT_LIBRARIES ${ASMJIT_LIBRARY})
set(ASMJIT_INCLUDE_DIRS ${ASMJIT_INCLUDE_DIR})

find_package_handle_standard_args(asmjit REQUIRED_VARS ASMJIT_LIBRARY ASMJIT_INCLUDE_DIR)

add_library(asmjit::asmjit UNKNOWN IMPORTED)
set_target_properties(asmjit::asmjit PROPERTIES
    IMPORTED_LOCATION ${ASMJIT_LIBRARY}
    INTERFACE_INCLUDE_DIRECTORIES ${ASMJIT_INCLUDE_DIR}
    INTERFACE_COMPILE_DEFINITIONS ASMJIT_STATIC
)


