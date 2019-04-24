# Superpermutations

Inspired by [Matt Parker's video](https://www.youtube.com/watch?v=OZzIvl1tbPo) I decided to give a go to the "shortest superpermutation problem".


A superpermutation is a string that contains all the possible permutations of an initial string. Finding the smallest superpermutation is still an open problem for values larger than 5, and researchers are still looking both into finding them and Maths proofs. More infos and links can be found on [Numberphile's YT channel](https://www.youtube.com/user/numberphile), [Matt Parker's YT channel](https://www.youtube.com/user/standupmaths/videos) and this [Google group](https://groups.google.com/forum/#!forum/superpermutators)

___

**My work:**

>MyTakeOnChaffinMethod folder

Ben Chaffin was the first to show with code that the minimum length of a superpermutation of N = 5 is 153. To prove it he designed the code available here http://www.njohnston.ca/2014/08/all-minimal-superpermutations-on-five-symbols-have-been-found/

Based on the idea of "wasted characters" and the indexing of permutations I designed my own solution. My code takes, as of the 23/04 updates, 0.2s to complete with N = 5 and it takes roughly 8 minutes to get to w = 101. To actually solve the problem it will still take some work, but I'm confident that it's possible to arrive to the solution through some optimization.

I will soon add a README inside the folder and add explecative comments.

The current "state of the art" for the ChaffinMethod can be found here https://github.com/superpermutators/superperm/tree/master/ChaffinMethod


>On `SupPerm_Checker-from-file.c` and the 11/04/2019 improvements

`SupPerm_Checker-from-file.c` takes the file directory from standard input, the value of N, and prints out if the permutations found are valid superpermutations. The source file should contain one superpermutation per line, and the code can also ignore # comment lines. The superpermutations should be made of numbers starting from 1 (easily interchangeble to letters, read comments in code). There is no error-handling for wrong N input, so please be sure to insert the right one.

The program runs until the EOF, and prints in output the number of permutation and if it's a superpermutation. The two main important functions used are:
* runChecker: it's the function that evaluates if the string recieved is a superpermutation by running getHashValue for every block of N
* getHashValue: gets the unique code of permutation of each blocks and returns it, -1 if there are at least two identical characters in the block

>on the recent improvements of `SupPerm_Checker-from-file.c` compared to the previous code

By storing the N possible values of factorial in an array and passing it to the funciton there was a 0.2X speed boost. The main speed boost (of over 2X on all test types) came by allocating the checker array only once and zeroing it after each array run. 

Some stats on the improvement:
* on 270 superpermutation of N = 9: from 73s to 32s (with 12/04 edits down to 29s)
* on 1024 superpermutation of N = 6: from 457ms to 180 ms (with 12/04 edits down to 160ms)

I've tried other changes to improve the speed (e.g. building a matrix of all the possible values of N * factorial(all the possible values of N)) but the was no noticable improvement. Also I tried changing a bit of the getHashValue structure, in particular on how it counts the number of values it has used, but for now I couldn't find a better solution.

Also a big thank you to Miles Gould from the Superpermutators Google Group who gave me some interesting inputs on how to improve the code.

A graphic explanation of the getHashValue function

![image](https://i.imgur.com/QQyH8UT.jpg)


**Older code comments**

>On `SupPerm_Checker.c` && `SupPerm_Checker-from-file.c`

Based on `Superpermutation_checker.c` but reducing the memory usage by taking away the string in the struct, just the hashValue function is sufficient.

Because most of the superpermutations generated are number based I decided to make this implementation numbers-only. Implementing letters requires just a couple of adds in the hashValue function.

In the "from-file" version the file directory and N should be inserted from standard input.

>On `Superpermutation_checker.c`, older code

I used the same code as in `Build_Hash_Permutations.c` and added some small parts to make it work both with capital letters (starting from A) and numbers (starting from 1). I checked it on known superpermutations and it works very well, taking it less than a second to complete.

In the first lines of the file there are the instructions on how to run it.

If the string is of N >= 9 an upload from the file may be needed. If someone needs it I can update the program to do it.

>On `Build_Hash_Permutations.c`

Trying to figure out how to build an hash and inserting all the elements in exactly N! spaces was kinda harder than expected. I couldn't find any code that gets a value of a permutation, so I build my own from the ground up. It may not be the best, but it works perfectly.

The solution I found was getting an array that would keep track of the elements used, and then use the following system to get the string given i position in the hash:
* the first letter is i / factorial(N - 1)
* then I place a 1 in the space of the array equal to the first letter
* the following values are given by the "value" (the after) of element divided by the factorial of the elements left

The value of an element is given by the number of unused elements before it. For example, given a string ABCD, the initial values of these letters are A=0, B=1, C=2, D=3; if the first letter used is B, A will keep the value 0, but C=1 and D=2. This gives a consistant value to all of the possible permutations of N different elements.


The hash can be built fine with N = 10, but with N = 11 it starts using around 3GB, and with 12 it goes beyond my PC's RAM.
Still, the computation required for finding a permutation of N>10 elements would require more computing power than currently available.

___

