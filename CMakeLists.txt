cmake_minimum_required(VERSION 2.6)
project(minature-ghosthack)

###########
## CMAKE ##
###########

# Set an output directory for our binaries
set(BIN_DIR ${minature-ghosthack_SOURCE_DIR}/bin)

###########
## FLAGS ##
###########
# Bump up warning levels appropriately for clang, gcc & msvc
# Also set debug/optimization flags depending on the build type. IDE users choose this when
# selecting the build mode in their IDE
if (${CMAKE_CXX_COMPILER_ID} STREQUAL "GNU" OR ${CMAKE_CXX_COMPILER_ID} STREQUAL "Clang")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -std=c++11")
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_DEBUG} -g")
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} ${CMAKE_CXX_FLAGS_RELEASE} -O2")
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL "MSVC")
	if (CMAKE_CXX_FLAGS MATCHES "/W[0-4]")
		string(REGEX REPLACE "/W[0-4]" "/W4" CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
	else()
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4")
	endif()
endif()


#############
## INCLUDE ##
#############

#Recursively add files from source folder to
#list to be compiled, removing duplicates
file(GLOB_RECURSE minature-ghosthack_SOURCES "src/*.cpp")
file(GLOB_RECURSE minature-ghosthack_HEADERS "include/*.h")

set (minature-ghosthack_INCLUDE_DIRS "")
foreach (_headerFile ${minature-ghosthack_HEADERS})
    get_filename_component(_dir ${_headerFile} PATH)
    list (APPEND minature-ghosthack_INCLUDE_DIRS ${_dir})
endforeach()
list(REMOVE_DUPLICATES minature-ghosthack_INCLUDE_DIRS)

include_directories(${minature-ghosthack_INCLUDE_DIRS})


#############
## COMPILE ##
#############
#Sets executable file extension to .exe
set(CMAKE_EXECUTABLE_SUFFIX ".exe")


add_executable(minature-ghosthack ${minature-ghosthack_SOURCES})

#Link libraries
target_link_libraries(minature-ghosthack)

#############
## INSTALL ##
#############
install(TARGETS minature-ghosthack RUNTIME DESTINATION ${BIN_DIR})
