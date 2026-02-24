# from the directory polimorfizm-ptr-move issue commands:
# makedir build-uts
# cd build-uts
# rm -rf ../build-uts/* && cmake ../uts
# cmake ../uts && make && ./mytests

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
	src/ut.cpp
)

target_link_libraries(mytests
	/home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build/libmylib.so
	gtest #/home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build-uts/lib/gtest.a
	gmock_main #/home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build-uts/lib/gmock_main.a
	gmock #/home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build-uts/lib/gmock.a
)

