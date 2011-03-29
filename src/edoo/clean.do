rm -f *.o
for f in *_main.cpp; do
  rm -f ${f%_main.cpp}
done
