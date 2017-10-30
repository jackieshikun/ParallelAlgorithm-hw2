test : main.o sort.o
	g++ -o -pthread test main.o sort.o

sort.o : sort.cpp
	g++ -c sort.cpp sort.hpp -pthread

main.o : main.cpp
	g++ -c main.cpp sort.cpp sort.hpp -pthread
clean :
	rm *.o test *.gch
