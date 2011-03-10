redo-ifchange data.o
redo-ifchange data_main.o
gcc -o $3 data.o data_main.o -lstdc++
