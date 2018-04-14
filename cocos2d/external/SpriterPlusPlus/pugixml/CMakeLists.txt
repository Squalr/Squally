project(PUGIXML CXX)

set(PUGIXML_HDRS
    pugiconfig.hpp
    pugixml.hpp)

set(PUGIXML_SRCS
    pugixml.cpp)

add_library(pugixml STATIC
    ${PUGIXML_SRCS})
