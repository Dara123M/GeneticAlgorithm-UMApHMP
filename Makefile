gen: main.o gen.o population.o loading.o 
	g++ -Wall -g -o gen main.o gen.o population.o loading.o

gen1: main.o gen.o population.o loading.o 
	g++ -Wall -g -o gen1 main.o gen.o population.o loading.o

gen2: main.o gen.o population.o loading.o 
	g++ -Wall -g -o gen2 main.o gen.o population.o loading.o

gen3: main.o gen.o population.o loading.o 
	g++ -Wall -g -o gen3 main.o gen.o population.o loading.o

main.o: main.cpp headers/population.hpp headers/loading.hpp
	g++ -Wall -c main.cpp

gen.o: code/gen.cpp headers/gen.hpp
	g++ -Wall -c code/gen.cpp 

population.o: code/population.cpp headers/population.hpp
	g++ -Wall -c code/population.cpp

loading.o: code/loading.cpp headers/loading.hpp
	g++ -Wall -c code/loading.cpp

.PHONY: clean

clean:
	rm *.o
