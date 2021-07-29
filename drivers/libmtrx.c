#include <stdio.h>
#include <stdlib.h>
#include "libmtrx.h"

#define N 128

#define swap(A, B) {int tmp = *A; *A = *B; *B = tmp;}

#define pmatrix(M, y, x, f) { \
/* print (y, x) matrix */ \
	for (short i = 0; i < y; i++) { \
		printf("["); \
		for (short j = 0; j < x; j++) { \
			(M[i][j].floatpoint < 0) ? printf("") : printf(" "); \
			if (f == 0) \
				printf("%LF", (long double) M[i][j].numerator / M[i][j].denominator); \
			else \
				printfrac(M[i][j]); \
			(j == x - 1) ? printf("") : printf(" "); \
		} \
		printf("]\n"); \
	} \
} \

#define make_matrix(w, h, A, M) { \
	for (int i = 0; i < h; i++) { \
		for (int j = 0; j < w; j++) { \
			M[i][j].numerator = A[i][j]; \
			M[i][j].denominator = 1; \
			M[i][j].floatpoint = (long double) A[i][j] / 1; \
		} \
	} \
} \

#define make_identity_matrix(M, d) { \
	for (int i = 0; i < d; i++) { \
		for (int j = 0; j < d; j++) { \
			M[i][j].numerator = (i == j) ? 1 : 0; \
			M[i][j].denominator = 1; \
			M[i][j].floatpoint = (i == j) ? 1.0 : 0.0; \
		} \
	} \
} \

#define dim(M, w, h) { \
	int y = sizeof(M) / sizeof(M[0]); \
	int x = sizeof(M[0]) / sizeof(M[0][0]); \
	w = &x; \
	h = &y; \
} \

int power(const int x, const int n) {
	function_assert(x == -1, "power assert reached. base not -1.");
	int pow = 1;
	for (int i = 0; i < n; i++) {
		pow *= x;
	}
	return pow;
}

unsigned long long factorial(unsigned long long n) {
	function_assert(n >= 0, "factorial assert reached. negative int.");
	if (n == 0) {
		return 1;
	} else {
		n *= factorial(n - 1);
	}
	return n;
}

int visited[N];
int destination[N];

static int dfs(const int i) {
	if (visited[i]) {
		return 0;
	}
	visited[i] = 1;
	int t = dfs(destination[i]);
	return (t + 1);
}

int ntransposition(const int *V, const int n) {
/* find the # of transpositions for a given *
 * array V  {1, 2, ..., n} and its length n */

	int t = 0, a = 0;
	short i;

	for (i = 1; i < n + 1; i++) {
		visited[i] = 0;
	}

	for (i = 1; i < n + 1; i++) {
		destination[V[i - 1]] = i;
	}

	for (i = 1; i < n + 1; i++) {
		if (!visited[i]) {
			a = dfs(i);
			t += a - 1;
		}
	}

	return t;
}

static void linear_row(int *v, const int n) {
	int start_at = 1;
	for (int i = start_at; i < n + 1; i++) {
		v[i-1] = i;
	}
}

static void transfer_matrix(const int w, const int h, frac F[][w], frac T[][w]) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			T[i][j].numerator = F[i][j].numerator;
			T[i][j].denominator = F[i][j].denominator;
			T[i][j].floatpoint = F[i][j].floatpoint;
		}
	}
}

static int is_identical(int w, int h, frac A[][w], frac B[][w]) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			simplify(&A[i][j]);
			simplify(&B[i][j]);
			if (A[i][j].numerator != B[i][j].numerator || A[i][j].denominator != B[i][j].denominator) {
				return 0;
			} 		
		}
	}
	return 1;
}


/* basic matrix operations */

#define m(A, y, x, B, C) { \
/* multiply matrix (y, x) A and B and put into C */ \
													\
/* TODO: allow for non square matrices aka add x and y for B */ \
													\
	frac dot; \
	for (short i = 0; i < y; i++) { \
		for (short  k = 0; k < y; k++) { \
			dot.numerator = 0; \
			dot.denominator = 1; \
			for (short j = 0; j < x; j++) { \
				dot.numerator = (A[i][j].numerator * B[j][k].numerator) * dot.denominator + dot.numerator * (A[i][j].denominator * B[j][k].denominator); \
				dot.denominator *= A[i][j].denominator * B[j][k].denominator; \
			} \
			C[i][k].numerator = dot.numerator; \
			C[i][k].denominator = dot.denominator; \
			C[i][k].floatpoint = dot.numerator / dot.denominator; \
			simplify(&C[i][k]); /* simplify the result of the multiplication */ \
		} \
	} \
} \


#define a(A, y, x, B) { \
/* add matrix A and B and put result in B */ \
	for (short i = 0; i < y; i++) { \
		for (short j = 0; j < x; j++) { \
			B[i][j].numerator = B[i][j].denominator * A[i][j].numerator + A[i][j].denominator * B[i][j].numerator; \
			B[i][j].denominator = max(B[i][j].denominator, 1) * A[i][j].denominator; \
			B[i][j].floatpoint += A[i][j].numerator /A[i][j].denominator; \
			simplify(&B[i][j]); /* simplify the result of the addition */ \
		} \
	} \
} \


#define s(A, y, x, B) { \
/* subtract matrix A from B and put result in B */ \
	for (short i = 0; i < y; i++) { \
		for (short j = 0; j < x; j++) { \
			B[i][j].numerator = B[i][j].denominator * A[i][j].numerator - A[i][j].denominator * B[i][j].numerator; \
			B[i][j].denominator = max(B[i][j].denominator, 1) * A[i][j].denominator; \
			B[i][j].floatpoint += A[i][j].numerator /A[i][j].denominator; \
			simplify(&B[i][j]); /* simplify the result of the subtraction */ \
		} \
	} \
} \


#define t(A, x, y, C) { \
/* transpose matrix A and put result in C */ \
	for (short i = 0; i < y; i++) { \
		for (short j = 0; j < x; j++) { \
			C[j][i] = A[i][j]; \
		} \
	} \
} \


#define mn(A, x, y, n) { \
/* multiply matrix A with n in place */ \
	for (short i = 0; i < y; i++) { \
		for (short j = 0; j < x; j++) { \
			A[j][i].numerator *= n.numerator; \
			A[j][i].denominator *= n.denominator; \
			simplify(&A[j][i]); /* simplify the result of the multiplication */ \
		} \
	} \
} \

/* end basic operations */


void d(int *V, const int n, const int s, const int x, frac *D, const frac M[][x], const unsigned long long f, const short r) {
/* calculate  square  matrix  determinant  using  Leibniz *
 * method. Recursively using Heap's permutation algorithm */

	/* function arguments:					*
	 *	- V: changing permutation vector 		*
	 *	- n: changing vector length			*
	 *	- s: initial vector length			*
	 *	- x: real width of M 				*
	 *	- D: changing determinant value			*
	 *	- M: matrix					*
	 *	- f: factorial of s				*
	 *	- r: reset c and D to 0 if true (1)		*/

	static int c = 0; /* speed optimization over ntransposition(V, s) assuming constant pattern */
	if (r) {
		c = 0;
		D->numerator = 0;
		D->denominator = 1;
	} 
		
	if (n == 1) {
		//int t = ntransposition(V, s); /* find number of transpositions (odd or even) */
		int sign = power(-1, c); 		
		long int prod_num = sign;
		long int prod_denom = 1;

		for (int i = 0; i < s; i++) {
			prod_num *= M[i][V[i] - 1].numerator;
			prod_denom *= M[i][V[i] - 1].denominator;
		}

		D->numerator = D->numerator * prod_denom + prod_num * D->denominator;
		D->denominator *= prod_denom;
		function_assert(D->denominator != 0, "0 denominator inside determinant function");
		++c;

		function_assert(c < f + 1, "determinant assert reached. too many permutations found.");

	} else {
		d(V, n - 1, s, x, D, M, f, 0);
		for (int i = 0; i < n - 1; i++) {

			if (n % 2 == 0) {
				swap(&V[i], &V[n-1]);
			} else {
				swap(&V[0], &V[n-1]);
			}

			d(V, n - 1, s, x, D, M, f, 0);
		}
		
	}
}

void reduce(const int w, const frac M[][w], const int x, const int y, frac R[][w]) {
/* create reduced matrices for calculation of Minors and Cofactors */

	/* function arguments:					*
	 *	- w: width of M					*
	 *	- M: matrix to reduce				*
	 *	- x: row to remove				*
	 *	- y: column to remove				*
	 *	- R: resulting matrix				*/

	function_assert(x < w, "reduce assert reached, x out of matrix bounds");
	function_assert(y < w, "reduce assert reached, y out of matrix bounds");

	int offset = 0;
	for (int i = 0; i < w; i++) {
		if (i == x)
			offset = 1;
		for (int j = 0; j < w; j++) {
			R[i][j].numerator = M[i + offset][j].numerator;
			R[i][j].denominator = M[i + offset][j].denominator;
		}
	}

	for (int i = 0; i < w; i++) {
		offset = 0;
		for (int j = 0; j < w; j++) {
			if (j == y)
				offset = 1;
			R[i][j].numerator = R[i][j + offset].numerator;
			R[i][j].denominator = R[i][j + offset].denominator;
		}
	}
}

void i(const int w, const frac M[][w], frac R[][w]) {
/* invert any non singular matrix with adjugated matrix */

	/* function arguments:					*
	 *	- w: width of M					*
	 *	- M: matrix to invert				*
	 *	- R: resulting matrix				*/

	int base_state[w - 1], base_state_full[w];
	frac det = {0,1,0.0};
	frac T[w][w], H[w][w];

	for (int i = 0; i < w; i++) {
		for (int j = 0; j < w; j++) {

			reduce(w, M, i, j, H);

			linear_row(base_state, w - 1);
			d(base_state, w - 1, w - 1, w, &det, H, factorial(w - 1), 1);

			T[i][j].numerator = power(-1, i + j) * det.numerator;
			T[i][j].denominator = det.denominator;
			function_assert(T[i][j].denominator != 0, "0 denominator inside invert function");

		}
	}

	t(T, w, w, R);

	linear_row(base_state_full, w);
	d(base_state_full, w, w, w, &det, M, factorial(w), 1);

	function_assert(det.numerator != 0, "can not invert singular matrix.");

	const frac det_f = {det.denominator, det.numerator, det.denominator / det.numerator};
	mn(R, w, w, det_f);
}

int is_invertable(const int w, const frac M[][w]) {
	frac det = {0,1,0.0};
	int base_state[w];

	linear_row(base_state, w);
	d(base_state, w, w, w, &det, M, factorial(w), 1);

	return det.numerator != 0;
}

int commutator(int w, frac A[][w], frac B[][w]) {
	frac T1[w][w], T2[w][w];
	m(A, w, w, B, T1);
	m(B, w, w, A, T2);
	if (is_identical(w, w, T1, T2))
		return 1;
	return 0;
}

void p(const int w, frac M[][w], frac R[][w], int n) {
/* raise matrix M to power of n and put result in matrix R */

	/* function arguments:				*
	 *	- w: width and height of M		*
	 *	- M: matrix to raise to power		*
	 *	- R: resulting matrix			*
	 *	- n: power to raise to			*/

	frac T[w][w];
	int i;

	for (i = 0; i < n - 1; i++) {
		if (i == 0) {
			m(M, w, w, M, T);
		} else {
			if (i % 2 == 0) {
				m(M, w, w, R, T);
			} else {
				m(M, w, w, T, R);
			}
		}
	}

	if (i % 2 == 1) 
		transfer_matrix(w, w, T, R);
}

 // int main() {

	/* test vectors here */
	
	/* driver code  here */

//	return 0;
// }
