# Advanced-Programming-ex 1 part 2
this is the manual for the second part of Ex1.

**to compile and run perform the following commands:**
1. git init
2. git clone https://github.com/OrrBav/Advanced-Programming-1.git
3. go inside the directory you cloned (by cd Advanced-Programming-1/)
4. you should check that there isn't, for some reason, a previous compiled main file by running the command ls, and if a main file exist (not the main.cpp file), run rm main to remove it
5. g++ function.h (the header file)
6. g++ -std=c++11 *.cpp
7. ./a.out


**Our code includes 4 files:**
1. main.cpp. - the main file of the program. gets input vector from user, and sends them to input_check.cpp to validate the numbers that the user typed, and then prints the result distance of each requested distance method, with a decimal point.
2. input_check.cpp - the two input vectors first undergo a series of input checks, in order to make sure they are a valid input that we can perform calculations on. in addition, it contains print_decimal function, which ensures values are printed as instructed.
3. distanceFunctions.cpp - we compute Euclidean, Manhattan, Chebyshev, Canberra and Minkowski distance, as requested, by the wikipedia formula. each functions returns a float that represents said distance.
Canberra distance has a const of p=1 by default.
4. helperFunctions.cpp - the distance functions use different operations such as absolute value, sum, square root and others, and this files holds all the relevant functions.

when you run the file, you should enter a series of numbers (can have a decimal point) separated by a single space between them, without any spaces before or after the first and last number, accordingly. any deviation from that format, or input vectors that are not of the same size, will result in termination of the program, after an error message.

for example:

![image](https://user-images.githubusercontent.com/101596419/203522356-08c6be9f-b62a-4e16-9c6f-9f2f7d096a00.png)

the code will compute the distance, and will print:

![image](https://user-images.githubusercontent.com/101596419/203522486-b85ae8be-5fab-4490-b4d2-170f09da49a8.png)


following text it for the first part of the exercise:
my first commit
my second commit
