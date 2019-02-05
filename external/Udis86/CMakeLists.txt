cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
project(udis86 VERSION 9999)

add_library(udis86 STATIC
    libudis86/decode.c
    libudis86/decode.h
    libudis86/extern.h
    libudis86/itab.c
    libudis86/itab.h
    libudis86/syn-att.c
    libudis86/syn-intel.c
    libudis86/syn.c
    libudis86/syn.h
    libudis86/types.h
    libudis86/udint.h
    libudis86/udis86.c
)

add_library(udis86::udis86 ALIAS udis86)

target_include_directories(udis86 PUBLIC
    ${PROJECT_SOURCE_DIR}
)
