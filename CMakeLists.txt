cmake_minimum_required(VERSION 3.21.2)

project(FirstTrial)

SET(APP_EXE main)

ADD_EXECUTABLE(${APP_EXE} main.c) 

ADD_LIBRARY(bit STATIC bitString.c checkEndianness.c crc.c gettersAndSetters.c)


TARGET_LINK_LIBRARIES(${APP_EXE} bit)