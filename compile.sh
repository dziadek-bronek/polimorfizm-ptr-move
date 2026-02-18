# in the higher level, where CMakeLists.txt is located, create directory 'build' and go to this directory
cd build
clear ; rm -rf * ; cmake ..
clear ; make # alternative: cmake --build .
clear ; ./polimorfizm-ptr-move 
