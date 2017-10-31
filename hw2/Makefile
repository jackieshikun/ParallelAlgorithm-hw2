test : main.o sort.o
	g++ -std=c++11 -lpthread -o test main.o sort.o

sort.o : sort.cpp
	g++ -std=c++11 -c sort.cpp sort.hpp -pthread

main.o : main.cpp
	g++ -std=c++11 -c main.cpp sort.cpp sort.hpp -pthread
clean :
	rm *.o test *.gch
