//The checker can now take file directory and N from standard input and ignores #comments

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//gets factorial of the int passed
int factorial(int val);

//function that gets a specific hashvalue of a string of N elements, returns -1 if invalid permutation, more info in README
long int getHashValue(char * string, int N);

//the checker function
int runChecker(int * str, bool * arr, int to, int N);


//The main, only for permutation of numbers from 1
int main() {
	int N;

	FILE * fp;

	char filepos[300];
	printf("Please, specify file directory (example: C:\\Users\\...:\n");
	scanf("%149[^\n]%*c", filepos);

	printf("\nPlease, specify N (number of different symbols):\n");
	scanf("%d", &N);

	fp = fopen(filepos, "r");
	if (fp == NULL) {
		printf("File not found\n");
		return -1;
	}

	//code that ignores # lines
	char c;
	c = fgetc(fp);	
	while (c == '#') {
		while (fgetc(fp) != '\n') {
			//do nothing til we get to new line
		}
		c = fgetc(fp);
	}

	char b = fgetc(fp);
	//gets the size
	int size = 1;
	while (b != '\n') {
		b = fgetc(fp);
		size++;
	}	
	rewind(fp);

	//re-doing because I rewinded the file pointer
	c = fgetc(fp);
	while (c == '#') {
		while (fgetc(fp) != '\n') { //go till new line
		}
		c = fgetc(fp);
	}

	for (int j = 1; c != EOF; j++) {
		bool *checker = (bool*)calloc(factorial(N), sizeof(bool));

		int * stringToCheck = (int *)malloc((size) * sizeof(int));
		stringToCheck[0] = c - '1';
		for (int i = 1; i < size; i++) {
			stringToCheck[i] = fgetc(fp) - '1'; //if in letters change 1 into A
		}

		int test = runChecker(stringToCheck, checker, size, N);

		if (test == 1)
			printf("Perm %d : Yes, it's a superpermutation\n", j);
		else
			printf("Perm %d : Not a superpermutation\n", j);

		free(stringToCheck);

		free(checker);

		c = fgetc(fp);
		c = fgetc(fp);
	}

	fclose(fp);

	return 0;
}



int runChecker(int * str, bool * arr, int to, int N) {
	char *perm = (char*)malloc(sizeof(char)*(N + 1));
	perm[N] = '\0';
	long int hashValue;

	for (int j = 0; j <= to - N; j++) {
		for (int i = 0; i < N; i++) {
			perm[i] = str[j + i];
			//printf("%d", perm[i]);
		}
		//printf(" %d\n", j);
		hashValue = getHashValue(perm, N);
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

long int getHashValue(char * string, int N) {
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

int factorial(int val) {
	int res = 1;
	for (int i = 1; i <= val; i++) {
		res = res * i;
	}
	return res;
}
