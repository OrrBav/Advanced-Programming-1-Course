# Advanced-Programming- Ex 2
this is the manual for Ex2.

**to compile and run perform the following commands:**
1. git init
2. git clone https://github.com/OrrBav/Advanced-Programming-1.git
3. go inside the directory you cloned (by cd Advanced-Programming-1/)
4. you should check that there isn't, for some reason, a previous compiled main file by running the command ls, and if a main file exist (not the main.cpp file), run rm main to remove it
5. g++ function.h (the header file)
6. g++ -std=c++11 *.cpp
7. ./a.out


**Our code is an implementation of the KNN algorithm:**
the program is initiated from main, receiving 3 arguments to init the run-
argv[1] is the chosen k value.
argv[2] is the file name of the classified samples that will be used to predict a new sample.
argv[3] is the chosen distance metric, written as an abbreviation (e.g "MAN" for manhattan distance).
All of these arguments undergo a series of input checks to make sure they are valid. If found not valid- we exit the program with the relevant error.
After initiated, an input vector is requested from the user, so it's class can be predicted by the KNN algorithm. This stage repeats in an infinite loop and the user can test an infinite amount of vectors and classify them.
...
...?

when you run the file, you should enter a series of numbers (can have a decimal point) separated by a single space between them, without any spaces before or after the first and last number, accordingly. any deviation from that format, or input vectors that are not of the same size, will result in termination of the program, after an error message.

for example:

![image](https://user-images.githubusercontent.com/101596419/203522356-08c6be9f-b62a-4e16-9c6f-9f2f7d096a00.png)

the code will compute the distance, and will print:

![image](https://user-images.githubusercontent.com/101596419/203522486-b85ae8be-5fab-4490-b4d2-170f09da49a8.png)



following text is for the first part of the exercise:
my first commit
here ariel do hes first commit and i deleted orr's second commit!
my third commit
my forth commit

