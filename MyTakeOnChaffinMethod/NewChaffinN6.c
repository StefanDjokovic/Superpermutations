/*THE OUTPUT WILL BE FIXED SOON
The new code asks at the beginning in which directory to place the output file.
Its format will be:
(wasted charactes) (max_perm)\n(the maximum permutation found)
*/

//Seems to be working well, but it still requires some improvements to be able to reach the final result
//will update the README soon

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
//used to build the indexing of the arrays
bool* arr;
int* upper;
short dong[3];
short dong2[4];
//given the index, the connected structure gives the lowest index of the permutation connected with it 
short connected[720][89]; 

short stopit;			//factval[N], the number of possible permutations at which the result is found
short stopitover;		//it's +N, the maximum number of characters generated with +1 wasted characters
int gotit;			//signals if a permutation of higher max_val was found


FILE * fp;

short curr_perm[2000];
short best_perm[2000];

//function that returns the factorial of the input value
int factorial(int k);

//function that gives the index of the input permutation
int getIndex(int* string);

//function that fills the strings in and checks their values
void fillStr0(short int pfound, short int permIndex, short int towaste);

//void getstring(short index, int start);

//void print();

//main body
int main() {

	N = 6;
	char enter;

	char filepos[300];
	printf("Please, specify file directory where max_perm will be place (example: C:\\Users\\...:\n");
	scanf("%149[^\n]%*c", filepos);

	fp = fopen(filepos, "w");
	if (fp == NULL) {
		printf("Error with opening the file\n");
		return -1;
	}


	printf("This tool will try to find the length of the shortest superpermutation of 6 symbols. Press enter to continue: ");
	scanf("%c", &enter);

	//initializes factval
	factval = (int*)malloc((N + 1) * sizeof(int));
	for (int i = 0; i <= N; i++) {
		factval[i] = factorial(i);
	}

	//allocating in memory the arrays needed
	upper = (int*)calloc(pow(N, N + 1), sizeof(int)); //a bit excessive, to improve

	checker = (bool*)malloc(sizeof(bool) * factval[N]);

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
		//0 waste: 0
		connected[i][0] = getIndex(&conn[1]);
		//1 waste: 1
		conn[N] = conn[1];
		conn[N + 1] = conn[0];
		connected[i][1] = getIndex(&conn[2]);
		//2 waste: 2 - 4
		conn[N + 1] = conn[2];
		conn[N + 2] = conn[0];
		connected[i][2] = getIndex(&conn[3]);
		conn[N] = conn[2];
		conn[N + 1] = conn[0];
		conn[N + 2] = conn[1];
		connected[i][3] = getIndex(&conn[3]);
		conn[N + 1] = conn[1];
		conn[N + 2] = conn[0];
		connected[i][4] = getIndex(&conn[3]);
		//3 waste: 5 - 17
		conn[N] = conn[1];
		conn[N + 1] = conn[2];
		conn[N + 2] = conn[3];
		conn[N + 3] = conn[0];
		connected[i][5] = getIndex(&conn[4]);
		conn[N + 1] = conn[3];
		conn[N + 2] = conn[0];
		conn[N + 3] = conn[2];
		connected[i][6] = getIndex(&conn[4]);
		conn[N + 2] = conn[2];
		conn[N + 3] = conn[0];
		connected[i][7] = getIndex(&conn[4]);

		conn[N] = conn[2];
		conn[N + 1] = conn[0];
		conn[N + 2] = conn[3];
		conn[N + 3] = conn[1];
		connected[i][8] = getIndex(&conn[4]);
		conn[N + 1] = conn[1];
		conn[N + 3] = conn[0];
		connected[i][9] = getIndex(&conn[4]);
		conn[N + 1] = conn[3];
		conn[N + 2] = conn[0];
		conn[N + 3] = conn[1];
		connected[i][10] = getIndex(&conn[4]);
		conn[N + 2] = conn[1];
		conn[N + 3] = conn[0];
		connected[i][11] = getIndex(&conn[4]);

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

		for (int j = 0; j < 6; j++) {
			connected[i][12 + j] = getIndex(&conn[4]) + j;
		}

		//4 waste: 18 - 88
		conn[N] = conn[1];
		conn[N + 1] = conn[2];
		conn[N + 2] = conn[3];
		conn[N + 3] = conn[4];
		conn[N + 4] = conn[0];
		connected[i][18] = getIndex(&conn[5]);
		conn[N + 2] = conn[4];
		conn[N + 3] = conn[0];
		conn[N + 4] = conn[3];
		connected[i][19] = getIndex(&conn[5]);
		conn[N + 3] = conn[3];
		conn[N + 4] = conn[0];
		connected[i][20] = getIndex(&conn[5]);
		conn[N + 1] = conn[3];
		conn[N + 2] = conn[0];
		conn[N + 3] = conn[4];
		conn[N + 4] = conn[2];
		connected[i][21] = getIndex(&conn[5]);
		conn[N + 2] = conn[2];
		conn[N + 4] = conn[0];
		connected[i][22] = getIndex(&conn[5]);
		conn[N + 1] = conn[3];
		conn[N + 2] = conn[4];
		conn[N + 3] = conn[0];
		conn[N + 4] = conn[2];
		connected[i][23] = getIndex(&conn[5]);
		conn[N + 3] = conn[2];
		conn[N + 4] = conn[0];
		connected[i][24] = getIndex(&conn[5]);
		conn[N + 1] = conn[4];

		conn[N + 2] = conn[0];
		conn[N + 3] = conn[2];
		conn[N + 4] = conn[3];
		connected[i][25] = getIndex(&conn[5]);
		conn[N + 3] = conn[3];
		conn[N + 4] = conn[2];
		connected[i][26] = getIndex(&conn[5]);
		conn[N + 2] = conn[2];
		conn[N + 3] = conn[0];
		conn[N + 4] = conn[3];
		connected[i][27] = getIndex(&conn[5]);
		conn[N + 3] = conn[3];
		conn[N + 4] = conn[0];
		connected[i][28] = getIndex(&conn[5]);
		conn[N + 2] = conn[3];
		conn[N + 3] = conn[0];
		conn[N + 4] = conn[2];
		connected[i][29] = getIndex(&conn[5]);
		conn[N + 3] = conn[2];
		conn[N + 4] = conn[0];
		connected[i][30] = getIndex(&conn[5]);

		conn[N] = conn[2];
		conn[N + 1] = conn[0];
		conn[N + 2] = conn[3];
		conn[N + 3] = conn[4];
		conn[N + 4] = conn[1];
		connected[i][31] = getIndex(&conn[5]);
		connected[i][32] = connected[i][31] + 1;
		connected[i][33] = connected[i][32] + 1;
		connected[i][34] = connected[i][33] + 4;
		connected[i][35] = connected[i][34] + 1;
		connected[i][36] = connected[i][35] + 1;
		connected[i][37] = connected[i][36] + 2;
		connected[i][38] = connected[i][37] + 2;
		for (int p = 1; p <= 8; p++)
			connected[i][38 + p] = connected[i][38] + p;
		connected[i][47] = connected[i][46] + 2;
		connected[i][48] = connected[i][47] + 2;
		connected[i][49] = connected[i][48] + 1;
		connected[i][50] = connected[i][49] + 1;
		connected[i][51] = connected[i][50] + 2;
		connected[i][52] = connected[i][51] + 2;
		connected[i][53] = connected[i][52] + 1;
		connected[i][54] = connected[i][53] + 1;
		connected[i][55] = connected[i][54] + 2;
		for (int p = 1; p <= 9; p++)
			connected[i][55 + p] = connected[i][55] + 1 + p;
		for (int p = 1; p <= 24; p++)
			connected[i][64 + p] = connected[i][64] + p;

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

		fprintf(fp, "%d %d\n", tot_bl, max_perm);
		//print();
		fprintf(fp, "\n");

		max_perm = max_perm + 4;	//to speed things up the hypotesis is that the new perm will be higher than the current+4

		if (max_perm >= factval[N]) {
			printf("\n-----\nDONE!\n-----\n\nMinimal superpermutations on %d symbols have %d wasted characters and a length of %d.\n", N, tot_bl, max_perm);
			break;
		}


	}

	getchar();
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
		int checked = 0;
		checker[permIndex] = 1;
		int pfound2 = pfound + 1;

		//Making unwasted characters
		if (checker[connected[permIndex][checked]] == 0)
			fillStr0(pfound2, connected[permIndex][checked], towaste);
		towaste--;
		checked = 1;
		if (towaste >= 0 && mperm_res[towaste] + pfound > max_perm) {
			if (checker[connected[permIndex][checked]] == 0)
				fillStr0(pfound2, connected[permIndex][checked], towaste);
			towaste--;
			if (towaste >= 0 && mperm_res[towaste] + pfound > max_perm) {
				checked = 2;
				if (checker[connected[permIndex][checked]] == 0)
					fillStr0(pfound2, connected[permIndex][checked], towaste);
				checked++;
				if (checker[connected[permIndex][checked]] == 0)
					fillStr0(pfound2, connected[permIndex][checked], towaste);
				checked++;
				if (checker[connected[permIndex][checked]] == 0)
					fillStr0(pfound2, connected[permIndex][checked], towaste);
				checked++;
				towaste--;
				if (towaste >= 0 && mperm_res[towaste] + pfound > max_perm) {
					for (checked = 5; checked < 18 && mperm_res[towaste] + pfound > max_perm; checked++) {
						if (checker[connected[permIndex][checked]] == 0)
							fillStr0(pfound2, connected[permIndex][checked], towaste);
					}
					towaste--;
					if (towaste >= 0) {
						for (checked = 18; checked < 89 && mperm_res[towaste] + pfound > max_perm; checked++) {
							if (checker[connected[permIndex][checked]] == 0)
								fillStr0(pfound2, connected[permIndex][checked], towaste);
						}
					}
				}
			}

		}
		checker[permIndex] = 0;
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

/*void getstring(short index, int start) {
	int step, k;
	int a;
	int resu[6];
	a = index / factval[N - 1];
	resu[0] = a + 1;
	long int upperValue;
	for (int s = 0; s < N; s++)
		arr[s] = 0;


	arr[a] = 1;
	upperValue = a;

	for (int j = 1; j < N; j++) {
		a = index % factval[N - j];
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
		resu[j] = k + 1;
	}
	for (int i = start; i < N; i++)
		fprintf(fp, "%d", resu[i]);
}

void print() {
	int wast = 0;
	getstring(best_perm[0], wast);
	for (int i = 1; i < max_perm; i++) {
		if (connected0[best_perm[i - 1]] == best_perm[i])
			wast = N - 1;
		else if (connected1[best_perm[i - 1]] == best_perm[i])
			wast = N - 2;
		else if (connected2[best_perm[i - 1]] == best_perm[i] || connected2[best_perm[i - 1]] + 1 == best_perm[i])
			wast = N - 3;
		else if (connected3[best_perm[i - 1]] >= best_perm[i] && connected3[best_perm[i - 1]] + 6 < best_perm[i])
			wast = N - 4;
		else if (connected4[best_perm[i - 1]] >= best_perm[i] && connected4[best_perm[i - 1]] + 24 < best_perm[i])
			wast = N - 5;
		else {
			//error message for debugging
			printf("ERROR!!! at %d, values are %d and %d\n", i, best_perm[i - 1], best_perm[i]);
			printf("connected2[best_perm[i - 1]]: %d %d\n", connected2[best_perm[i - 1]], connected2[best_perm[i - 1]] + 1);
			fprintf(fp, "ERROR HERE, PERMS ARE: ");
			getstring(best_perm[i - 1], 0);
			fprintf(fp, " AND ");
			getstring(best_perm[i], 0);
			return;
		}
		getstring(best_perm[i], wast);
	}
}*/
