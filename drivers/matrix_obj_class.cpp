#include <stdio.h>
#include <stdlib.h>
#include "fractional_obj_class.cpp"
#include "base_operations.h"

/* matrix object class providing  basic *
 * matrix operations. The matrix object *
 * is based on a  matrix  struct  which *
 * can be manipulated  using  the class *
 * methods.   Available methods:        *
 *		- construct(void)	*
 * 		- populate(v[])		*
 * 		- populate_frac(v[])	*
 * 		- identity(void)	*
 * 		- duplicate(void)	*
 *		- get(w, h)		*
 *		- out(void)		*
 *		- add(A)		*
 *		- subtract(A)		*
 *		- multiply(A)		*
 *		- mulitply_n(n)		*
 *		- mulitply_f(f)		*
 *		- transpose(void)	*
 *		- determinant(void)	*
 *		- reduce(h, w)		*
 *		- invert(void)		*
 *		- is_identical(A)	*
 *		- is_commutator(A)	*
 *		- topower(n)		*/


/* TODO: *
 * Update matrix_as_vector after every manipulation */


#define					MAX_MATRIX_VECTOR_SIZE	2560

typedef struct {
	int 	  			w; 		// width of M
	int 	  			h;		// height of M
	fraction 		      **M;		// matrix
} 	matrix_struct;

class matrix {
	private:

		matrix_struct 		*M;
		fraction 		matrix_as_vector[MAX_MATRIX_VECTOR_SIZE];
		fraction		det;

		matrix_struct *get_mstruct(int h, int w) {
			matrix_struct *m_tmp = (matrix_struct *) malloc(sizeof(matrix_struct));
			// matrix_struct *m_tmp = new matrix_struct; /* more type safe */
			m_tmp->h = h;
			m_tmp->w = w;
			m_tmp->M = new fraction *[h];
			for (int i = 0; i < h; i++) {
				m_tmp->M[i] = new fraction[w];
			}
			return m_tmp;
		}

		void copy(matrix_struct *tmp) {
			for (int i = 0; i < M->h; i++) {
				for (int j = 0; j < M->w; j++) {
					M->M[i][j].set(tmp->M[i][j].n, tmp->M[i][j].d);
					matrix_as_vector[k++].set(tmp->M[i][j].n, tmp->M[i][j].d);
				}
			} 
		}

		void lin_row(int *v, int n) {
		/* void linear_row(int *V, int n) ported from libmtrx.c */
			for (int i = 1; i < n + 1; i++) 
				v[i - 1] = i;
		}

		void d(int *v, const int n, const int s, const int x, const unsigned long long f, const short r) {
		/* void d(int *V, const int n, const int s, const int x, frac *D, const frac (*M)[x], const unsigned long long f, const short r) *
		 * ported from libmtrx.c 																										 */
			
			static int c = 0;
			if (r)
				c = 0;
			
			if (n == 1) {
				int sign = power(-1, c);
				fraction prod;
				prod.set(sign, 1);

				for (int i = 0; i < s; i++) {
					prod.multiply(&M->M[i][v[i] - 1]);
				}
				
				det.add(&prod);
				++c;

			} else {

				d(v, n - 1, s, x, f, 0);
				for (int i = 0; i < n - 1; i++) {

					if (n % 2 == 0) {
						swap(&v[i], &v[n-1]);
					} else {
						swap(&v[0], &v[n-1]);
					}

					d(v, n - 1, s, x, f, 0);
				}
			}
		}

		void m(void) {
		/* multiply by itself */
			matrix_struct *m_tmp = get_mstruct(M->h, M->w);
			fraction dot, f_tmp;
			for (int i = 0; i < M->h; i++) {
				for (int j = 0; j < M->h; j++) {
					dot.set(0, 1);
					for (int k = 0; k < M->w; k++) {
						f_tmp.set(M->M[i][k].n, M->M[k][j].d);
						f_tmp.multiply(&M->M[k][j]);
						dot.add(&f_tmp);
						f_tmp.set(0, 1);
					}
					m_tmp->M[i][j].set(dot.n, dot.d);
				}
			}
			copy(m_tmp);
		}

	public:

		int 			height;
		int 			width;

	 	matrix(void) {
	 	/* construct our matrix object */
			M = (matrix_struct *) malloc(sizeof(matrix_struct));
			//M = new matrix_struct; /* more type safe */
		}

		void construct(int h, int w) {
			M->M = new fraction *[h];
			for (int i = 0; i < h; i++) {
				M->M[i] = new fraction[w];
			}
			M->w = width = w;
			M->h = height = h;
		}

		void populate(const int v[]) {
		/* no sanity check! assumes that v[] has correct dimension */
			for (int i = 0, k = 0; i < M->h; i++) {
				for (int j = 0; j < M->w; j++) {
					M->M[i][j].set(v[k], 1);
					if (k < MAX_MATRIX_VECTOR_SIZE)
						matrix_as_vector[k].set(v[k], 1);
					k++;
				}
			}
		}

		void populate_frac(const fraction v[]) {
			for (int i = 0, k = 0; i < M->h; i++) {
				for (int j = 0; j < M->w; j++) {
					M->M[i][j].set(v[k].n, v[k].d);
					if (k < MAX_MATRIX_VECTOR_SIZE)
						matrix_as_vector[k].set(v[k].n, v[k].d);
					k++;
				}
			}
		}

		void identity(void) {
		/* make M an identity matrix fast, does not overwrite non diagonal values! */
			for (int i = 0; i < M->w; i++) {
				M->M[i][i].set(1, 1);
			}
		}

		matrix duplicate(void) {
			class matrix Mout;
			Mout.construct(M->h, M->w);
			//Mout.populate_frac(matrix_as_vector);
			for (int i = 0; i < M->h; i++) {
				for (int j = 0; j < M->w; j++) {
					Mout.M->M[i][j].set(M->M[i][j].n, M->M[i][j].d);
				}
			}
			return Mout;
		}

		fraction *get(int h, int w) {
		/* get element at position (h,w) */
			return &(M->M[h][w]);
		}

		int add(matrix *A) {
		/* add matrix A to current matrix object */
			if (!(A->width == M->w && A->height == M->h))
				return -1; /* addition failed */
			for (int i = 0; i < M->h; i++) {
				for (int j = 0; j < M->w; j++) {
					M->M[i][j].add(A->get(i, j));
				}
			}
			return 0;
		}

		int subtract(matrix *A) {
		/* subtract matrix A from current matrix object */
			if (!(A->width == M->w && A->height == M->h))
				return -1; /* subtraction failed */
			for (int i = 0; i < M->h; i++) {
				for (int j = 0; j < M->w; j++) {
					M->M[i][j].subtract(A->get(i, j));
				}
			}
			return 0;
		}

		void multiply(matrix *A) {
		/* multiply A with current matrix object */
			if (width == A->height) {
				matrix_struct *m_tmp = get_mstruct(height, A->width);
				fraction dot, f_tmp;
				for (int i = 0; i < M->h; i++) {
					for (int j = 0; j < A->width; j++) {
						dot.set(0, 1);
						for (int k = 0; k < M->w; k++) {
							f_tmp.set(M->M[i][k].n, M->M[i][k].d);
							f_tmp.multiply(A->get(k, j));
							dot.add(&f_tmp);
						}
						m_tmp->M[i][j].set(dot.n, dot.d);
					}
				}
				if (width != A->width || height != A->height) {
					construct(height, A->width);
				}
				copy(m_tmp);
			}
		}

		void multiply_n(int n) {
			fraction f;
			f.set(n, 1);
			for (int i = 0; i < M->h; i++) {
				for (int j = 0; j < M->w; j++) {
					M->M[i][j].multiply(&f);
					M->M[i][j].simplify();
				}
			}
		}

		void multiply_f(fraction f) {
			for (int i = 0; i < M->h; i++) {
				for (int j = 0; j < M->w; j++) {
					M->M[i][j].multiply(&f);
					M->M[i][j].simplify();
				}
			}
		}

		void transpose(void) {
		/* transpose matrix M */
			matrix_struct *m_tmp = get_mstruct(M->w, M->h);
			for (int i = 0; i < M->h; i++) {
				for (int j = 0; j < M->w; j++) {
					m_tmp->M[j][i].set(M->M[i][j].n, M->M[i][j].d);
				}
			} 
			construct(M->w, M->h);
			copy(m_tmp);
		}

		fraction determinant() {
			int v[M->w];
			lin_row(v, M->w);
			d(v, M->w, M->w, M->w, factorial(M->w), 1);
			return det;
		}

		void reduce(int w, int h) {
		/* void reduce(const int w, const frac (*M)[w], const int x, const int y, frac (*R)[w]) *
		 * ported from libmtrx.c . Indexation for w and h starts at 0.							*
		 *                                           OPTIMIZED VERSION                                                  */

			matrix_struct *m_tmp = get_mstruct(M->h, M->w);

			int offseti = 0, offsetj;
			for (int i = 0; i < M->w; i++) {
				if (i == h) {
					offseti = 1;
					continue;
				}

				offsetj = 0;
				for (int j = 0; j < M->w; j++) {
					if (j == w) {
						offsetj = 1;
						continue;
					}

					m_tmp->M[i - offseti][j - offsetj].set(M->M[i][j].n, M->M[i][j].d);
				}
			}
			copy(m_tmp);
			M->w--, width--;
			M->h--, height--;
		}

		void invert(void) {
		/* void i(const int w, const frac (*M)[w], frac (*R)[w]) ported from libmtrx.c */

			int vfull[width], vreduced[width - 1];
			fraction det;
			matrix H, T;

			H.construct(M->h, M->w);
			T.construct(M->h, M->w);

			for (int i = 0; i < M->w; i++) {
				for (int j = 0; j < M->w; j++) {
					H = duplicate();

					H.reduce(i, j);

					det = H.determinant();

					T.M->M[i][j].set(power(-1, i + j) * det.n, det.d);
				}
			}

			det = determinant();
			if (det.n != 0) {
				det.flip();

				T.multiply_f(det);
				copy(T.M);
			}
		}

		int is_identical(matrix *A) {
			if (width != A->width || height != A->height)
				return 0;
			for (int i = 0; i < M->h; i++) {
				for (int j = 0; j < M->w; j++) {
					if (M->M[i][j].n != A->M->M[i][j].n || M->M[i][j].d != A->M->M[i][j].d)
						return 0;
				}
			}
			return 1;
		}

		int is_commutator(matrix *A) {
		/* int commutator(int w, frac (*A)[w], frac (*B)[w]) ported from libmtrx.c */

			matrix M1 = duplicate();

			M1.multiply(A);
			A->m();

			if (M1.is_identical(A))
				return 1;
			return 0;
		}

		void topower(int n) {
		/* raise M to power n */

			matrix Mcopy = duplicate();

			for (int i = 0; i < n - 1; i++) {
				multiply(&Mcopy);
			}
		}

		void out(void) {
			for (int i = 0; i < M->h; i++) {
				printf("%c", '[');
				for (int j = 0; j < M->w; j++) {
					M->M[i][j].simplify();
					if (M->M[i][j].d == 1 || M->M[i][j].d == -1)
						printf(" %ld ", (M->M[i][j].d == -1) ? M->M[i][j].n * -1 : M->M[i][j].n);
					else
						printf(" %ld/%ld ", (M->M[i][j].d < 0) ? M->M[i][j].n * -1 : M->M[i][j].n, (M->M[i][j].d < 0) ? M->M[i][j].d * -1 : M->M[i][j].d);
				}
				printf("%c\n", ']');
			}
		}
};


// int main() {

// 	matrix M1;
// 	matrix M2;

// 	M1.construct(2,2);
// 	M2.construct(2,2);
// 	int v[9] = {1,2,3,4,9,6,7,8,9};
// 	int v1[25] = {1,6,6,0,8,4,7,3,8,8,5,4,6,9,7,7,1,1,3,7,2,7,5,5,6};
// 	int v2[4] = {1,2,3,4};
// 	int v3[4] = {1,0,0,1};

// 	M1.populate(v2);
// 	M2.populate(v3);

// 	//int r = M1.add(&M2);
// 	// printf("%d\n", r);

// 	//M1.transpose();
// 	//M1.multiply(&M2);

// 	// fraction d = M1.determinant();
// 	// printf("det:\n");
// 	// d.out();

// 	//M1.reduce(2,2);
// 	//M1.out();

// 	M1.topower(8);

// 	M1.out();
// 	M2.out();

// 	printf("%d\n", M2.is_commutator(&M1));


// 	//M2.invert();

// 	//M2.out();

// 	return 0;
// }
