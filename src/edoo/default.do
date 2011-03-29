if [ -e $1_main.cpp ]; then
  redo-ifchange $1_main.o $1.o
  gcc -o $3 $1_main.o $1.o -lstdc++
fi