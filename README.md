# BIG_INT:A-New-Datatype
This project implements basic arithmetic operations (addition, subtraction, and multiplication) on large integers using custom algorithms, bypassing the limitations of built-in data types like int or long. 
It uses a BigInt structure where each digit of the large number is stored in an array in reverse order.
The ADD(), SUB(), and MULTI() functions handle the addition, subtraction, and multiplication of large numbers by processing each digit and managing carryovers and borrow operations.
The project also includes a compare() function for comparing two large integers and methods for inputting and displaying the numbers. 
The input function converts a string to a BigInt and the display function prints the number in a readable format, removing leading zeros and correctly handling the sign. 
This approach demonstrates how arbitrary precision arithmetic works by simulating fundamental number operations, useful in fields like cryptography and scientific computing.
