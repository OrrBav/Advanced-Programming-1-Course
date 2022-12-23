a.out: main.o distanceMatric.o helperFunctions.o input_check.o knn.o readFromFile.o
	g++ main.o distanceMatric.o helperFunctions.o input_check.o knn.o readFromFile.o -o a.out

main.o: main.cpp main.h
	g++ -std=c++11 -c main.cpp

distanceMatric.o: distanceMatric.cpp distanceMatric.h
	g++ -std=c++11 -c distanceMatric.cpp

helperFunctions.o: helperFunctions.cpp function.h
	g++ -std=c++11 -c helperFunctions.cpp

input_check.o: input_check.cpp function.h
	g++ -std=c++11 -c input_check.cpp

knn.o: knn.cpp knn.h
	g++ -std=c++11 -c knn.cpp

readFromFile.o: readFromFile.cpp readFromFile.h
	g++ -std=c++11 -c readFromFile.cpp

clean:
	rm *.o a.out