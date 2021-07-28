#include "libmtrx.c"

/* the size of matrix struct is  capped  at *
 * 256 x 256 by default. This value can  be *
 * tweeked when bigger  matrices  are  used */
#define MAX_WIDTH_MATRIX 	256
#define MAX_HEIGHT_MATRIX 	256
typedef struct {
	int 	width;
	int 	height;
	frac 	Matrix[MAX_HEIGHT_MATRIX][MAX_WIDTH_MATRIX];
} matrix;
/* wrapper struct  to  hide ugly notation and *
 * for enhancement of  the  ease of  use.  If *
 * memory   and  speed   efficiency   are  of *
 * importance, the use of  the matrix  struct *
 * is  not recommended,  reffer  to  use  of: *
 * frac (*M)[w] where w is the width  of   M */

static void cpymtrx(int w, int h, frac (*A)[w], matrix *M) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			M->Matrix[i][j].numerator = A[i][j].numerator;
			M->Matrix[i][j].denominator = A[i][j].denominator;
			M->Matrix[i][j].floatpoint = A[i][j].floatpoint;
		}
	}
}

static void cpymtrxstrct(int w, int h, matrix *F, matrix *M) {
	for (int i = 0; i < h; i++) {
		for (int j = 0; j < w; j++) {
			M->Matrix[i][j].numerator = F->Matrix[i][j].numerator;
			M->Matrix[i][j].denominator = F->Matrix[i][j].denominator;
			M->Matrix[i][j].floatpoint = F->Matrix[i][j].floatpoint;
		}
	}
}

#define pmatrixstruct(Mat, f) { \
/* print (y, x) matrix */ \
	for (short i = 0; i < Mat->height; i++) { \
		printf("["); \
		for (short j = 0; j < Mat->width; j++) { \
			(Mat->Matrix[i][j].floatpoint < 0) ? printf("") : printf(" ");  \
			if (f == 0) \
				printf("%LF", (long double) Mat->Matrix[i][j].numerator /   \
											Mat->Matrix[i][j].denominator); \
			else \
				printfrac(Mat->Matrix[i][j]); \
			(j == Mat->width - 1) ? printf("") : printf(" "); \
		} \
		printf("]\n"); \
	} \
} \

/*		 class MTRX_FUNCTIONS_NO_R 		  */
/*   print only functions with no rvalue  */

static void MTRX_FUNCTIONS_NO_R__addition(char *a, char *b) {

	int *size_A = parse_matrix_size(a);
	int *size_B = parse_matrix_size(b);

	function_assert(size_A[0] == size_B[0], 
		"Matrix A and B do not have the same height, addition requires identically sized matrices.");
	function_assert(size_A[1] == size_B[1], 
		"Matrix A and B do not have the same width, addition requires identically sized matrices.");

	frac (*A)[size_A[1]] = parse_matrix(a);
	frac (*B)[size_B[1]] = parse_matrix(b);

	a(A, size_A[0], size_A[1], B);

	pmatrix(B, size_B[0], size_B[1], 1);
}

static void MTRX_FUNCTIONS_NO_R__subtraction(char *a, char *b) {
	int *size_A = parse_matrix_size(a);
	int *size_B = parse_matrix_size(b);

	function_assert(size_A[0] == size_B[0], 
		"Matrix A and B do not have the same height, addition requires identically sized matrices.");
	function_assert(size_A[1] == size_B[1], 
		"Matrix A and B do not have the same width, addition requires identically sized matrices.");

	frac (*A)[size_A[1]] = parse_matrix(a);
	frac (*B)[size_B[1]] = parse_matrix(b);

	s(A, size_A[0], size_A[1], B);
	pmatrix(B, size_B[0], size_B[1], 1);
}

static void MTRX_FUNCTIONS_NO_R__multiplication(char *a, char *b) {
	int *size_A = parse_matrix_size(a);
	int *size_B = parse_matrix_size(b);

	function_assert(size_A[1] == size_B[0], 
		"Matrix A and B can not be multiplied, width of A must be equal to height of B.");

	frac (*A)[size_A[1]] = parse_matrix(a);
	frac (*B)[size_B[1]] = parse_matrix(b);

	frac M[size_B[0]][size_B[1]];

	m(A, size_A[0], size_A[1], B, M);
	pmatrix(M, size_B[0], size_B[1], 1);
}

static void MTRX_FUNCTIONS_NO_R__transpose(char *a) {
	int *size_A = parse_matrix_size(a);

	frac (*A)[size_A[1]] = parse_matrix(a);

	frac M[size_A[0]][size_A[1]];

	t(A, size_A[0], size_A[1], M);
	pmatrix(M, size_A[0], size_A[1], 1);
}

static void MTRX_FUNCTIONS_NO_R__invert(char *a) {
	int *size_A = parse_matrix_size(a);

	function_assert(size_A[1] == size_A[0], 
		"Matrix is not square.");

	frac (*A)[size_A[1]] = parse_matrix(a);

	frac M[size_A[0]][size_A[1]];

	i(size_A[0], A, M);
	pmatrix(M, size_A[0], size_A[1], 1);
}

static void MTRX_FUNCTIONS_NO_R__determinant(char *a) {
	int *size_A = parse_matrix_size(a);

	function_assert(size_A[1] == size_A[0], 
		"Matrix is not square.");

	frac (*A)[size_A[1]] = parse_matrix(a);

	frac det = {0,1,0.0};
	int base_state[size_A[1]];

	linear_row(base_state, size_A[1]);
	d(base_state, size_A[1], size_A[1], size_A[1], &det, A, factorial(size_A[1]), 1);

	printfrac(det);
	printf("\n");
}

static void MTRX_FUNCTIONS_NO_R__power(char *a, int n) {
	int *size_A = parse_matrix_size(a);

	frac (*A)[size_A[1]] = parse_matrix(a);

	frac M[size_A[0]][size_A[1]];

	p(size_A[1], A, M, n);
	pmatrix(M, size_A[0], size_A[1], 1);
}


/*		 class MTRX_FUNCTIONS_R 		  */
/*   functions with rvalue and str input  */

static matrix *MTRX_FUNCTIONS_R__create(char *a) {
	matrix *M = (matrix *) malloc(sizeof(matrix));

	int *size_A = parse_matrix_size(a);

	frac (*A)[size_A[1]] = parse_matrix(a);

	cpymtrx(size_A[1], size_A[0], A, M);
	M->height = size_A[0];
	M->width = size_A[1];

	return M;
}

static matrix *MTRX_FUNCTIONS_R__addition(char *a, char *b) {
	matrix *M = (matrix *) malloc(sizeof(matrix));

	int *size_A = parse_matrix_size(a);
	int *size_B = parse_matrix_size(b);

	function_assert(size_A[0] == size_B[0], 
		"Matrix A and B do not have the same height, addition requires identically sized matrices.");
	function_assert(size_A[1] == size_B[1], 
		"Matrix A and B do not have the same width, addition requires identically sized matrices.");

	frac (*A)[size_A[1]] = parse_matrix(a);
	frac (*B)[size_B[1]] = parse_matrix(b);

	a(A, size_A[0], size_A[1], B);

	cpymtrx(size_B[1], size_B[0], B, M);
	M->height = size_B[0];
	M->width = size_B[1];

	return M;
}

static matrix *MTRX_FUNCTIONS_R__subtraction(char *a, char *b) {
	matrix *M = (matrix *) malloc(sizeof(matrix));

	int *size_A = parse_matrix_size(a);
	int *size_B = parse_matrix_size(b);

	function_assert(size_A[0] == size_B[0], 
		"Matrix A and B do not have the same height, addition requires identically sized matrices.");
	function_assert(size_A[1] == size_B[1], 
		"Matrix A and B do not have the same width, addition requires identically sized matrices.");

	frac (*A)[size_A[1]] = parse_matrix(a);
	frac (*B)[size_B[1]] = parse_matrix(b);

	s(A, size_A[0], size_A[1], B);

	cpymtrx(size_B[1], size_B[0], B, M);
	M->height = size_B[0];
	M->width = size_B[1];

	return M;
}

static matrix *MTRX_FUNCTIONS_R__multiplication(char *a, char *b) {
	matrix *M = (matrix *) malloc(sizeof(matrix));

	int *size_A = parse_matrix_size(a);
	int *size_B = parse_matrix_size(b);

	function_assert(size_A[1] == size_B[0], 
		"Matrix A and B can not be multiplied, width of A must be equal to height of B.");

	frac (*A)[size_A[1]] = parse_matrix(a);
	frac (*B)[size_B[1]] = parse_matrix(b);

	frac _M[size_B[0]][size_B[1]];

	m(A, size_A[0], size_A[1], B, _M);

	cpymtrx(size_B[1], size_B[0], _M, M);
	M->height = size_B[0];
	M->width = size_B[1];

	return M;
}

static matrix *MTRX_FUNCTIONS_R__transpose(char *a) {
	matrix *M = (matrix *) malloc(sizeof(matrix));

	int *size_A = parse_matrix_size(a);

	frac (*A)[size_A[1]] = parse_matrix(a);

	frac _M[size_A[0]][size_A[1]];

	t(A, size_A[0], size_A[1], _M);

	cpymtrx(size_A[1], size_A[0], _M, M);
	M->height = size_A[0];
	M->width = size_A[1];

	return M;
}

static matrix *MTRX_FUNCTIONS_R__invert(char *a) {
	matrix *M = (matrix *) malloc(sizeof(matrix));

	int *size_A = parse_matrix_size(a);

	function_assert(size_A[1] == size_A[0], 
		"Matrix is not square.");

	frac (*A)[size_A[1]] = parse_matrix(a);

	frac _M[size_A[0]][size_A[1]];

	i(size_A[1], A, _M);

	cpymtrx(size_A[1], size_A[0], _M, M);
	M->height = size_A[0];
	M->width = size_A[1];

	return M;
}

static matrix *MTRX_FUNCTIONS_R__power(char *a, int n) {
	matrix *M = (matrix *) malloc(sizeof(matrix));

	int *size_A = parse_matrix_size(a);

	frac (*A)[size_A[1]] = parse_matrix(a);

	frac _M[size_A[0]][size_A[1]];

	p(size_A[1], A, _M, n);

	cpymtrx(size_A[1], size_A[0], _M, M);
	M->height = size_A[0];
	M->width = size_A[1];

	return M;
}

static int MTRX_FUNCTIONS_R__determinant(char *a) {
	int *size_A = parse_matrix_size(a);

	function_assert(size_A[1] == size_A[0], 
		"Matrix is not square.");

	frac (*A)[size_A[1]] = parse_matrix(a);

	frac det = {0,1,0.0};
	int base_state[size_A[1]];

	linear_row(base_state, size_A[1]);
	d(base_state, size_A[1], size_A[1], size_A[1], &det, A, factorial(size_A[1]), 1);

	return det.numerator / det.denominator;
}

/*		 class MTRX_FUNCTIONS_RAW 		  */
/*   functions with rvalue and raw input  */

static matrix *MTRX_FUNCTIONS_RAW__addition(matrix *a, matrix *b) {
	matrix *M = (matrix *) malloc(sizeof(matrix));

	a(a->Matrix, a->height, a->width, b->Matrix);

	cpymtrxstrct(b->width, b->height, b, M);
	M->height = b->height;
	M->width = b->width;

	return M;
}

static matrix *MTRX_FUNCTIONS_RAW__subtraction(matrix *a, matrix *b) {
	matrix *M = (matrix *) malloc(sizeof(matrix));

	s(a->Matrix, a->height, a->width, b->Matrix);

	cpymtrxstrct(b->width, b->height, b, M);
	M->height = b->height;
	M->width = b->width;

	return M;
}

static matrix *MTRX_FUNCTIONS_RAW__multiplication(matrix *a, matrix *b) {
	matrix *M = (matrix *) malloc(sizeof(matrix));

	frac _M[b->height][b->width];

	m(a->Matrix, a->height, a->width, b->Matrix, _M);

	cpymtrx(b->height, b->width, _M, M);
	M->height = b->height;
	M->width = b->width;

	return M;
}

static matrix *MTRX_FUNCTIONS_RAW__transpose(matrix *a) {
	matrix *M = (matrix *) malloc(sizeof(matrix));

	frac _M[a->height][a->width];

	t(a->Matrix, a->height, a->width, _M);

	cpymtrx(a->height, a->width, _M, M);
	M->height = a->height;
	M->width = a->width;

	return M;
}

// . . . 
// TODO: add invert, power and determinant.


/*			wrapper functions 			*/

/* without rvalue */
void add(char *a, char *b) {
	MTRX_FUNCTIONS_NO_R__addition(a, b);
}

void subtract(char *a, char *b) {
	MTRX_FUNCTIONS_NO_R__subtraction(a, b);
}

void mulitply(char *a, char *b) {
	MTRX_FUNCTIONS_NO_R__multiplication(a, b);
}

void transpose(char *a) {
	MTRX_FUNCTIONS_NO_R__transpose(a);
}

void invert(char *a) {
	MTRX_FUNCTIONS_NO_R__invert(a);
}

void determinant(char *a) {
	MTRX_FUNCTIONS_NO_R__determinant(a);
}

void topower(char *a, int n) {
	MTRX_FUNCTIONS_NO_R__power(a, n);
}

void show(matrix *m) {
/* visualize the matrix struct */
	pmatrixstruct(m, 1);
}

/* with rvalue */
matrix *create(char *s) {
	return MTRX_FUNCTIONS_R__create(s);
}

matrix *add_r(char *a, char *b) {
	return MTRX_FUNCTIONS_R__addition(a, b);
}

matrix *subtract_r(char *a, char *b) {
	return MTRX_FUNCTIONS_R__subtraction(a, b);
}

matrix *mulitply_r(char *a, char *b) {
	return MTRX_FUNCTIONS_R__multiplication(a, b);
}

matrix *transpose_r(char *a) {
	return MTRX_FUNCTIONS_R__transpose(a);
}

matrix *invert_r(char *a) {
	return MTRX_FUNCTIONS_R__invert(a);
}

int determinant_r(char *a) {
	return MTRX_FUNCTIONS_R__determinant(a);
}

matrix *topower_r(char *a, int n) {
	return MTRX_FUNCTIONS_R__power(a, n);
}

matrix *add_raw(matrix *a, matrix *b) {
	return MTRX_FUNCTIONS_RAW__addition(a, b);
}

matrix *subtract_raw(matrix *a, matrix *b) {
	return MTRX_FUNCTIONS_RAW__subtraction(a, b);
}

matrix *mulitply_raw(matrix *a, matrix *b) {
	return MTRX_FUNCTIONS_RAW__multiplication(a, b);
}

matrix *transpose_raw(matrix *a) {
	return MTRX_FUNCTIONS_RAW__transpose(a);
}
