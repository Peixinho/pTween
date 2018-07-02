cmake_minimum_required(VERSION 3.1)

project(pTween)

set(CMAKE_CXX_STANDARD 11)


# Check Build Type
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
	add_definitions(-D_DEBUG)
endif ()


# Lib Type
option(STATIC_LIB "Build Static Lib" OFF)
if (STATIC_LIB)
	SET(LIB_TYPE STATIC)
else()
	SET(LIB_TYPE SHARED)
endif()


# Engine Sources
set(SOURCE
	${SOURCE}
	${CMAKE_CURRENT_SOURCE_DIR}/src/pTween/core/pTweenEngine.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/pTween/core/pTweenObject.cpp
)


# Headers
set(HEADERS
	${HEADERS}
	${CMAKE_CURRENT_SOURCE_DIR}/include
)

include_directories(${HEADERS})

# Build Library
add_library(pTween ${LIB_TYPE} ${SOURCE})
