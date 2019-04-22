//!!! I just noticed this version contains a bug when looking for the hashValue of connected4 !!!
//The result is correct, but just for pure casuality

//Still working on it, for now trying to improve for N = 5
//This code has improved the speed of the original Chaffin code by x4 for N = 5
//It works but there are many things to improve, uploading this just for reference
//The code has no comments, I will add them soon, and it needs to be reorganized
//Most of it works on the same base as the hashValue search

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int curstr[1000], max_perm, mperm_res[1000], N, tot_bl;
unsigned long int cur_perms[1000];

int factorial(int k);
bool *checker;
int *factval;
long int * upper;
int * power;
int * connected1;
int * connected2;
int * connected3;
int * connected4;
bool * arr;
unsigned long int tperm;
int stopit;

int getHashValue2(int * string) {
	long int val = 0;
	for (int i = 0; i < N; i++) {
		val = val * N + string[i];
	}
	val = upper[val];
	
	//printf("%d ", val);

	return val;
}

void max(int a, short int b, int pos) {
	if (b > a) {
		max_perm = b;
		/*printf("result: ");
		for (int i = 0; i < pos && max_perm < 40; i++)
			printf("%d", curstr[i]);
		printf(" .... ");*/
	}

}

int getSmallHash3(int * conn) {
	if (conn[0] < conn[1]) {
		if (conn[0] < conn[2]) {
			if (conn[1] < conn[2]) {
				return 0;
			}
			else {
				return 1;
			}

		}
		else {
			return 4;
		}
	}
	else {
		if (conn[1] < conn[2]) {
			if (conn[0] < conn[2]) {
				return 2;
			}
			else {
				return 3;
			}
		}
		else {
			return 5;
		}
	}
}


/*void fillStr2(short int pos, short int pfound, int hashValue, int waste);
void fillStr3(short int pos, short int pfound, int hashValue, int waste);*/


/*void fillStr1(short int pos, short int pfound, int hashValue, int waste) {
	for (int i = 0; i < N; i++) {
		if (curstr[pos - 1] != i) {
			curstr[pos] = i;

			if (curstr[pos] == curstr[pos - N]) {
				hashValue = getHashValue2(&curstr[pos - N + 1]);
				if (checker[hashValue] == 0) {
					checker[hashValue] = 1;
					fillStr1(pos + 1, pfound + 1, hashValue, waste);
					checker[hashValue] = 0;
				}	
			}
			else if (curstr[pos] == curstr[pos - N + 1]) {
				if (waste - 1 >= 0)
					fillStr2(pos + 1, pfound, hashValue, waste - 1);
			}
			else if (curstr[pos] == curstr[pos - N + 2]) {
				if (waste - 2 >= 0)
					fillStr3(pos + 1, pfound, hashValue, waste - 2);
			}
		}
	}
}*/

/*void fillStr2(short int pos, short int pfound, int hashValue, int waste) {
	int pos2 = pos + 1;
	curstr[pos] = curstr[pos - N - 1];
	hashValue = getHashValue2(&curstr[pos - N + 1]);
	if (checker[hashValue == 0]) {
		checker[hashValue] = 1;
		for (int i = 0; i < N; i++) {
			if (curstr[pos] != i) {
				curstr[pos2] = i;

				if (curstr[pos2] == curstr[pos2 - N]) {
					fillStr1(pos2 + 1, pfound + 1, hashValue, waste);
				}
				else if (curstr[pos2] == curstr[pos2 - N + 1]) {
					if (waste - 1 >= 0)
						fillStr2(pos2 + 1, pfound + 1, hashValue, waste - 1);
				}
				else if (curstr[pos] == curstr[pos - N + 2]) {
					if (waste - 2 >= 0)
						fillStr3(pos2 + 1, pfound + 1, hashValue, waste - 2);
				}
			}
		}
		checker[hashValue] = 0;
	}
}
*/
/*void fillStr3(short int pos, short int pfound, int hashValue, int waste) {
	int pos3 = pos + 2;
	curstr[pos] = curstr[pos - N - 1];
	curstr[pos + 1] = curstr[pos - N];
	hashValue = getHashValue2(&curstr[pos - N + 2]);
	if (checker[hashValue] == 0) {
		checker[hashValue] = 1;
		for (int i = 0; i < N; i++) {
			if (curstr[pos + 1] != i) {
				curstr[pos3] = i;

				if (curstr[pos3] == curstr[pos3 - N]) {
					fillStr1(pos3 + 1, pfound + 1, hashValue, waste);
				}
				else if (curstr[pos3] == curstr[pos3 - N + 1]) {
					if (waste - 1 >= 0)
						fillStr2(pos3 + 1, pfound + 1, hashValue, waste - 1);
					else
						max(max_perm, pfound + 1);
				}
				else if (curstr[pos] == curstr[pos - N + 2]) {
					if (waste - 2 >= 0)
						fillStr3(pos3 + 1, pfound + 1, hashValue, waste - 2);
					else
						max(max_perm, pfound + 1);
				}
			}
		}

		checker[hashValue] = 0;
	}

	curstr[pos] = curstr[pos - N];
	curstr[pos + 1] = curstr[pos - N - 1];
	hashValue = getHashValue2(&curstr[pos - N + 2]);
	if (checker[hashValue] == 0) {
		checker[hashValue] = 1;
		for (int i = 0; i < N; i++) {
			if (curstr[pos + 1] != i) {
				curstr[pos3] = i;

				if (curstr[pos3] == curstr[pos3 - N]) {
					fillStr1(pos3 + 1, pfound + 1, hashValue, waste);
				}
				else if (curstr[pos3] == curstr[pos3 - N + 1]) {
					if (waste - 1 >= 0)
						fillStr2(pos3 + 1, pfound + 1, hashValue, waste - 1);
					else
						max(max_perm, pfound + 1);
				}
				else if (curstr[pos] == curstr[pos - N + 2]) {
					if (waste - 2 >= 0)
						fillStr3(pos3 + 1, pfound + 1, hashValue, waste - 2);
					else
						max(max_perm, pfound + 1);
				}
			}
		}
		checker[hashValue] = 0;
	}
}*/

//this is the starting fillStr call
void fillStr0(short int pos, short int pfound, int hashValue, int waste) {
	max(max_perm, pfound, pos);
	if ((waste == tot_bl || (mperm_res[waste] + pfound > max_perm && mperm_res[waste] + pfound > mperm_res[tot_bl - 1] + 2) && stopit)) {
		int minihash = hashValue;	
		for (int i = 0; i < N; i++) {
			if (i != curstr[pos - 1]) {
				curstr[pos] = i;
	
				if (curstr[pos] == curstr[pos - N]) {
					hashValue = connected1[minihash];
					//printf("%d ", hashValue);
					//hashValue = getHashValue2(&curstr[pos - N + 1]);
					
					if (checker[hashValue] == 0) {
						checker[hashValue] = 1;
						fillStr0(pos + 1, pfound+1, hashValue, waste);
						checker[hashValue] = 0;
					}				
				}
				else if (curstr[pos] == curstr[pos - N + 1]) {
					if (waste - 1 >= 0) {
						curstr[pos + 1] = curstr[pos - N];
						hashValue = connected2[minihash];
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 2, pfound + 1, hashValue, waste - 1);
							checker[hashValue] = 0;
						}
					}			
				}
				else if (curstr[pos] == curstr[pos - N + 2]) {
					if (waste - 2 >= 0) {
						curstr[pos + 1] = curstr[pos - N];
						curstr[pos + 2] = curstr[pos - N + 1];
						if (curstr[pos - N] < curstr[pos - N + 1]) {
							hashValue = connected3[minihash];
						}
						else
							hashValue = connected3[minihash] + 1;
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 3, pfound + 1, hashValue, waste - 2);
							checker[hashValue] = 0;
						}

						curstr[pos + 1] = curstr[pos - N + 1];
						curstr[pos + 2] = curstr[pos - N];
						if (curstr[pos - N + 1] < curstr[pos - N]) {
							hashValue = connected3[minihash];
						}
						else
							hashValue = connected3[minihash] + 1;
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 3, pfound + 1, hashValue, waste - 2);
							checker[hashValue] = 0;
						}
					}

				}
				else if (curstr[pos] == curstr[pos - N + 3]) {
					if (waste - 3 >= 0) {
						curstr[pos + 1] = curstr[pos - N];
						curstr[pos + 2] = curstr[pos - N + 1];
						curstr[pos + 3] = curstr[pos - N + 2];
						hashValue = connected4[minihash] + getSmallHash3(&curstr[pos + 1]);
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 4, pfound + 1, hashValue, waste - 3);
							checker[hashValue] = 0;
						}
						curstr[pos + 1] = curstr[pos - N];
						curstr[pos + 2] = curstr[pos - N + 2];
						curstr[pos + 3] = curstr[pos - N + 1];
						hashValue = connected4[minihash] + getSmallHash3(&curstr[pos + 1]);
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 4, pfound + 1, hashValue, waste - 3);
							checker[hashValue] = 0;
						}
						curstr[pos + 1] = curstr[pos - N + 1];
						curstr[pos + 2] = curstr[pos - N];
						curstr[pos + 3] = curstr[pos - N + 2];
						hashValue = connected4[minihash] + getSmallHash3(&curstr[pos + 1]);
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 4, pfound + 1, hashValue, waste - 3);
							checker[hashValue] = 0;
						}
						curstr[pos + 1] = curstr[pos - N + 1];
						curstr[pos + 2] = curstr[pos - N + 2];
						curstr[pos + 3] = curstr[pos - N];
						hashValue = connected4[minihash] + getSmallHash3(&curstr[pos + 1]);
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 4, pfound + 1, hashValue, waste - 3);
							checker[hashValue] = 0;
						}
						curstr[pos + 1] = curstr[pos - N + 2];
						curstr[pos + 2] = curstr[pos - N];
						curstr[pos + 3] = curstr[pos - N + 1];
						hashValue = connected4[minihash] + getSmallHash3(&curstr[pos + 1]);
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 4, pfound + 1, hashValue, waste - 3);
							checker[hashValue] = 0;
						}
						curstr[pos + 1] = curstr[pos - N + 2];
						curstr[pos + 2] = curstr[pos - N + 1];
						curstr[pos + 3] = curstr[pos - N];
						hashValue = connected4[minihash] + getSmallHash3(&curstr[pos + 1]);
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 4, pfound + 1, hashValue, waste - 3);
							checker[hashValue] = 0;
						}
					}
				}
			}
		}
	}

}

void fillStrQ(short int pos, short int pfound, int hashValue, int waste) {
		int minihash = hashValue;
		max(max_perm, pfound, pos);
		for (int i = 0; i < N; i++) {
			if (i != curstr[pos - 1]) {
				curstr[pos] = i;

				if (curstr[pos] == curstr[pos - N]) {
					hashValue = connected1[minihash];
					//printf("%d ", hashValue);
					//hashValue = getHashValue2(&curstr[pos - N + 1]);

					if (checker[hashValue] == 0) {
						checker[hashValue] = 1;
						fillStr0(pos + 1, pfound + 1, hashValue, waste);
						checker[hashValue] = 0;
					}
				}
				else if (curstr[pos] == curstr[pos - N + 1]) {
					if (waste - 1 >= 0) {
						curstr[pos + 1] = curstr[pos - N];
						hashValue = connected2[minihash];
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 2, pfound + 1, hashValue, waste - 1);
							checker[hashValue] = 0;
						}
					}
				}
				else if (curstr[pos] == curstr[pos - N + 2]) {
					if (waste - 2 >= 0) {
						curstr[pos + 1] = curstr[pos - N];
						curstr[pos + 2] = curstr[pos - N + 1];
						if (curstr[pos - N] < curstr[pos - N + 1]) {
							hashValue = connected3[minihash];
						}
						else 
							hashValue = connected3[minihash] + 1; 
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 3, pfound + 1, hashValue, waste - 2);
							checker[hashValue] = 0;
						}

						curstr[pos + 1] = curstr[pos - N + 1];
						curstr[pos + 2] = curstr[pos - N];
						if (curstr[pos - N] < curstr[pos - N + 1]) {
							hashValue = connected3[minihash];
						}
						else
							hashValue = connected3[minihash] + 1;
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 3, pfound + 1, hashValue, waste - 2);
							checker[hashValue] = 0;
						}
					}

				}
				else if (curstr[pos] == curstr[pos - N + 3]) {
					if (waste - 3 >= 0) {
						curstr[pos + 1] = curstr[pos - N];
						curstr[pos + 2] = curstr[pos - N + 1];
						curstr[pos + 3] = curstr[pos - N + 2];
						hashValue = connected4[minihash] + getSmallHash3(&curstr[pos + 1]);
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 4, pfound + 1, hashValue, waste - 3);
							checker[hashValue] = 0;
						}
						curstr[pos + 1] = curstr[pos - N];
						curstr[pos + 2] = curstr[pos - N + 2];
						curstr[pos + 3] = curstr[pos - N + 1];
						hashValue = connected4[minihash] + getSmallHash3(&curstr[pos + 1]);
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 4, pfound + 1, hashValue, waste - 3);
							checker[hashValue] = 0;
						}
						curstr[pos + 1] = curstr[pos - N + 1];
						curstr[pos + 2] = curstr[pos - N];
						curstr[pos + 3] = curstr[pos - N + 2];
						hashValue = connected4[minihash] + getSmallHash3(&curstr[pos + 1]);
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 4, pfound + 1, hashValue, waste - 3);
							checker[hashValue] = 0;
						}
						curstr[pos + 1] = curstr[pos - N + 1];
						curstr[pos + 2] = curstr[pos - N + 2];
						curstr[pos + 3] = curstr[pos - N];
						hashValue = connected4[minihash] + getSmallHash3(&curstr[pos + 1]);
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 4, pfound + 1, hashValue, waste - 3);
							checker[hashValue] = 0;
						}
						curstr[pos + 1] = curstr[pos - N + 2];
						curstr[pos + 2] = curstr[pos - N];
						curstr[pos + 3] = curstr[pos - N + 1];
						hashValue = connected4[minihash] + getSmallHash3(&curstr[pos + 1]);
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 4, pfound + 1, hashValue, waste - 3);
							checker[hashValue] = 0;
						}
						curstr[pos + 1] = curstr[pos - N + 2];
						curstr[pos + 2] = curstr[pos - N + 1];
						curstr[pos + 3] = curstr[pos - N];
						hashValue = connected4[minihash] + getSmallHash3(&curstr[pos + 1]);
						if (checker[hashValue] == 0) {
							checker[hashValue] = 1;
							fillStr0(pos + 4, pfound + 1, hashValue, waste - 3);
							checker[hashValue] = 0;
						}
					}
				}
			}
		}

}


int main()
{
	unsigned short int j0;

	printf("This tool will try to find the length of the shortest superpermutation on n symbols. Please enter n: ");
	scanf("%d", &N);

	mperm_res[0] = N;

	///MY PART OF THE CODE
	//contains factorial values from 0! to N!
	factval = (int*)malloc((N + 1) * sizeof(int));
	for (int i = 0; i <= N; i++) {
		factval[i] = factorial(i);
	}

	stopit = factval[N];

	upper = (long int*)calloc(pow(N, N + 2), sizeof(long int)); //a bit excessive, to improve
	power = (int*)malloc(sizeof(int) * (N * 2 + 1));
	connected1 = (int*)malloc(sizeof(int) * factorial(N));
	connected2 = (int*)malloc(sizeof(int) * factorial(N));
	connected3 = (int*)malloc(sizeof(int) * factorial(N));
	connected4 = (int*)malloc(sizeof(int) * factorial(N));

	for (int i = 0; i < factorial(N); i++) {
		connected1[i] = 0;
		connected2[i] = 0;
		connected3[i] = 0;
		connected4[i] = 0;
	}

	//contains power values of 6 from 0 to N*2
	for (int i = 0; i <= N * 2; i++) {
		power[i] = pow(N, i);
	}

	arr = (bool*)malloc(N * sizeof(bool));
	for (int s = 0; s < N; s++)
		arr[s] = 0;

	int a;
	int step;
	int k;

	//connecting first order connections to hash values
	for (int i = 0; i < factorial(N); i++) {
		long int upperValue = 0;
		for (int s = 0; s < N; s++)
			arr[s] = 0;

		a = i / factorial(N - 1);
		arr[a] = 1;
		upperValue = a;

		for (int j = 1; j < N; j++) {
			a = i % factorial(N - j);
			step = a / factorial(N - (j + 1));

			k = 0;
			while (arr[k] == 1)
				k++;
			while (step != 0) {
				if (arr[k] != 1)
					step--;
				k++;
				while (arr[k] == 1)
					k++;
			}
			arr[k] = 1;
			upperValue = upperValue * N + k;

		}
		upper[upperValue] = i;

	}

	//generationg connected1 and connected2
	int * conn = (int*)malloc(sizeof(int) * (N + 2));
	for (int i = 0; i < factorial(N); i++) {
		for (int s = 0; s < N; s++)
			arr[s] = 0;

		a = i / factorial(N - 1);
		arr[a] = 1;
		conn[0] = a;
		conn[N] = a;
		for (int j = 1; j < N; j++) {
			a = i % factorial(N - j);
			step = a / factorial(N - (j + 1));

			k = 0;
			while (arr[k] == 1)
				k++;
			while (step != 0) {
				if (arr[k] != 1)
					step--;
				k++;
				while (arr[k] == 1)
					k++;
			}
			arr[k] = 1;
			conn[j] = k;
		}
		connected1[i] = getHashValue2(&conn[1]);
		conn[N] = conn[1];
		conn[N + 1] = conn[0];
		connected2[i] = getHashValue2(&conn[2]);
		conn[N] = conn[2];
		if (conn[0] < conn[1]) {
			conn[N + 1] = conn[0];
			conn[N + 2] = conn[1];
		}
		else {
			conn[N + 1] = conn[1];
			conn[N + 2] = conn[0];
		}
		connected3[i] = getHashValue2(&conn[3]);

		conn[N] = conn[3];
		if (conn[0] < conn[1]) {
			if (conn[0] < conn[2]) {
				conn[N + 1] = conn[0];
				if (conn[1] < conn[2]) {
					conn[N + 2] = conn[1];
					conn[N + 3] = conn[2];
				}
				else {
					conn[N + 2] = conn[2];
					conn[N + 3] = conn[1];
				}

			}
			else {
				conn[N + 1] = conn[2];
				conn[N + 2] = conn[0];
				conn[N + 3] = conn[1];
			}
		}
		else {
			if (conn[1] < conn[2]) {
				conn[N + 1] = conn[1];
				if (conn[0] < conn[2]) {
					conn[N + 2] = conn[0];
					conn[N + 3] = conn[2];
				}
				else {
					conn[N + 2] = conn[2];
					conn[N + 3] = conn[0];
				}
			}
			else {
				conn[N + 1] = conn[2];
				conn[N + 2] = conn[1];
				conn[N + 3] = conn[0];
			}
		}
		connected4[i] = getHashValue2(&conn[4]);
	}

	checker = (bool*)malloc(sizeof(bool) * factval[N]); //RICORDATI DI AZZERARLO!
	///END OF GENERATING CONNECTIONS ETC


	printf("Thanks for choosing N: %d, let's start!\n", N);

	for (tot_bl = 1; tot_bl <= 1000; tot_bl++) {
		max_perm = 1;

		for (int i = 0; i < factval[N]; i++) ///THE NEW CLEARPERMS
			checker[i] = 0;

		for (j0 = 0; j0 < N; j0++) {
			curstr[j0] = j0;
		}
		checker[0] = 1;

		fillStrQ(N, 1, 0, tot_bl);
		mperm_res[tot_bl] = max_perm;

		printf("%d wasted characters: at most %d permutations, N is at %d\n", tot_bl, max_perm, N);

		if (max_perm >= factval[N]) {
			printf("\n-----\nDONE!\n-----\n\nMinimal superpermutations on %d symbols have %d wasted characters and a length of %d.\n", N, tot_bl, max_perm);
			break;
		}
	}

	getchar();
	return 0;
}

// this function computes the factorial of a number
int factorial(int val) {
	int res = 1;
	for (int i = 1; i <= val; i++) {
		res = res * i;
	}
	return res;
}
