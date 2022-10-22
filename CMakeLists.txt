#
# File: CMakeLists.txt
# Project: Extermination
# File Created: Saturday, 24th September 2022 8:19:28 am
# Author: Marek Fischer
# -----
# Last Modified: Saturday, 24th September 2022 8:19:28 am
# Modified By: Marek Fischer 
# -----
# Copyright - 2022 Deep Vertic
#

cmake_minimum_required(VERSION 3.0)
project(extermination)

##FILES##
file(GLOB_RECURSE sources src/*.cpp src/*.hpp)

##TARGET DEFINITION##
add_executable(extermination ${sources})

##Libs##
add_subdirectory(Yuna libYuna)
add_subdirectory(Yuna/mfGUI libmfGUI)

find_package(SFML REQUIRED audio network graphics window system)

target_include_directories(extermination PUBLIC
							src
							Yuna/includes
							Yuna/mfGui/includes
						)

target_link_libraries(extermination
	${SFML_LIBRARIES} 
	${SFML_DEPENDENCIES}
)

##DEPENDENCIES##

