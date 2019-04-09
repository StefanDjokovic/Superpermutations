/*Only for permutation of numbers starting from 1 (switching it to cap letters only is fairly easy)
just decide the N in line 10 and place your superpermutation in 106
Attention! If the string is of N > 9 it probably requires to be uploaded from file, istruction line 110*/
//For N = 12 it requires around 3GB of RAM

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N //N different characters, please input it here

//struct of permutations, can be expanded freely
typedef struct permutation {
	int check;
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
void new_perm(int i, permutation ** hash) {
	permutation * new_vertex = (permutation *)malloc(sizeof(permutation));
	hash[i] = new_vertex;
	hash[i]->check = 0;
}

//function that gets the hashvalue of a string of N elements, returns -1 if invalid permutation
int getHashValue(char * string) {
	int val = 0;
	int *arr = (int*)calloc(N, sizeof(int));

	val = (string[0] - '1') * factorial(N - 1);
	arr[string[0] - '1'] = 1;

	for (int p = 1; p < N; p++) {
		int k = 0;
		int count = 0;
		int step = string[p] - '1';
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
	char *perm = (char*)malloc(sizeof(char)*(N + 1));
	perm[N] = '\0';
	int hashValue;

	for (int j = 0; j <= to - N; j++) {
		for (int i = 0; i < N; i++) {
			perm[i] = str[j + i];
		}
		hashValue = getHashValue(perm);
		if (hashValue != -1)
			hash[hashValue]->check++;
	}

	for (int i = 0; i < factorial(N); i++) {
		if (hash[i]->check != 1)
			return 0;
	}

	free(perm);

	return 1;
}


//The main, only for permutation of numbers from 1
int main() {
	permutation ** hash = (permutation**)calloc(factorial(N), sizeof(permutation*));

	for (int i = 0; i < factorial(N); i++) {
		new_perm(i, hash);
	}

	char *stringToCheck;
	stringToCheck = "";	//place here your string
	
	int sizeSup = strlen(stringToCheck);

	/*If the string used has more than 65KB the string should be taken from file with sth like
	FILE * fp = fopen(fp, "file.directory", "r");
	for (int i = 0; fp != EOF; i++) {
	str[i] = getc(fp);
	After allocating the string
	*/

	int test = runChecker(stringToCheck, hash, sizeSup);

	if (test == 1)
		printf("\nYes, it's a superpermutation\n");
	else
		printf("\nNot a superpermutation\n");


	return 0;
}
