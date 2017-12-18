cmake_minimum_required(VERSION 3.4.1)



set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -DNDEBUG -O3")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -fno-rtti -fno-exceptions -Wall -DNDEBUG -O3")


add_library(ccurl SHARED
            CCurl.cpp
            curl.c
            pearl_diver.c
            converter.c
            )

# Include libraries needed for lib
target_link_libraries(ccurl
                      android
                      log
                      m)
