#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int fact(int n);
void swap(int* xp, int* yp);
int distance (int j, int k);
void nextPermutation (int p[], int n);

int main () {
	int k, p, q;
	scanf("%d", &p);
	printf("\n");
	int c = pow(2,p)-1;
	int length[c];
	for (int i = 0; i < pow(2,p)-1; i++) {
		length[i] = 0;
	}
	int** combination = malloc(sizeof(int*)*(pow(2,p)-1));
	for (int i = 0; i < pow(2,p)-1; i++) {
		combination[i] = malloc(sizeof(int)*p);
	}
	for (int i = 0; i < pow(2,p)-1; i++) {
		for (int j = 0; j < p; j++) {
			combination[i][j] = 0;
		}
	}
	for (int i = 0; i < pow(2,p)-1; i++) {
		k = i+1;
		for (int j = (p-1); j >= 0; j--) {
			if (k % 2 == 0) {
				combination[i][j] = 0;
				k = k/2;
			}
			else if (k % 2 != 0) {
				combination[i][j] = 1;
				k = k/2;
			}
		}
	}
	for (int i = 0; i < pow(2,p)-1; i++) {
		for (int j = 0; j < p; j++) {
			if (combination[i][j] == 1) {
				length[i]++;
			}
		}
	}
	int** updatedCombinations = malloc(sizeof(int*)*(pow(2,p)-1));
	for (int i = 0; i < pow(2,p)-1; i++) {
		updatedCombinations[i] = malloc(sizeof(int));
	}
	for (int i = 0; i < pow(2,p)-1; i++) {
		q = 0;
		for (int j = 0; j < p; j++) {
			if (combination[i][j] == 1) {
				updatedCombinations[i] = realloc(updatedCombinations[i], sizeof(int)*(q+1));
				updatedCombinations[i][q] = j+1;
				q++;
			}
		}
	}
	printf("()\n");
	for (int i = 0; i < p; i++) {
		for (int j = 0; j < pow(2,p)-1; j++) {
			if (length[j] == (i+1)) {
				for (int e = 0; e < i+1; e++) {
					if (e == 0 && i == 0) {
						printf("(%d)", updatedCombinations[j][e]);
					}
					else if (e == 0) {
						printf("(%d,", updatedCombinations[j][e]);
					}
					else if (e == i) {
						printf("%d)", updatedCombinations[j][e]);
					}
					else {
						printf("%d,", updatedCombinations[j][e]);
					}
				}
				printf("\n");
				for (int e = 0; e < fact(i+1)-1; e++) {
					nextPermutation(updatedCombinations[j], i+1);
					for (int f = 0; f < i+1; f++) {
						if (f == 0 && i == 0) {
							printf("(%d)", updatedCombinations[j][f]);
						}
						else if (f == 0) {
							printf("(%d,", updatedCombinations[j][f]);
						}
						else if (f == i) {
							printf("%d)", updatedCombinations[j][f]);
						}
						else {
							printf("%d,", updatedCombinations[j][f]);
						}
					}
					printf("\n");
				}
			}
		}
	}
}
int fact(int n) {
	if (n == 1) {
		return 1;
	}
	else {
		return n * fact(n-1);
	}
}

void nextPermutation (int p[], int n) {
	int current = 0, smaller = 0, closest, min, j;
	for (int i = n-1; i > 0; i--) {
		if (p[i] > p[i-1]) {
			current = i;
			smaller = i-1;
			break;
		}
	}
	closest = current;
	for (int i = current; i < n; i++) {
		if ((distance(p[i], p[smaller]) > 0) && (distance(p[i], p[smaller]) < distance(p[closest], p[smaller]))) {
			closest = i;
		}
	}
	swap(&p[closest], &p[smaller]);
	if (closest != 0) {
		for (int i = current; i < n-1; i++) {
    	    min = i;
    	    for (j = i + 1; j < n; j++) {
    	        if (p[j] < p[min]) {
                	min = j;
            	}
        	}
    	    swap(&p[min], &p[i]);
    	}
	}
}
int distance (int j, int k) {
	return (j-k);
}
void swap(int* xp, int* yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}