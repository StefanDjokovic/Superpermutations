//Faster N = 6, it gets to 94 in about 30s.
//Seems to be working well, but it still requires some improvements to be able to reach the final result
//Also this version doesn't print the partial results, will add that soon

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

short max_perm;
short mperm_res[1000];
short tot_bl;

short cur_perm[4000];	//to 4000 just to be safe
short cur_best[4000];

short N;

bool* checker;
int* factval;
int* upper;
int* power;
short* connected1;
short* connected2;
short* connected3;
short* connected4;
short* connected5;
bool* arr;
short stopit;
short stopitover;
short dong[3];
short dong2[4];
short minim;


int factorial(int k);

int getHashValue2(int* string) {
	long int val = 0;
	for (int i = 0; i < N; i++) {
		val = val * N + string[i];
	}
	val = upper[val];

	return val;
}

//this is the starting fillStr call
void fillStr0(short int pfound, short int hashValue, short int waste) {
	if (pfound > max_perm) {
		max_perm = pfound;
	}

	if (max_perm < stopit && max_perm < stopitover) {
		int minihash = hashValue;
		checker[minihash] = 1;
		int pfound2 = pfound + 1;

		//Making unwasted characters
		if (checker[connected1[minihash]] == 0)
			fillStr0(pfound2, connected1[minihash], waste);
		waste--;
		if (waste >= 0 && mperm_res[waste] + pfound > max_perm && mperm_res[waste] + pfound >= minim) {
			if (checker[connected2[minihash]] == 0)
				fillStr0(pfound2, connected2[minihash], waste);
			waste--;
			if (waste >= 0 && mperm_res[waste] + pfound > max_perm && mperm_res[waste] + pfound >= minim) {
				hashValue = connected3[minihash];
				if (checker[hashValue] == 0)
					fillStr0(pfound2, hashValue, waste);
				hashValue++;
				if (checker[hashValue] == 0)
					fillStr0(pfound2, hashValue, waste);
				waste--;
				if (waste >= 0 && mperm_res[waste] + pfound > max_perm && mperm_res[waste] + pfound >= minim) {
					hashValue = connected4[minihash];
					if (checker[hashValue] == 0)
						fillStr0(pfound2, hashValue, waste);
					hashValue++;
					if (checker[hashValue] == 0)
						fillStr0(pfound2, hashValue, waste);
					hashValue++;
					if (checker[hashValue] == 0)
						fillStr0(pfound2, hashValue, waste);
					hashValue++;
					if (checker[hashValue] == 0)
						fillStr0(pfound2, hashValue, waste);
					hashValue++;
					if (checker[hashValue] == 0)
						fillStr0(pfound2, hashValue, waste);
					hashValue++;
					if (checker[hashValue] == 0)
						fillStr0(pfound2, hashValue, waste);

					waste--;
					if (waste >= 0 && mperm_res[waste] + pfound > max_perm && mperm_res[waste] + pfound >= minim) {
						hashValue = connected5[minihash];
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
						hashValue++;
						if (checker[hashValue] == 0)
							fillStr0(pfound2, hashValue, waste);
					}
				}
			}

		}
		checker[minihash] = 0;
	}
}



int main()
{
	unsigned short int j0;

	printf("This tool will try to find the length of the shortest superpermutation on n symbols. Please enter n: 6");
	//scanf("%d", &N);

	N = 6;

	mperm_res[0] = N;

	//contains factorial values from 0! to N!
	factval = (int*)malloc((N + 1) * sizeof(int));
	for (int i = 0; i <= N; i++) {
		factval[i] = factorial(i);
	}

	stopit = factval[N];

	upper = (int*)calloc(pow(N, N + 1), sizeof(int)); //a bit excessive, to improve
	power = (int*)malloc(sizeof(int) * (N * 2 + 1));
	connected1 = (short*)malloc(sizeof(short) * factval[N]);
	connected2 = (short*)malloc(sizeof(short) * factval[N]);
	connected3 = (short*)malloc(sizeof(short) * factval[N]);
	connected4 = (short*)malloc(sizeof(short) * factval[N]);
	connected5 = (short*)malloc(sizeof(short) * factval[N]);

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

	//generationg connected1 and connected2
	int* conn = (int*)malloc(sizeof(int) * (N + 2));
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
		connected5[i] = getHashValue2(&conn[5]);

	}
	checker = (bool*)malloc(sizeof(bool) * factval[N]);


	printf("Thanks for choosing N: %d, let's start!\n", N);

	max_perm = 1;
	mperm_res[0] = N;
	mperm_res[1] = 12;

	for (tot_bl = 1; tot_bl <= 150; tot_bl++) {
		//max_perm = 1; I can keep the previous max_perm to speed things up


		minim = mperm_res[tot_bl - 1] + 4;
		stopitover = mperm_res[tot_bl - 1] + 6;
		for (int i = 0; i < factval[N]; i++) {
			checker[i] = 0;
		}

		checker[0] = 1;

		fillStr0(1, 0, tot_bl);
		mperm_res[tot_bl] = max_perm;
		mperm_res[tot_bl + 1] = max_perm + 4;	//conjecture that the current will be at least +4 in N=6 compared the previous


		printf("%d wasted characters: at most %d permutations\n", tot_bl, max_perm);

		for (int i = 0;i < 1000; i++) {
			fprintf(fp, "%d ",cur_best[i]);
		}
		fprintf(fp, "\n");

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
