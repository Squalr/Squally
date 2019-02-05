# Finder module for steam sdk
include(FindPackageHandleStandardArgs)

# Root path of steamworks
set(STEAMWORKS_ROOT_PATH "${CMAKE_CURRENT_LIST_DIR}/../external/steam")

# Architecture diameter (32 vs 64 bit)
# TODO: does this work when cross compiling?
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    set(STEAMWORKS_ARCH_WIDTH "32")
elseif(CMAKE_SIZEOF_VOID_P EQUAL 8)
    set(STEAMWORKS_ARCH_WIDTH "64")
else()
    message(ERROR "unsupported architecture width? WTF are you runnning this on?")
endif()

# Library Path
if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    set(STEAMWORKS_API_LIBRARY "${STEAMWORKS_ROOT_PATH}/lib/osx/libsteam_api.dylib")
    set(STEAMWORKS_ENCRYPTEDAPPTICKET_LIBRARY "${STEAMWORKS_ROOT_PATH}/lib/osx/libsdkencryptedappticket.dylib")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    set(STEAMWORKS_API_LIBRARY "${STEAMWORKS_ROOT_PATH}/lib/linux${STEAMWORKS_ARCH_WIDTH}/libsteam_api.so")
    set(STEAMWORKS_ENCRYPTEDAPPTICKET_LIBRARY "${STEAMWORKS_ROOT_PATH}/lib/linux${STEAMWORKS_ARCH_WIDTH}/libsdkencryptedappticket.so")
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Windows")
    set(STEAMWORKS_API_LIBRARY "${STEAMWORKS_ROOT_PATH}/lib/win${STEAMWORKS_ARCH_WIDTH}/steam_api.lib")
    set(STEAMWORKS_ENCRYPTEDAPPTICKET_LIBRARY "${STEAMWORKS_ROOT_PATH}/lib/win${STEAMWORKS_ARCH_WIDTH}/sdkencryptedappticket.lib")
else()
    message(ERROR "Unsupported platform.")
endif()

find_package_handle_standard_args(SteamWorks REQUIRED_VARS
    STEAMWORKS_API_LIBRARY
    STEAMWORKS_ENCRYPTEDAPPTICKET_LIBRARY
)

# Setup targets
if(NOT TARGET SteamWorks::API)
    add_library(SteamWorks::API UNKNOWN IMPORTED)
    set_target_properties(SteamWorks::API PROPERTIES
        IMPORTED_LOCATION "${STEAMWORKS_API_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${STEAMWORKS_ROOT_PATH}"
    )
endif()

if(NOT TARGET SteamWorks::EncryptedAppTicket)
    add_library(SteamWorks::EncryptedAppTicket UNKNOWN IMPORTED)
    set_target_properties(SteamWorks::EncryptedAppTicket PROPERTIES
        IMPORTED_LOCATION "${STEAMWORKS_ENCRYPTEDAPPTICKET_LIBRARY}"
        INTERFACE_INCLUDE_DIRECTORIES "${STEAMWORKS_ROOT_PATH}"
        INTERFACE_LINK_LIBRARIES SteamWorks::API
    )
endif()