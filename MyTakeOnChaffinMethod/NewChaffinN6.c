//The objective of this code is to find the smallest superpermutation possible of 6 different characters,
//and prove that it's the smallest superpermutation possible

/*This program is based on the Chaffin Method, its description
and the original code can be found here:
http://www.njohnston.ca/2014/08/all-minimal-superpermutations-on-five-symbols-have-been-found/

My approach is slightly different: instead of looking character per character, I do the
search by looking the possible permutation that can be added
The code also assumes that no connectetion of wasted characters = 6 or more is beneficial
to the formation of the minimal superpermutation (conjecture still to be formally proven)
*/

/*The program asks at the beginning in which directory to place the output file.
Output file's format will be:
(wasted charactes) (max_perm)\n(the maximum permutation found)\n
*/


//It works well, but it still requires some improvements to be able to reach the final result

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
short dong3[5];
//given the index, the connected matrix gives the lowest index of the permutation connected with it 
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

void getstring(short index, int start);

void print();

//main body
int main() {

	N = 6;
	char enter;

	char filepos[300];
	printf("Please, specify file directory where max_perm will be place (example: C:\\Users\\...:\n");
	scanf("%149[^\n]%*c", filepos);
	char attach[] = "\\output.txt";
	strcat(filepos, attach);

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
		conn[N + 1] = conn[0];
		conn[N + 2] = conn[4];
		conn[N + 3] = conn[1];
		conn[N + 4] = conn[3];
		connected[i][32] = getIndex(&conn[5]);
		conn[N + 1] = conn[0];
		conn[N + 2] = conn[4];
		conn[N + 3] = conn[3];
		conn[N + 4] = conn[1];
		connected[i][33] = getIndex(&conn[5]);
		conn[N + 1] = conn[1];
		conn[N + 2] = conn[3];
		conn[N + 3] = conn[4];
		conn[N + 4] = conn[0];
		connected[i][34] = getIndex(&conn[5]);
		conn[N + 1] = conn[1];
		conn[N + 2] = conn[4];
		conn[N + 3] = conn[0];
		conn[N + 4] = conn[3];
		connected[i][35] = getIndex(&conn[5]);
		conn[N + 1] = conn[1];
		conn[N + 2] = conn[4];
		conn[N + 3] = conn[3];
		conn[N + 4] = conn[0];
		connected[i][36] = getIndex(&conn[5]);
		conn[N + 1] = conn[3];
		conn[N + 2] = conn[0];
		conn[N + 3] = conn[4];
		conn[N + 4] = conn[1];
		connected[i][37] = getIndex(&conn[5]);
		conn[N + 1] = conn[3];
		conn[N + 2] = conn[1];
		conn[N + 3] = conn[4];
		conn[N + 4] = conn[0];
		connected[i][38] = getIndex(&conn[5]);
		conn[N + 1] = conn[3];
		conn[N + 2] = conn[4];
		conn[N + 3] = conn[0];
		conn[N + 4] = conn[1];
		connected[i][39] = getIndex(&conn[5]);
		conn[N + 1] = conn[3];
		conn[N + 2] = conn[4];
		conn[N + 3] = conn[1];
		conn[N + 4] = conn[0];
		connected[i][40] = getIndex(&conn[5]);
		conn[N + 1] = conn[4];
		conn[N + 2] = conn[0];
		conn[N + 3] = conn[1];
		conn[N + 4] = conn[3];
		connected[i][41] = getIndex(&conn[5]);
		conn[N + 1] = conn[4];
		conn[N + 2] = conn[0];
		conn[N + 3] = conn[3];
		conn[N + 4] = conn[1];
		connected[i][42] = getIndex(&conn[5]);
		conn[N + 1] = conn[4];
		conn[N + 2] = conn[1];
		conn[N + 3] = conn[0];
		conn[N + 4] = conn[3];
		connected[i][43] = getIndex(&conn[5]);
		conn[N + 1] = conn[4];
		conn[N + 2] = conn[1];
		conn[N + 3] = conn[3];
		conn[N + 4] = conn[0];
		connected[i][44] = getIndex(&conn[5]);
		conn[N + 1] = conn[4];
		conn[N + 2] = conn[3];
		conn[N + 3] = conn[0];
		conn[N + 4] = conn[1];
		connected[i][45] = getIndex(&conn[5]);
		conn[N + 1] = conn[4];
		conn[N + 2] = conn[3];
		conn[N + 3] = conn[1];
		conn[N + 4] = conn[0];
		connected[i][46] = getIndex(&conn[5]);

		conn[N] = conn[3];
		conn[N + 1] = conn[0];
		conn[N + 2] = conn[1];
		conn[N + 3] = conn[4];
		conn[N + 4] = conn[2];
		connected[i][47] = getIndex(&conn[5]);
		conn[N + 1] = conn[0];
		conn[N + 2] = conn[2];
		conn[N + 3] = conn[4];
		conn[N + 4] = conn[1];
		connected[i][48] = getIndex(&conn[5]);
		conn[N + 1] = conn[0];
		conn[N + 2] = conn[4];
		conn[N + 3] = conn[1];
		conn[N + 4] = conn[2];
		connected[i][49] = getIndex(&conn[5]);
		conn[N + 1] = conn[0];
		conn[N + 2] = conn[4];
		conn[N + 3] = conn[2];
		conn[N + 4] = conn[1];
		connected[i][50] = getIndex(&conn[5]);
		conn[N + 1] = conn[1];
		conn[N + 2] = conn[0];
		conn[N + 3] = conn[4];
		conn[N + 4] = conn[2];
		connected[i][51] = getIndex(&conn[5]);
		conn[N + 1] = conn[1];
		conn[N + 2] = conn[2];
		conn[N + 3] = conn[4];
		conn[N + 4] = conn[0];
		connected[i][52] = getIndex(&conn[5]);
		conn[N + 1] = conn[1];
		conn[N + 2] = conn[4];
		conn[N + 3] = conn[0];
		conn[N + 4] = conn[2];
		connected[i][53] = getIndex(&conn[5]);
		conn[N + 1] = conn[1];
		conn[N + 2] = conn[4];
		conn[N + 3] = conn[2];
		conn[N + 4] = conn[0];
		connected[i][54] = getIndex(&conn[5]);
		conn[N + 1] = conn[2];
		conn[N + 2] = conn[0];
		conn[N + 3] = conn[4];
		conn[N + 4] = conn[1];
		connected[i][55] = getIndex(&conn[5]);
		conn[N + 1] = conn[2];
		conn[N + 2] = conn[1];
		conn[N + 3] = conn[4];
		conn[N + 4] = conn[0];
		connected[i][56] = getIndex(&conn[5]);
		conn[N + 1] = conn[2];
		conn[N + 2] = conn[4];
		conn[N + 3] = conn[0];
		conn[N + 4] = conn[1];
		connected[i][57] = getIndex(&conn[5]);
		conn[N + 1] = conn[2];
		conn[N + 2] = conn[4];
		conn[N + 3] = conn[1];
		conn[N + 4] = conn[0];
		connected[i][58] = getIndex(&conn[5]);
		conn[N + 1] = conn[4];
		conn[N + 2] = conn[0];
		conn[N + 3] = conn[1];
		conn[N + 4] = conn[2];
		connected[i][59] = getIndex(&conn[5]);
		conn[N + 3] = conn[2];
		conn[N + 4] = conn[1];
		connected[i][60] = getIndex(&conn[5]);
		conn[N + 2] = conn[1];
		conn[N + 3] = conn[0];
		conn[N + 4] = conn[2];
		connected[i][61] = getIndex(&conn[5]);
		conn[N + 3] = conn[2];
		conn[N + 4] = conn[0];
		connected[i][62] = getIndex(&conn[5]);
		conn[N + 2] = conn[2];
		conn[N + 3] = conn[0];
		conn[N + 4] = conn[1];
		connected[i][63] = getIndex(&conn[5]);
		conn[N + 3] = conn[1];
		conn[N + 4] = conn[0];
		connected[i][64] = getIndex(&conn[5]);

		conn[N] = conn[4];

		for (int k = 0; k < 4; k++)
			dong3[k] = conn[k];
		for (int k = 1; k < 4; k++)
			for (int j = k; j > 0 && dong3[j - 1] > dong3[j]; j--) {
				kk = dong3[j];
				dong3[j] = dong3[j - 1];
				dong3[j - 1] = kk;
			}
		for (int k = 0; k < 4; k++)
			conn[k + 1 + N] = dong3[k];

		int cutconnected = getIndex(&conn[5]);

		for (int j = 65; j <= 88; j++) {
			connected[i][j] = cutconnected + j - 65;
		}
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
		print();
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

void getstring(short index, int start) {
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
	int q;
	getstring(best_perm[0], wast);
	for (int i = 1; i < max_perm; i++) {
		int stop = 0;
		for (q = 0; q < 90 && stop == 0; q++) {
			if (q == 90) {
				printf("ERROR!!! at %d, values are %d and %d\n", i, best_perm[i - 1], best_perm[i]);
				fprintf(fp, "ERROR HERE, PERMS ARE: ");
				getstring(best_perm[i - 1], 0);
				fprintf(fp, " AND ");
				getstring(best_perm[i], 0);
				return;
			}
			else if (connected[best_perm[i - 1]][q] == best_perm[i]) {
				stop = 1;
			}
		}
		q--;
		if (q == 0)
			getstring(best_perm[i], N - 1);
		if (q == 1)
			getstring(best_perm[i], N - 2);
		if (q >= 2 && q <= 4)
			getstring(best_perm[i], N - 3);
		if (q >= 5 && q <= 17)
			getstring(best_perm[i], N - 4);
		if (q >= 18 && q <= 88)
			getstring(best_perm[i], N - 5);
	}
}
