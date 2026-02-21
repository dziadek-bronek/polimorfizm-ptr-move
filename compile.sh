# in the higher level, where CMakeLists.txt is located, create directory 'build' and go to this directory
cd build
clear ; rm -rf ~/cprogs/github/polimorfizm-ptr-move/build/* ; cmake ..
clear ; make # alternative: cmake --build .
clear ; ./polimorfizm-ptr-move 

# to format:
clang-format -i -style=chromium src/*.cpp
clang-format -i -style=chromium src/include/*.hpp
