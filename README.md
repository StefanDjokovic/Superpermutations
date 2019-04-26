# Superpermutations

Inspired by [Matt Parker's video](https://www.youtube.com/watch?v=OZzIvl1tbPo) I decided to give a go to the "shortest superpermutation problem".


A superpermutation is a string that contains all the possible permutations of an initial string. Finding the smallest superpermutation is still an open problem for values larger than 5, and researchers are still looking both into finding them and Maths proofs. More infos and links can be found on [Numberphile's YT channel](https://www.youtube.com/user/numberphile), [Matt Parker's YT channel](https://www.youtube.com/user/standupmaths/videos) and this [Google group](https://groups.google.com/forum/#!forum/superpermutators)

___

**My work:**

> `MyTakeOnChaffinMethod` folder

Ben Chaffin was the first to show with code that the minimum length of a superpermutation of N = 5 is 153. To prove it he designed the code available here http://www.njohnston.ca/2014/08/all-minimal-superpermutations-on-five-symbols-have-been-found/

Based on the idea of "wasted characters" and the indexing of permutations I designed my own solution. My code takes, as of the 23/04 updates, 0.2s to complete with N = 5. However N = 6 is way harder to prove, and it requires way more time. The NewChaffinN6.c version is still not good enough to get to the required value, but the speed at which it runs is a big step towards the optimal result.  

There is a more specific README in that folder explaining my approach, and I've added comments in the NewChaffinN6.c code.


Greg Egan has also worked on the ChaffinMethod, his code can be found here:
https://github.com/superpermutators/superperm/tree/master/ChaffinMethod

>On `SupPerm_Checker-from-file.c` 

`SupPerm_Checker-from-file.c` is designed as an easy-to-use and fast superpermutation checker.

It takes the file directory from standard input, the value of N, and prints out if the permutations found are valid superpermutations. The source file should contain one superpermutation per line, and the code can also ignore # comment lines. The superpermutations should be made of numbers starting from 1 (easily interchangeble to letters, read comments in code). There is no error-handling for wrong N input, so please be sure to insert the right one.

The program runs until the EOF, and prints in output the number of permutation and if it's a superpermutation. The two main important functions used are:
* runChecker: it's the function that evaluates if the string recieved is a superpermutation by running getHashValue for every block of N
* getHashValue: gets the unique code of permutation of each blocks and returns it, -1 if there are at least two identical characters in the block

A graphic explanation of the getHashValue function

![image](https://i.imgur.com/QQyH8UT.jpg)

