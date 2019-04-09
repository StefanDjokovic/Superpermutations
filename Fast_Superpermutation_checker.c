/*This program finds reliably if a string is a superpermutation is less than a second (tested til N = 8)
NOTE: to use this code remember to:
change the value of N to the number of different symbols used on line 13
place your string between the "" on line 150
This program runs both with capital letters starting from A and numbers starting from 1
Bonus: there are functions for printing the hash both on the console and a file, you can enable them by taking away //
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N //N different characters, please input it here

//struct of permutations, can be expanded freely
typedef struct permutation {
	char string[N + 1];	
	int check;		// check >= 1 if the permutation was found in the string
} permutation;

//gets factorial of the int passed
int factorial(int val) {
	int res = 1;
	for (int i = 1; i <= val; i++) {
		res = res * i;
	}
	return res;
}

//adds the new element, more info in README
void new_perm(int i, permutation ** hash, int * arr) {
	for (int j = 0; j < N; j++)
		arr[j] = 0;

	permutation * new_vertex = (permutation *)malloc(sizeof(permutation));
	hash[i] = new_vertex;
	hash[i]->check = 0;
	hash[i]->string[0] = 'A' + i / factorial(N - 1);

	arr[hash[i]->string[0] - 'A'] = 1;

	for (int p = 1; p < N; p++) {
		int val = i % factorial(N - p);

		int step = val / factorial(N - (p + 1));

		int k = 0;
		while (arr[k] == 1)
			k++;
		while (step != 0) {
			if (arr[k] != 1)
				step--;
			k++;
			while (arr[k] == 1)
				k++;
		}
		hash[i]->string[p] = 'A' + k;
		arr[k] = 1;
	}
	hash[i]->string[N] = '\0';
}

//prints the position of the permutation and its string
void printHash(permutation ** hash) {
	for (int i = 0; i < factorial(N); i++) {
		printf("string %d = %s, check = %d\n", i, hash[i]->string, hash[i]->check);
	}
}

//function that gets the hashvalue of a string of N elements, returns -1 if invalid permutation
int getHashValue(char * string) {
	int val = 0;
	int *arr = (int*)calloc(N, sizeof(int));

	val = (string[0] - 'A') * factorial(N - 1);
	arr[string[0] - 'A'] = 1;

	for (int p = 1; p < N; p++) {
		int k = 0;
		int count = 0;
		int step = string[p] - 'A';
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
	return val;
}

//converts string to letters A,B,C...
char * convertString(char **string) {
	int to = strlen(*string);
	char *str = (char*)malloc(sizeof(char) * to);
	strcpy(str, *string);
	for (int i = 0; i < to; i++) {
		str[i] = str[i] - '1' + 'A';
	}

	return str;
}

int runChecker(char * str, permutation** hash, int to) {
	char *perm = (char*)malloc(sizeof(char)*(N+1));
	perm[N] = '\0';
	int hashValue; 

	for (int j = 0; j <= to - N; j++) {
		for (int i = 0; i < N; i++) {
			perm[i] = str[j+i];
		}
		hashValue = getHashValue(perm);
		if (hashValue != -1)
			hash[hashValue]->check = hash[hashValue]->check + 1;
	}

	for (int i = 0; i < factorial(N); i++) {
		if (hash[i]->check != 1)
			return 0;
	}

	free(perm);

	return 1;
}


int main() {
	permutation ** hash = (permutation**)calloc(factorial(N), sizeof(permutation*));

	//printf("Dim hash: %d\n\n", factorial(N));

	int arr[N];
	for (int i = 0; i < factorial(N); i++) {
		new_perm(i, hash, arr);
	}

	//FILE * fp;
	//fp = fopen("Destination printed hash", "w");

	char *stringToCheck;

	stringToCheck = "";	//place here your string
	int to = strlen(stringToCheck);
	char * str = (char*)malloc(sizeof(char) * strlen(stringToCheck));
	strcpy(str, stringToCheck);

	if (str[0] < 'A')
		str = convertString(&stringToCheck); //converts from numbers to capital letters

	int test = runChecker(str, hash, to);

	//printHash(hash);

	//printHash in file
	/*for (int i = 0; i < factorial(N); i++) {
		fprintf(fp, "string %d = %s, check = %d\n", i, hash[i]->string, hash[i]->check);
	}*/


	if (test == 1)
		printf("\nYes, it's a superpermutation\n");
	else
		printf("\nNot a superpermutation\n");


	return 0;
}
