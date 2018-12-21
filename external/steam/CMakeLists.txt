project(STEAM)

file(GLOB_RECURSE STEAM_SRC "*.cpp" "*.h")

include_directories(
  ..
)

add_library(steam STATIC
  ${STEAM_SRC}
)

set(STEAM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${STEAM_INCLUDE_DIR})

IF (APPLE)
	target_link_libraries(steam ${CMAKE_CURRENT_SOURCE_DIR}/redistributable_bin/osx32/libsteam_api.dylib)
ELSEIF (UNIX)
	IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
		target_link_libraries(steam ${CMAKE_CURRENT_SOURCE_DIR}/redistributable_bin/linux32/libsteam_api.so)
	ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 8)
		target_link_libraries(steam ${CMAKE_CURRENT_SOURCE_DIR}/redistributable_bin/linux64/libsteam_api.so)
	ENDIF()
ELSEIF (WIN32)
	IF(CMAKE_SIZEOF_VOID_P EQUAL 4)
		target_link_libraries(steam ${CMAKE_CURRENT_SOURCE_DIR}/redistributable_bin/steam_api.lib)
	ELSEIF(CMAKE_SIZEOF_VOID_P EQUAL 8)
		target_link_libraries(steam ${CMAKE_CURRENT_SOURCE_DIR}/redistributable_bin/win64/steam_api64.lib)
	ENDIF()
ENDIF()

set_target_properties(steam
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib"
)

INCLUDE(FindPackageHandleStandardArgs)