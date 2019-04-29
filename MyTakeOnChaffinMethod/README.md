# My ChaffinMethod approach

!The code has an important bug I will try to fix in the following days!

Most of the following consideration are only present in NewChaffinN6.c. For N5 I don't feel an update is required because it already completes in around 250ms, which is a sufficient speed boost from the original 4 minutes.

**Two Lines on the original ChaffinMethod**

Given a string generated, the Chaffin algorithm attaches a character in the final part of the string. If the last N characters are a valid permutation, and if the the number of wasted characters doesn't go over the limit, it keeps going.

**My program**

Instead of placing a random character, my idea was placing permutations. This speeds the Chaffin algorithm because there is no need to check if the string generated contains a new permutation, and there are other tricks that can only be applied with this method.

Another imporant implementation is an exact and ordered index of permutations, which makes possible the use of the following strategy.
Given the index of the starting string (012345, which is equals to 0), with the arrays connected0, connected1, ... connected5 I can instantly get the index value of a permutation that can be placed in the string with 0 wasted characters, 1  wasted characters and so on. 
The permutations of 0 and 1 wasted characters are unique (e.g. 012345 with w = 0 gives 0123450, while 012345 with w = 1 gives 01234510, so just  a character swap between the first two), while for the others a different strategy is used: given 012345 we know that we have 2 possible for w = 2, 6 for w = 3, and 24 for w = 4. These permutations are consecutive thanks to the indexing, so we just need to get the first permutation of each and the others can be found just adding consecutive +1 to the index generated.

To speed things even further, first it is checked if there are any connected0 values that have not been checked. If so, it keeps going. If now, it's checked if there is a connected1 available. If there is places it and goes back to check connected0, if not it checks connected2, and so on. If by placing a new permutation from connected1 or more the number of wasted characters goes through the limit, it kills the goes back.

**Some notes on the speed-up strategies used**
There are 4 main strategies used to kill the inefficient and useless branches:

1. By adding one wasted character the maximum number of permutations that can be added are 6
2. The program first check if, after adding a new wasted character, there are at least 5 new permutation. If it doesn't happen, it goes to 4, than 3 etc.
3. checker == 0 actually doesn't elimitate the presence of multiple permutations in the complete superpermutation. One explecative example: given 12345612345 checker==0 will avoid the placement of the digit 6 at the end (in fact 123456 was already present at the beginning) but a 6 may appear with 3 wasted characters when 456132 is added. In fact the string 123456123456132 will be checked, making sure that all the possible valuable string are checked
4. mperm_res[towaste] + pfound > max_perm also checks if it's possible that with a certain ammount of wasted characters left to get to a better max_perm. This is strongly tied to point 2 because max_perm is initialized as the precedent max_perm + 4. 

![image](https://i.imgur.com/ufW0LCo.jpg)
