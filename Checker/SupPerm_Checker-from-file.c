//The program takes file directory and N from standard input and is able to ignores # comments lines
//It outputs the number of the permutation taken in consideration and if it is a superpermutation
//more info on how it works in README

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


//gets factorial of the int passed
int factorial(int val);

//function that gets a specific hashvalue of a string of N elements, returns -1 if invalid permutation, more info in README
long int getHashValue(int * string);

//the checker function
int runChecker(int * str, bool * checker, int to);

int z; //N-1
bool * arr;
int N;
int *factval;

int main() {
	FILE * fp;
	char filepos[300];
	printf("Please, specify file directory (example: C:\\Users\\...:\n");
	scanf("%149[^\n]%*c", filepos);

	printf("\nPlease, specify N (number of different symbols):\n");
	scanf("%d", &N);

	z = N - 1;

	fp = fopen(filepos, "r");
	if (fp == NULL) {
		printf("File not found\n");
		return -1;
	}

	//contains factorial values from 0! to N!
	factval = (int*)malloc((N + 1) * sizeof(int)); 
	for (int i = 0; i <= N; i++) {
		factval[i] = factorial(i);
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

	//re-ignoring # lines because I rewinded the file pointer
	c = fgetc(fp);
	while (c == '#') {
		while (fgetc(fp) != '\n') { //go till new line
		}
		c = fgetc(fp);
	}


	bool *checker = (bool*)malloc(factval[N] * sizeof(bool));
	arr = (bool*)malloc(N * sizeof(bool));
	for (int j = 1; c != EOF; j++) {
		for (int i = 0; i < factval[N]; i++)
			checker[i] = 0;

		int * stringToCheck = (int *)malloc((size) * sizeof(int));
		//converting the string in ints from 0
		stringToCheck[0] = c - '1';
		for (int i = 1; i < size; i++) {
			stringToCheck[i] = fgetc(fp) - '1'; //if in letters change 1 into A
		}

		//test = 1 if valid superperm, else 0
		int test = runChecker(stringToCheck, checker, size);

		//printing result
		/*if (test == 1)
			printf("Perm %d : Yes, it's a superpermutation\n", j);
		else
			printf("Perm %d : Not a superpermutation\n", j);*/

		free(stringToCheck);

		c = fgetc(fp); //clearing from /n
		c = fgetc(fp);	//gets the first character of the new line, EOF if it's the end
	}

	fclose(fp);

	return 0;
}


int runChecker(int * str, bool * checker, int to) {
	long int hashValue;

	for (int j = 0; j <= to - N; j++) {
		hashValue = getHashValue(&str[j]); 
		if (hashValue != -1)
			checker[hashValue] = 1;

		for (int i = 0; i < N; i++)
			arr[i] = 0;
	}

	for (int i = 0; i < factval[N]; i++) {
		if (checker[i] != 1) {
			return 0;
		}

	}

	return 1;
}

//how it works in README
long int getHashValue(int * string) {
	long int val = 0;

	val = (string[0]) * factval[z];
	arr[string[0]] = 1;
	for (int p = 1; p < N; p++) {			
		int count = 0;
		int step = string[p];
		if (p != z) {
			int k = 0;

			while (k != step) {
				if (arr[k] != 1)
					count++;
				k++;
			}
		}
		if (arr[step] == 0)
			arr[step] = 1;
		else
			return -1;

		val = val + count * factval[z - p];
	}

	return val;
}

int factorial(int val) {
	int res = 1;
	for (int i = 1; i <= val; i++) {
		res = res * i;
	}
	return res;
}

