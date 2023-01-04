# Advanced-Programming-1 - Ex 3
This is the manual for Ex3.

**to compile and run perform the following commands:**  
Open 2 terminals (1- for server side, 2- for client side):  
On both Terminals 1 & 2:
1. git init  
2. git clone https://github.com/ArielAsh1/Advanced-Programming-1-EX3.git  
3. cd Advanced-Programming-1-EX3  
4. make  
5. **On Terminal 1 (server):** recieves 2 arguments-   
./server.out file_path port  
6. **On terminal 2 (client):** recieves 2 arguments-   
./client.out server ip server_port  

On this exercise, we implemented server and client side with TCP protocol.  
The server classifies input from client, then sends the cllassification back to client, where message is printed.    
The program will loop endlessly, until "-1" is inserted for client side, where client will close itself.  
Server will forver stay running, and therfore we can reconnect to it from a new client with the same command as before: "./client.out ip port".  
To initialize server, run command: "./server.out csv file locatiom port".
Port should be the same for server and client, and between 1024 and 65535.
Ip address should be valid address: 4 numbers, from 0 to 255, separated by dots.
After a succesfull initialize, user will insert input for client: numbers vector, separated by spaces, distance matric and a potisitve integer k.  
All of these arguments undergo a series of input checks to make sure they are valid, on both programs.
If found not valid - the program will print a fitting message, at client side, where user can reinsert a new input.  

The code comprised of couple of key classes, and runs simultaneously both server and client side. Both user functions from helperFunctions.cpp for various reasons, mainly for input check.
Server side will use  Readfromfile.cpp to read the input csv file and ensure the input for KNN class will be accurate,
and Knn class that implemants the KNN algorithem, with the use of distancematric class, which holds the distance matrics from the previous exercise.


when you run the file, you should enter a series of numbers (can have a decimal point) separated by a single space between them, without any spaces before or after the first and last number, accordingly.
any deviation from that format, or input vectors that are not of the same size, will result in termination of the program, after an error message.

For convinience reasons, we added the classified csv file to the repository, so cloning it will result of cloning said files as well.

for example:

client side:

![image](https://user-images.githubusercontent.com/101596419/210170486-bbf7fc3c-1eb0-4c99-8800-c1cc72be33b0.png)

server side:

![image](https://user-images.githubusercontent.com/101596419/210170406-0116c94f-90bb-4f86-9d43-76124c679b56.png)

