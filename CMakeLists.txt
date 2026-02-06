cmake_minimum_required(VERSION 3.5)

project(polimorfizm-ptr-move-proj)

add_library(mylib SHARED
    src/children.cpp

    src/child-creators.cpp
    src/child-selector.cpp
    
    src/framework.cpp
)

add_executable(polimorfizm-ptr-move
    src/main.cpp
    )

target_link_libraries(polimorfizm-ptr-move mylib)
