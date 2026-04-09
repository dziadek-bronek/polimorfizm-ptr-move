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

add_test(mytest-ut base)
add_test(mytest-asc asc)

add_executable(base
	src/ut.cpp
)

add_executable(asc
	src/asc-ut.cpp
)

target_link_libraries(base
	/home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build/libmylib.so
	gtest gmock_main gmock
)

target_link_libraries(asc
	/home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build/libmylib.so
	gtest gmock_main gmock
)

add_custom_target(b COMMAND base DEPENDS base)
add_custom_target(a COMMAND asc DEPENDS asc)
