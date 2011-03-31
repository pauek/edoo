OBJS="DataHora_main.o DataHora.o Data.o Hora.o"
redo-ifchange $OBJS
gcc -o $3 $OBJS -lstdc++