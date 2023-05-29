gen: main.o gen.o population.o loading.o 
	g++ -Wall -g -o gen main.o gen.o population.o loading.o


main.o: main.cpp population.hpp loading.hpp
	g++ -Wall -c main.cpp

genetski.o: gen.cpp gen.hpp
	g++ -Wall  -c gen.cpp 

population.o: population.cpp population.hpp
	g++ -Wall -c population.cpp

loading.o: loading.cpp loading.hpp
	g++ -Wall -c loading.cpp

.PHONY: clean

clean:
	rm *.o
