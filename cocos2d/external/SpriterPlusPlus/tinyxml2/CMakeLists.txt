project(TINYXML2 CXX)

set(TINYXML2_HDRS
    tinyxml2.h)

set(TINYXML2_SRCS
    tinyxml2.cpp)

add_library(tinyxml2 STATIC
    ${TINYXML2_SRCS})
