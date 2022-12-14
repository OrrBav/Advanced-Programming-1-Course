a.out: distanceMatric.o helperFunctions.o input_check.o knn.o readFromFile.o main.o
	g++ distanceMatric.o helperFunctions.o input_check.o knn.o readFromFile.o main.o -o a.out

distanceMatric.o:
	g++ -std=c++11 -c distanceMatric.cpp distanceMatric.h

helperFunctions.o:
	g++ -std=c++11 helperFunctions.cpp function.h

input_check.o:
	g++ -std=c++11 -c input_check.cpp function.h

knn.o:
	g++ -std=c++11 -c knn.cpp knn.h

readFromFile.o:
	g++ -std=c++11 -c readFromFile.cpp readFromFile.h

main.o:
	g++ -std=c++11 -c main.cpp main.h

target: dependencies
	action

clean:
	rm *.o *.h.gch a.out