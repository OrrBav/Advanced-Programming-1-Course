# Advanced-Programming- Ex 2
this is the manual for Ex2.

**to compile and run perform the following commands:**
1. git init
2. git clone -b Ex2-Master-Branch https://github.com/OrrBav/Advanced-Programming-1.git (the designated branch for Ex2)
3. cd Advanced-Programming-1
4. make
5 ./a.out argv[1](k value) argv[2] (path of file) argv[3] (distance matric).

**Our code is an implementation of the KNN algorithm:**
the program is initiated from main, receiving 3 arguments to init the run-
argv[1] is the chosen k value.
argv[2] is the file name of the classified samples that will be used to predict a new sample.
argv[3] is the chosen distance metric, written as an abbreviation (e.g "MAN" for manhattan distance).
All of these arguments undergo a series of input checks to make sure they are valid. If found not valid- we exit the program with the relevant error.
After initiated, an input vector is requested from the user, so it's class can be predicted by the KNN algorithm. This stage repeats in an infinite loop and the user can test an infinite amount of vectors and classify them.
The code comprised of couple of key classes: first we use Readfromfile.cpp to read the input csv file and ensure the input for KNN class will be accurate. from there, we create the Knn class that implemants the KNN algorithem, with the use of distancematric class, which holds the distance matrics from the previous exercise. 


when you run the file, you should enter a series of numbers (can have a decimal point) separated by a single space between them, without any spaces before or after the first and last number, accordingly. any deviation from that format, or input vectors that are not of the same size, will result in termination of the program, after an error message.

for example:
![image](https://user-images.githubusercontent.com/101596419/207710882-94903924-cefe-4ab6-8bd7-cca1e4a52a3b.png)


