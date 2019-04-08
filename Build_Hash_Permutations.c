#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 5	//N different characters

//struct of permutations, can be expanded freely
typedef struct permutation {
	char string[N+1];
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
	hash[i]->string[0] = 'A' + i / factorial(N-1);

	arr[hash[i]->string[0] - 'A'] = 1;

	for (int p = 1; p < N; p++) {
		int val = i % factorial(N - p);

		int step = val / factorial(N - (p+1));

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
		printf("string %d = %s\n", i, hash[i]->string);
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


//The main
int main() {
	permutation ** hash = (permutation**)calloc(factorial(N), sizeof(permutation*));

	printf("Dim hash: %d\n\n", factorial(N));

	int arr[N];
	for (int i = 0; i < factorial(N); i++) {
		new_perm(i, hash, arr);
	}

	printHash(hash);

	return 0;
}
