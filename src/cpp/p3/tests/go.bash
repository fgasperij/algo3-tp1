#!/bin/bash

g++ -std=c++0x p3-test.cpp -o p3-test
g++ -O3 randomGen.cpp -o randomGen
./randomGen > instancias.txt
cat instancias.txt | ./p3-test > tiempos_con_ambas_podas.txt
