/*Based on Faster_SuperPermutation_Checker, you need to put a value to N in line 11 and insert file directory to 88
There are still many improvments to implement, coming soon
*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define N //N different characters, please input it here

//gets factorial of the int passed
int factorial(int val) {
	int res = 1;
	for (int i = 1; i <= val; i++) {
		res = res * i;
	}
	return res;
}

//function that gets the hashvalue of a string of N elements, returns -1 if invalid permutation
long int getHashValue(char * string) {
	long int val = 0;
	bool *arr = (bool*)calloc(N, sizeof(bool));

	val = (string[0]) * factorial(N - 1);
	arr[string[0]] = 1;

	for (int p = 1; p < N; p++) {
		int k = 0;
		int count = 0;
		int step = string[p];
		//printf(" step : %d ", string[p]);
		while (k != step) {
			if (arr[k] != 1)
				count++;
			k++;
		}
		if (arr[step] == 0)
			arr[step] = 1;
		else
			return -1;

		val = val + count * factorial(N - (p + 1));
	}

	free(arr);
	//printf(" val: %d ", val);
	return val;
}

int runChecker(int * str, bool * arr, int to) {
	char *perm = (char*)malloc(sizeof(char)*(N + 1));
	perm[N] = '\0';
	long int hashValue;

	for (int j = 0; j <= to - N; j++) {
		for (int i = 0; i < N; i++) {
			perm[i] = str[j + i];
			//printf("%d", perm[i]);
		}
		//printf(" %d\n", j);
		hashValue = getHashValue(perm);
		if (hashValue != -1)
			arr[hashValue] = 1;
		//printf("wow %d ", j);
	}

	for (int i = 0; i < factorial(N); i++) {
		if (arr[i] != 1) {
			return 0;
		}
			
	}

	free(perm);

	return 1;
}


//The main, only for permutation of numbers from 1
int main() {
	bool *checker = (bool*)calloc(factorial(N), sizeof(bool));

	FILE * fp;
	fp = fopen("insert-file-directory", "r"); //insert here your file directory
	if (fp == NULL) {
		printf("File not found\n");
		return -1;
	}



	int size = -1;
	while (feof(fp) == 0) {
		fgetc(fp);
		size++;
	}
	rewind(fp);
	printf("size = %d\n", size);

	int * stringToCheck = (int *)malloc((size) * sizeof(int));
	for (int i = 0; feof(fp) == 0; i++) {
		stringToCheck[i] = fgetc(fp) - '1'; //if in letters change 1 into A
	}

	int test = runChecker(stringToCheck, checker, size);

	if (test == 1)
		printf("\nYes, it's a superpermutation\n");
	else
		printf("\nNot a superpermutation\n");

	free(checker);

	fclose(fp);

	return 0;
}
