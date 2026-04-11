clear
mkdir /home/dtstgseete/cprogs/github/polimorfizm-ptr-move/uts/build-uts
cd /home/dtstgseete/cprogs/github/polimorfizm-ptr-move/uts/build-uts
#if clear-all, then:
#rm -rf /home/dtstgseete/cprogs/github/polimorfizm-ptr-move/uts/build-uts/*

cmake .. &&  cmake --build . && make test
#cmake .. &&  cmake --build . &&  { echo; echo; echo; ./asc; }
#cmake .. &&  cmake --build . &&  { echo; echo; echo; ./asc; }
#cmake .. &&  make CFrameworkUTs

# for the command 'cmake --build .' alternative is command: 'make'
# for the command  'make' alternative is command: 'make all'??

