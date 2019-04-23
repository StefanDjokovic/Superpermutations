//clearer and faster code

//clearer and faster code

#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int curstr[1000], max_perm, mperm_res[1000], N, tot_bl;
unsigned long int cur_perms[1000];
int curmax[1000];

bool* checker;
int* factval;
long int* upper;
int* power;
int* connected1;
int* connected2;
int* connected3;
int* connected4;
int* connected5;
bool* arr;
unsigned long int tperm;
int stopit;
int stopitover;
int dong[3];
int dong2[4];
int minim;


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
void fillStr0(short int pos, short int pfound, int hashValue, int waste) {
	if (pfound > max_perm)
		max_perm = pfound;
	if (max_perm < stopit && max_perm < stopitover) {
		int minihash = hashValue;
		int tempwaste;
		checker[minihash] = 1;
		int pfound2 = pfound + 1;
		int pos4 = pos + 4;
		int pos5 = pos + 5;
		int running;

		//Making unwasted characters
		hashValue = connected1[minihash];
		if (checker[hashValue] == 0)
			fillStr0(pos+1, pfound2, hashValue, waste);
		tempwaste = waste - 1;
		if (tempwaste >= 0 && mperm_res[tempwaste] + pfound > max_perm && mperm_res[tempwaste] + pfound >= minim) {
			hashValue = connected2[minihash];
			if (checker[hashValue] == 0)
				fillStr0(pos+2, pfound2, hashValue, tempwaste);
			tempwaste--;
			if (tempwaste >= 0 && mperm_res[tempwaste] + pfound > max_perm && mperm_res[tempwaste] + pfound >= minim) {
				hashValue = connected3[minihash];
				if (checker[hashValue] == 0)
					fillStr0(pos+3, pfound2, hashValue, tempwaste);
				hashValue++;
				if (checker[hashValue] == 0)
					fillStr0(pos+3, pfound2, hashValue, tempwaste);
				tempwaste--;
				if (tempwaste >= 0 && mperm_res[tempwaste] + pfound > max_perm && mperm_res[tempwaste] + pfound >= minim) {
					hashValue = connected4[minihash];
					running = hashValue + 6;
					while (hashValue < running) {
						if (checker[hashValue] == 0)
							fillStr0(pos4, pfound2, hashValue, tempwaste);
						hashValue++;
					}
					tempwaste--;
					if (tempwaste >= 0 && mperm_res[tempwaste] + pfound > max_perm && mperm_res[tempwaste] + pfound >= minim) {
						hashValue = connected5[minihash];
						running = hashValue + 24;
						while (hashValue < running) {
							if (checker[hashValue] == 0)
								fillStr0(pos5, pfound2, hashValue, tempwaste);
							hashValue++;
						}
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

	/*FILE* fp;
	fp = fopen("C:\\Users\\Stefan Djokovic\\Desktop\\Superpermutations\\resultsCaffinN6.txt", "w");*/

	//contains factorial values from 0! to N!
	factval = (int*)malloc((N + 1) * sizeof(int));
	for (int i = 0; i <= N; i++) {
		factval[i] = factorial(i);
	}

	stopit = factval[N];

	upper = (long int*)calloc(pow(N, N + 1), sizeof(long int)); //a bit excessive, to improve
	power = (int*)malloc(sizeof(int) * (N * 2 + 1));
	connected1 = (int*)malloc(sizeof(int) * factval[N]);
	connected2 = (int*)malloc(sizeof(int) * factval[N]);
	connected3 = (int*)malloc(sizeof(int) * factval[N]);
	connected4 = (int*)malloc(sizeof(int) * factval[N]);
	connected5 = (int*)malloc(sizeof(int) * factval[N]);

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
				dong[j - 1] = kk;
			}
		for (int k = 0; k < 4; k++)
			conn[k + 1 + N] = dong[k];
		connected5[i] = getHashValue2(&conn[5]);

	}

	checker = (bool*)malloc(sizeof(bool) * factval[N]);
	///END OF GENERATING CONNECTIONS ETC


	printf("Thanks for choosing N: %d, let's start!\n", N);

	for (tot_bl = 1; tot_bl <= 150; tot_bl++) {
		max_perm = 1;

		for (int i = 0; i < factval[N]; i++) ///THE NEW CLEARPERMS
			checker[i] = 0;

		for (j0 = 0; j0 < N; j0++) {
			curstr[j0] = j0;
		}
		checker[0] = 1;
		minim = mperm_res[tot_bl - 1] + 4;
		stopitover = mperm_res[tot_bl - 1] + 6;
		fillStr0(N, 1, 0, tot_bl);
		mperm_res[tot_bl] = max_perm;

		printf("%d wasted characters: at most %d permutations\n", tot_bl, max_perm);

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
