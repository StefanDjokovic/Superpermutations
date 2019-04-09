# Superpermutations

*Currently this repo contains a superpermutation checker written in c, `Build_Hash_Permutations.c`*

___

Inspired by [Matt Parker's video](https://www.youtube.com/watch?v=OZzIvl1tbPo) I decided to give it a go on trying to find the smallest superpermutation of N elements.


A superpermutation is a string that contains all the possible permutations of an initial string. Finding the smallest superpermutation is still an open problem for values larger than 5, and researchers are still looking both into finding them and maths proofs. More infos can be found on the internet, in particular on [Numberphile's YT channel](https://www.youtube.com/user/numberphile), [Matt Parker's YT channel](https://www.youtube.com/user/standupmaths/videos) and this [Google group](https://groups.google.com/forum/#!forum/superpermutators)

___

*My work:*

I started by building a hash table of all the N possible elements, and implementing a function getHashValue which works extremly well for N<11

>On `Super_Fast_Superpermutation_checker.c`

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

