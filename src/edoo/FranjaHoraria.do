OBJS="FranjaHoraria_main.o FranjaHoraria.o DataHora.o Data.o Hora.o"
redo-ifchange $OBJS
gcc -o $3 $OBJS -lstdc++