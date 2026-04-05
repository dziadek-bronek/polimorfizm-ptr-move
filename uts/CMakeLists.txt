#	project-dir
#		/ src
#		/ CMakeLists.txt
#		/ build
#
#		/ uts
#			/ src
#			/ CMakeLists.txt
#			/ build-uts

cmake_minimum_required(VERSION 3.10)
project(polimorfizm-ptr-move-uts)

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG main
)

FetchContent_MakeAvailable(googletest)

enable_testing()
add_test(mytests mytests)

add_executable(mytests
#	src/ut.cpp
#	src/asc-ut.cpp
	src/asc-ut.cpp
)

target_link_libraries(mytests
	/home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build/libmylib.so
	gtest gmock_main gmock
)

