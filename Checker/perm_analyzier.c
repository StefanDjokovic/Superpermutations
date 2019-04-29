//This tool can be used only for permutations of 6 different characters for now
//It can be used to see how many wasted characters a permutation has,
//how many characters it is made of, and how many different permutations it contains

//Note: the maximum number of wasted characters must be of N-1 (so at least the last
//character and the first of the successor must be the same. Also the permutations should 
//be made of digits starting from 1

//The permutation is insered with standard input, and the result is output through standard output

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

short max_perm;			//keeps the maximum permutation value
short mperm_res[1000];	//keeps all the maximum permutation values for each wasted character
short tot_bl;			//wasted character

short N;				//N = 6 in this version, it's the number of different characters

bool* checker;			//this array is used to keep the permutation used 
bool* newchecker;
int* factval;			//array with the useful factorials			
int* power;				//array with the useful powers of N
//used to build the indexing of the arrays
bool* arr;
int* upper;
short dong[3];
short dong2[4];
//given the index, the connected structure gives the lowest index of the permutation connected with it 
short* connected0;		//0 wasted characters
short* connected1;		//1 wasted characters
short* connected2;		//2 wasted characters
short* connected3;		//3 wasted characters
short* connected4;		//4 wasted characters
short stopit;			//factval[N], the number of possible permutations at which the result is found
short stopitover;		//it's +N, the maximum number of characters generated with +1 wasted characters
int gotit;				//signals if a permutation of higher max_val was found

short curr_perm[2000];
short best_perm[2000];

int allin[6];

//function that returns the factorial of the input value
int factorial(int k);

//function that gives the index of the input permutation
int getIndex(int* string);
//same as getIndex + checks for unrepeated characters
int getIndex2(int* string); 

//function that fills the strings in and checks their values
void fillStr0(short int pfound, short int permIndex, short int towaste);

//main body
int main() {

	N = 6;
	char enter;

	//initializes factval
	factval = (int*)malloc((N + 1) * sizeof(int));
	for (int i = 0; i <= N; i++) {
		factval[i] = factorial(i);
	}

	//allocating in memory the arrays needed
	upper = (int*)calloc(pow(N, N + 1), sizeof(int)); //a bit excessive, to improve
	power = (int*)malloc(sizeof(int) * (N * 2 + 1));
	connected0 = (short*)malloc(sizeof(short) * factval[N]);
	connected1 = (short*)malloc(sizeof(short) * factval[N]);
	connected2 = (short*)malloc(sizeof(short) * factval[N]);
	connected3 = (short*)malloc(sizeof(short) * factval[N]);
	connected4 = (short*)malloc(sizeof(short) * factval[N]);

	checker = (bool*)malloc(sizeof(bool) * factval[N]);
	newchecker = (bool*)malloc(sizeof(bool) * factval[N]);

	//zeroing, just a safety measure, could have used calloc insted
	for (int i = 0; i < factorial(N); i++) {
		connected0[i] = 0;
		connected1[i] = 0;
		connected2[i] = 0;
		connected3[i] = 0;
		connected4[i] = 0;
		checker[i] = 0;
		newchecker[i] = 0;
	}

	//initializing power
	for (int i = 0; i <= N * 2; i++) {
		power[i] = pow(N, i);
	}
	//initializing arr
	arr = (bool*)malloc(N * sizeof(bool));
	for (int s = 0; s < N; s++)
		arr[s] = 0;
	//some variables required to make the indexing work, check README on how this works
	int a;
	int step;
	int k;

	//generating indexing
	for (int i = 0; i < factorial(N); i++) {
		long int upperValue = 0;
		for (int s = 0; s < N; s++)
			arr[s] = 0;

		a = i / factval[N - 1];
		arr[a] = 1;
		upperValue = a;

		for (int j = 1; j < N; j++) {
			a = i % factval[N - j];
			step = a / factval[N - (j + 1)];

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

	//generationg all connected arrays
	int* conn = (int*)malloc(sizeof(int) * (N + N));
	for (int i = 0; i < factval[N]; i++) {
		for (int s = 0; s < N; s++)
			arr[s] = 0;

		a = i / factval[N - 1];
		arr[a] = 1;
		conn[0] = a;
		conn[N] = a;
		for (int j = 1; j < N; j++) {
			a = i % factval[N - j];
			step = a / factval[N - (j + 1)];

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
		connected0[i] = getIndex(&conn[1]);
		conn[N] = conn[1];
		conn[N + 1] = conn[0];
		connected1[i] = getIndex(&conn[2]);
		conn[N] = conn[2];
		if (conn[0] < conn[1]) {
			conn[N + 1] = conn[0];
			conn[N + 2] = conn[1];
		}
		else {
			conn[N + 1] = conn[1];
			conn[N + 2] = conn[0];
		}
		connected2[i] = getIndex(&conn[3]);

		//building connected3
		conn[N] = conn[3];
		for (int k = 0; k < 3; k++)
			dong2[k] = conn[k];
		int kk;
		for (int k = 1; k < 3; k++)
			for (int j = k; j > 0 && dong2[j - 1] > dong2[j]; j--) {
				kk = dong2[j];
				dong2[j] = dong2[j - 1];
				dong2[j - 1] = kk;
			}
		for (int k = 0; k < 3; k++)
			conn[k + 1 + N] = dong2[k];
		connected3[i] = getIndex(&conn[4]);

		//building connected4
		conn[N] = conn[4];
		for (int k = 0; k < 4; k++)
			dong2[k] = conn[k];
		for (int k = 1; k < 4; k++)
			for (int j = k; j > 0 && dong2[j - 1] > dong2[j]; j--) {
				kk = dong2[j];
				dong2[j] = dong2[j - 1];
				dong2[j - 1] = kk;
			}
		for (int k = 0; k < 4; k++)
			conn[k + 1 + N] = dong2[k];
		connected4[i] = getIndex(&conn[5]);

	}

	printf("Insert the starting permutation: ");
	while (1) {
		int scan = 0;
		int s_perm[1000];
		for (int i = 0; i < factval[N]; i++)
			newchecker[i] = 0;

		int length = 0;

		scanf("%c", &scan);
		for (length = 0; scan != '\n'; length++) {
			s_perm[length] = scan - '1';	//Converting all to start from 0
			scanf("%c", &scan);
		}
		int check;
		int wasted = 0;

		for (int i = 0; i <= length - N; i++) {
			check = getIndex2(&s_perm[i]);
			if (check != -1 && newchecker[check] == 0) {
				newchecker[getIndex2(&s_perm[i])] = 1;
			}
			else
				wasted++;
		}

		printf("length = %d ; wasted = %d ; pfound = %d\n", length, wasted, length - wasted - N + 1);
	}

	return 0;
}


//function that fills the strings in and checks their values
void fillStr0(short int pfound, short int permIndex, short int towaste) {
	curr_perm[pfound - 1] = permIndex;
	if (pfound > max_perm) {
		max_perm = pfound;
		gotit = 1;
		for (int i = 0; i < max_perm; i++)
			best_perm[i] = curr_perm[i];
	}

	if (max_perm < stopit && max_perm < stopitover) {
		int tempIndex = permIndex;
		checker[tempIndex] = 1;
		int pfound2 = pfound + 1;

		//Making unwasted characters
		if (checker[connected0[tempIndex]] == 0)
			fillStr0(pfound2, connected0[tempIndex], towaste);
		towaste--;
		if (towaste >= 0 && mperm_res[towaste] + pfound > max_perm) {
			if (checker[connected1[tempIndex]] == 0)
				fillStr0(pfound2, connected1[tempIndex], towaste);
			towaste--;
			if (towaste >= 0 && mperm_res[towaste] + pfound > max_perm) {
				permIndex = connected2[tempIndex];
				if (checker[permIndex] == 0)
					fillStr0(pfound2, permIndex, towaste);
				permIndex++;
				if (checker[permIndex] == 0)
					fillStr0(pfound2, permIndex, towaste);
				towaste--;
				if (towaste >= 0 && mperm_res[towaste] + pfound > max_perm) {
					permIndex = connected3[tempIndex];
					int aa;
					for (aa = 0; aa < 6 && mperm_res[towaste] + pfound > max_perm; aa++) {
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
					}
					towaste--;
					if (towaste >= 0) {
						permIndex = connected4[tempIndex];
						for (aa = 0; aa < 24 && mperm_res[towaste] + pfound > max_perm; aa++) {
							if (checker[permIndex] == 0)
								fillStr0(pfound2, permIndex, towaste);
							permIndex++;
						}
					}
				}
			}

		}
		checker[tempIndex] = 0;
	}
}

//function that gives the index of the input permutation
int getIndex(int* string) {
	long int val = 0;
	for (int i = 0; i < N; i++) {
		val = val * N + string[i];
	}
	val = upper[val];

	return val;
}

int getIndex2(int* string) {
	long int val = 0;
	for (int i = 0; i < N; i++)
		allin[i] = 0;
	for (int i = 0; i < N; i++) {
		if (allin[string[i]] == 1)
			return -1;
		else
			allin[string[i]] = 1;
	}

	for (int i = 0; i < N; i++) {
		val = val * N + string[i];
	}
	val = upper[val];

	return val;
}

// this function computes the factorial of a number
int factorial(int val) {
	int res = 1;
	for (int i = 1; i <= val; i++) {
		res = res * i;
	}
	return res;
}
