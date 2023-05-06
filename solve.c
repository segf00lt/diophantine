#include <stdio.h>
#include <assert.h>
#define STB_DS_IMPLEMENTATION
#include "stb_ds.h"

#define Array(T) T *

void euclid_decomp(int a, int b, Array(int) *vals, Array(int) *coefs) {
	int v, c;

	arrput(*vals, a);
	arrput(*vals, b);
	arrput(*coefs, 1);

	while(b != 0) {
		v = a % b;
		c = a / b;
		a = b;
		b = v;
		arrput(*vals, v);
		arrput(*coefs, c);
	}

	assert(arrlast(*vals) == 0);

	arrpop(*vals);
	arrpop(*coefs);
}

void bezout(Array(int) coefs, int *u, int *v) {
	assert(coefs && u && v);

	Array(int) arr = NULL;
	size_t len = arrlen(coefs);
	size_t i = len - 1;

	arrsetlen(arr, len);
	for(int x = 0; x < len; ++x) arr[x]=0; 
	arr[i] = -coefs[i];
	arr[i-1] = 1;

	while(i > 1) {
		arr[i-2] += arr[i];
		arr[i-1] += arr[i] * -coefs[i-1];
		--i;
	}

	*u = arr[0];
	*v = arr[1];

	arrfree(arr);
}

int main() {
	int a, b, c, d;
	printf("enter a: ");
	scanf("%i", &a);
	printf("enter b: ");
	scanf("%i", &b);
	printf("enter c: ");
	scanf("%i", &c);
	Array(int) vals = NULL;
	Array(int) coefs = NULL;
	euclid_decomp(a, b, &vals, &coefs);
	d = arrlast(vals);
	int a_prime = a / d;
	int b_prime = b / d;
	int c_prime = c / d;

	if(c % d != 0) {
		printf("%ix + %iy = %i has no solutions\n", a, b, c);
		return 1;
	}

	int u, v;
	bezout(coefs, &u, &v);

	assert((vals[0]*u + vals[1]*v) == (arrlast(vals)));

	printf("S = { %i + (%i)k, %i - (%i)k) : k in Z }\n", u*c_prime, b_prime, v*c_prime, a_prime);
	return 0;
}
