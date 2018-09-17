project(librecast C CXX)

################################################################################
# Source groups
################################################################################
set(DebugUtils
    ../DebugUtils/DebugDraw.cpp
    ../DebugUtils/DebugDraw.h
    ../DebugUtils/DetourDebugDraw.cpp
    ../DebugUtils/DetourDebugDraw.h
)
source_group("DebugUtils" FILES ${DebugUtils})

set(Detour
    ../Detour/DetourAlloc.cpp
    ../Detour/DetourAlloc.h
    ../Detour/DetourAssert.h
    ../Detour/DetourCommon.cpp
    ../Detour/DetourCommon.h
    ../Detour/DetourMath.h
    ../Detour/DetourNavMesh.cpp
    ../Detour/DetourNavMesh.h
    ../Detour/DetourNavMeshBuilder.cpp
    ../Detour/DetourNavMeshBuilder.h
    ../Detour/DetourNavMeshQuery.cpp
    ../Detour/DetourNavMeshQuery.h
    ../Detour/DetourNode.cpp
    ../Detour/DetourNode.h
    ../Detour/DetourStatus.h
)
source_group("Detour" FILES ${Detour})

set(DetourCrowd
    ../DetourCrowd/DetourCrowd.cpp
    ../DetourCrowd/DetourCrowd.h
    ../DetourCrowd/DetourLocalBoundary.cpp
    ../DetourCrowd/DetourLocalBoundary.h
    ../DetourCrowd/DetourObstacleAvoidance.cpp
    ../DetourCrowd/DetourObstacleAvoidance.h
    ../DetourCrowd/DetourPathCorridor.cpp
    ../DetourCrowd/DetourPathCorridor.h
    ../DetourCrowd/DetourPathQueue.cpp
    ../DetourCrowd/DetourPathQueue.h
    ../DetourCrowd/DetourProximityGrid.cpp
    ../DetourCrowd/DetourProximityGrid.h
)
source_group("DetourCrowd" FILES ${DetourCrowd})

set(DetourTileCache
    ../DetourTileCache/DetourTileCache.cpp
    ../DetourTileCache/DetourTileCache.h
    ../DetourTileCache/DetourTileCacheBuilder.cpp
    ../DetourTileCache/DetourTileCacheBuilder.h
)
source_group("DetourTileCache" FILES ${DetourTileCache})

set(fastlz
    ../fastlz/fastlz.c
    ../fastlz/fastlz.h
)
source_group("fastlz" FILES ${fastlz})

set(ALL_FILES  ${DebugUtils} ${DetourCrowd} ${DetourTileCache} ${Detour} ${fastlz})

################################################################################
# Target
################################################################################
add_library(${PROJECT_NAME} STATIC ${ALL_FILES})

if(NOT ("${CMAKE_VS_PLATFORM_NAME}" STREQUAL "Win32"))
    message(WARNING "${CMAKE_VS_PLATFORM_NAME} arch is not supported!")
endif()

################################################################################
# Target name
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${TARGET_NAME})

################################################################################
# Output directory
################################################################################
set_target_properties(${PROJECT_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${OUT_DIR})
set_target_properties(${PROJECT_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${OUT_DIR})

################################################################################
# Compile definitions
################################################################################

################################################################################
# Compile and link options
################################################################################
if(MSVC)
endif()

