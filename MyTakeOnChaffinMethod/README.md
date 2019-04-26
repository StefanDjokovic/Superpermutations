**Two Lines on the original ChaffinMethod**

Given a string generated, the Chaffin algorithm attaches a character in the final part of the string. If the last N characters are a valid permutation, and if the the number of wasted characters doesn't go over the limit, it keeps going.

**My approach**

Instead of placing a random character, my program places a permutation. This speeds the Chaffin algorithm because there is no need to check if the string generated contains a new permutation.

Another imporant implementation is an exact indexing of permutations, which makes possible the use of the following strategy.
Given the index of the starting string (012345, which is equals to 0), with the arrays connected0, connected1, ... connected5 I can instantly get the index value of a permutation that can be placed in the string with 0 wasted characters, 1  wasted characters and so on. 
The permutations of 0 and 1 wasted characters are unique (e.g. 012345 with w = 0 gives 0123450, while 012345 with w = 1 gives 01234510, so just  a character swap between the first two), while for the others a different strategy is used: given 012345 we know that we have 2 possible for w = 2, 6 for w = 3, and 24 for w = 4. These permutations are consecutive thanks to the indexing, so we just need to get the first permutation of each and the others can be found just adding consecutive +1 to the index generated.

To speed things up, first it is checked if there are any connected0 values that have not been checked. If so, it keeps going. If now, it's checked if there is a connected1 available. If there is places it and goes back to check connected0, if not it checks connected2, and so on. If by placing a new permutation from connected1 or more the number of wasted characters goes through the limit, it kills the goes back.

This are the basic structure and ideas that were used in newChaffinN6.c
