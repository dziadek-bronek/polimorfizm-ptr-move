# in the higher level, where CMakeLists.txt is located, create directory 'build' and go to this directory
#clear ; rm -rf build/* ; cmake ..


clear

cd ~/cprogs/github/polimorfizm-ptr-move/build && rm -rf ~/cprogs/github/polimorfizm-ptr-move/build/* ; cmake .. &&  cmake --build .  # alternative command: make

# clear


# clear
echo; echo; echo; ./polimorfizm-ptr-move 
