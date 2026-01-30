cmake_minimum_required(VERSION 3.5)

project(polimorfizm-ptr-move-proj)

add_library(mylib SHARED
    src/children.cpp
    src/child-creator.cpp
    src/produce-child-creators.cpp
    src/child-creators-register.cpp
)

add_executable(polimorfizm-ptr-move
    src/main.cpp
    )

target_link_libraries(polimorfizm-ptr-move mylib)
