# clang-format -i -style=Microsoft ~/cprogs/github/polimorfizm-ptr-move/src/*.cpp
# clang-format -i -style=Microsoft ~/cprogs/github/polimorfizm-ptr-move/src/include/*.hpp
# clang-format -i -style=Microsoft ~/cprogs/github/polimorfizm-ptr-move/uts/src/*.cpp


# x="Microsoft"
# x="chromium"

x="{$(cat /home/dtstgseete/cprogs/github/my-clang-format | tr '\n' ',')}"

echo "$x"

clang-format -i -style="$x" /home/dtstgseete/cprogs/github/polimorfizm-ptr-move/src/*.cpp
clang-format -i -style="$x" /home/dtstgseete/cprogs/github/polimorfizm-ptr-move/src/*.cpp
clang-format -i -style="$x" /home/dtstgseete/cprogs/github/polimorfizm-ptr-move/src/include/*.hpp
clang-format -i -style="$x" /home/dtstgseete/cprogs/github/polimorfizm-ptr-move/uts/src/*.cpp
