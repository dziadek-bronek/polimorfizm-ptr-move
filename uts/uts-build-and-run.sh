clear
mkdir /home/dtstgseete/cprogs/github/polimorfizm-ptr-move/uts/build-uts
cd /home/dtstgseete/cprogs/github/polimorfizm-ptr-move/uts/build-uts
#if clear-all, then:
#rm -rf /home/dtstgseete/cprogs/github/polimorfizm-ptr-move/uts/build-uts/*
cmake .. &&  make CFrameworkUTs
#cmake .. &&  cmake --build . && make CFrameworkUTs
#cmake .. &&  cmake --build . &&  { echo; echo; echo; ./asc; }
#cmake .. &&  cmake --build . &&  { echo; echo; echo; ./asc; }
# for the command 'cmake --build .' alternative is command: 'make'

