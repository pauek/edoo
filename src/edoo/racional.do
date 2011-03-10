DEPS="racional.o racional_main.o"
redo-ifchange $DEPS
gcc -o $3 $DEPS -lstdc++
