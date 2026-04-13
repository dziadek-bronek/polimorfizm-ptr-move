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

add_test(make-b-ut.c base)
add_test(make-a-asc-ut.c asc)
add_test(make-f-CFrameworkUTs.c CFrameworkUTs)

add_executable(base src/ut.cpp)

add_executable(asc src/asc-ut.cpp)

add_executable(CFrameworkUTs src/CFrameworkUTs.cpp)

# add_executable(CSelectorConfiguratorUTs src/CSelectorConfiguratorUTs.cpp)

target_link_libraries(base
	/home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build/libmylib.so
	gtest gmock_main gmock
)
target_link_libraries(asc
	/home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build/libmylib.so
	gtest gmock_main gmock
)

target_link_libraries(CFrameworkUTs
/home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build/CMakeFiles/mylib.dir/src/CFramework.cpp.o
/home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build/CMakeFiles/mylib.dir/src/CFrameworkIf.cpp.o
	gtest gmock_main gmock
)

#[[
target_link_libraries(CSelectorConfiguratorUTs
/home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build/CMakeFiles/mylib.dir/src/CSelectorConfigurator.cpp.o
/home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build/CMakeFiles/mylib.dir/src/CSelectorConfiguratorIf.cpp.o

/home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build/CMakeFiles/mylib.dir/src/CSelectorIf.cpp.o
	gtest gmock_main gmock
)
]]

add_custom_target(b COMMAND base DEPENDS base)
add_custom_target(a COMMAND asc DEPENDS asc)
add_custom_target(f COMMAND CFrameworkUTs DEPENDS CFrameworkUTs)
# add_custom_target(c COMMAND CSelectorConfiguratorUTs DEPENDS CSelectorConfiguratorUTs)
