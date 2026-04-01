clear
mkdir /home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build
cd /home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build
# if clear all, then:
# rm -rf /home/dtstgseete/cprogs/github/polimorfizm-ptr-move/build/*
cmake .. &&  cmake --build . && { echo; echo; echo; ./polimorfizm-ptr-move; }
# for the command 'cmake --build .' alternative is command: 'make'

