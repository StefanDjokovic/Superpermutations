//This code uses the following assumptions to run as fast as possible (Still not speedy enough to reach the final result in a valuable time):
//1) In the shortest superpermutation a permutation appears only once; it's considered to be true, but there is no
//proof yet
//2) The maximum number of new permutation after adding a new wasted character will be equals or less than 6. The discussion
//is still going on, but it's thought to be true.

//Seems to be working well, but it still requires some improvements to be able to reach the final result
//Also this version doesn't print the partial results, will add that soon

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

//function that returns the factorial of the input value
int factorial(int k);

//function that gives the index of the input permutation
int getIndex(int* string);

//function that fills the strings in and checks their values
void fillStr0(short int pfound, short int permIndex, short int towaste);

//main body
int main() {

	N = 6;
	char enter;

	printf("This tool will try to find the length of the shortest superpermutation of 6 symbols. Press enter to continue: ");
	scanf("%c", &enter);

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

	//zeroing, just a safety measure, could have used calloc insted
	for (int i = 0; i < factorial(N); i++) {
		connected0[i] = 0;
		connected1[i] = 0;
		connected2[i] = 0;
		connected3[i] = 0;
		connected4[i] = 0;
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

	//generationg all connected arrays, how it works (Soon) in readme
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
		connected3[i] = getIndex(&conn[4]);

		conn[N] = conn[4];
		for (int k = 0; k < 4; k++)
			dong2[k] = conn[k];
		int kk;
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
	
	stopit = factval[N];
	
	//Starting values
	mperm_res[0] = N;
	max_perm = N;


	for (tot_bl = 1; tot_bl <= 250; tot_bl++) {
		gotit = 0;
		stopitover = mperm_res[tot_bl - 1] + N;
		for (int i = 0; i < factval[N]; i++) {
			checker[i] = 0;
		}

		checker[0] = 1;

		fillStr0(1, 0, tot_bl);
		//if fillStr didn't find a new permutation, or it's not the end try with a lower number of max_perm
		if (gotit == 0 && max_perm != factval[N]) {
			max_perm--;
			for (int i = 0; i < factval[N]; i++) {
				checker[i] = 0;
			}
			checker[0] = 1;
			fillStr0(1, 0, tot_bl);

			if (gotit == 0 && max_perm != factval[N]) {
				max_perm--;
				for (int i = 0; i < factval[N]; i++) {
					checker[i] = 0;
				}
				checker[0] = 1;
				fillStr0(1, 0, tot_bl);

				if (gotit == 0 && max_perm != factval[N]) {
					max_perm--;
					for (int i = 0; i < factval[N]; i++) {
						checker[i] = 0;
					}
					checker[0] = 1;
					fillStr0(1, 0, tot_bl);
				}
			}
		}
		mperm_res[tot_bl] = max_perm;

		printf("%d wasted characters: at most %d permutations\n", tot_bl, max_perm);

		max_perm = max_perm + 4;	//to speed things up the hypotesis is that the new perm will be higher than the current+4

		if (max_perm >= factval[N]) {
			printf("\n-----\nDONE!\n-----\n\nMinimal superpermutations on %d symbols have %d wasted characters and a length of %d.\n", N, tot_bl, max_perm);
			break;
		}


	}

	getchar();
	return 0;
}


void fillStr0(short int pfound, short int permIndex, short int towaste) {
	if (pfound > max_perm) {
		max_perm = pfound;
		gotit = 1;
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
					if (checker[permIndex] == 0)
						fillStr0(pfound2, permIndex, towaste);
					permIndex++;
					if (checker[permIndex] == 0)
						fillStr0(pfound2, permIndex, towaste);
					permIndex++;
					if (checker[permIndex] == 0)
						fillStr0(pfound2, permIndex, towaste);
					permIndex++;
					if (checker[permIndex] == 0)
						fillStr0(pfound2, permIndex, towaste);
					permIndex++;
					if (checker[permIndex] == 0)
						fillStr0(pfound2, permIndex, towaste);
					permIndex++;
					if (checker[permIndex] == 0)
						fillStr0(pfound2, permIndex, towaste);

					towaste--;
					if (towaste >= 0 && mperm_res[towaste] + pfound > max_perm) {
						permIndex = connected4[tempIndex];
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
						permIndex++;
						if (checker[permIndex] == 0)
							fillStr0(pfound2, permIndex, towaste);
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

// this function computes the factorial of a number
int factorial(int val) {
	int res = 1;
	for (int i = 1; i <= val; i++) {
		res = res * i;
	}
	return res;
}
