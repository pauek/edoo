#!/bin/bash

sed -i -e 's/<T>/\textless{}T\textgreater{}/g' \
       -e 's/::::/::/g' \
  _build/latex/Apunts_PBD.tex
