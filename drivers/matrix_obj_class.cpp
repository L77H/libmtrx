#include <stdio.h>
#include <stdlib.h>

/* matrix object class providing  basic *
 * matrix operations. The matrix object *
 * is based on a  matrix  struct  which *
 * can be manipulated  using  the class *
 * methods.   Available methods:        *
 *		- construct(void)	*
 * 		- populate(v[])		*
 * 		- duplicate(void)	*
 *		- get(w, h)		*
 *		- out(void)		*
 *		- add(A)		*
 *		- subtract(A)		*
 *		- multiply(A)		*
 *		- mulitply_n(n)		*
 *		- transpose(void)	*/

/* TODO:
 * add methods: determinant, invert and power *
 * add support for: fractional numbers        */

#define					  MAX_MATRIX_VECTOR_SIZE	2560

typedef struct {
	int 	  			  w; 		// width of M
	int 	  			  h;		// height of M
	int 			        **M;		// matrix
} 	matrix_struct;

class matrix {
	private:

		matrix_struct 	        *M;
		int 			matrix_as_vector[MAX_MATRIX_VECTOR_SIZE];

		matrix_struct *get_mstruct(void) {
			matrix_struct *m_tmp = (matrix_struct *) malloc(sizeof(matrix_struct));
			m_tmp->M = new int *[M->h];
			for (int i = 0; i < M->h; i++) {
				m_tmp->M[i] = new int[M->w];
			}
			return m_tmp;
		}

		void copy(matrix_struct *tmp) {
			for (int i = 0; i < M->w; i++) {
				for (int j = 0; j < M->h; j++) {
					M->M[i][j] = tmp->M[i][j];
				}
			} 
		}

	public:

		int 			height;
		int 			width;

	 	matrix(void) {
	 	/* construct our matrix object */
			M = (matrix_struct *) malloc(sizeof(matrix_struct));
		}

		void construct(int h, int w) {
			M->M = new int *[h];
			for (int i = 0; i < h; i++) {
				M->M[i] = new int[w];
			}
			M->w = width = w;
			M->h = height = h;
		}

		void populate(int v[]) {
		/* no sanity check! assumes that v[] has correct dimension */
			for (int i = 0, k = 0; i < M->h; i++) {
				for (int j = 0; j < M->w; j++) {
					M->M[i][j] = v[k];
					if (k < MAX_MATRIX_VECTOR_SIZE)
						matrix_as_vector[k] = v[k];
					k++;
				}
			}
		}

		matrix duplicate(void) {
			class matrix Mout;
			Mout.construct(M->h, M->w);
			Mout.populate(matrix_as_vector);
			return Mout;
		}

		int get(int h, int w) {
		/* get element at position (h,w) */
			return M->M[h][w];
		}

		int add(matrix *A) {
		/* add matrix A to current matrix object */
			if (!(A->width == M->w && A->height == M->h))
				return -1; /* addition failed */
			for (int i = 0; i < M->h; i++) {
				for (int j = 0; j < M->w; j++) {
					M->M[i][j] += A->get(i, j);
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
					M->M[i][j] -= A->get(i, j);
				}
			}
			return 0;
		}

		void multiply(matrix *A) {
			matrix_struct *m_tmp = get_mstruct();
			long int dot;
			for (int i = 0; i < M->h; i++) {
				for (int j = 0; j < M->h; j++) {
					dot = 0;
					for (int k = 0; k < M->w; k++) {
						dot += M->M[i][k] * A->get(k, j);
					}
					m_tmp->M[i][j] = dot;
				}
			}
			copy(m_tmp);
		}

		void multiply_n(int n) {
			for (int i = 0; i < M->h; i++) {
				for (int j = 0; j < M->w; j++) {
					M->M[i][j] *= n;
				}
			}
		}

		void transpose(void) {
		/* transpose matrix M */
			matrix_struct *m_tmp = get_mstruct();
			for (int i = 0; i < M->w; i++) {
				for (int j = 0; j < M->h; j++) {
					m_tmp->M[j][i] = M->M[i][j];
				}
			} 
			copy(m_tmp);
		}

		void out(void) {
			for (int i = 0; i < M->h; i++) {
				printf("%c", '[');
				for (int j = 0; j < M->w; j++) {
					printf(" %d ", M->M[i][j]);
				}
				printf("%c\n", ']');
			}
		}
};


int main() {

    /* test and driver code */
	class matrix matrix;
	class matrix M2;

	matrix.construct(3, 3);
	M2.construct(3, 3);
	int v[9] = {1,2,3,4,5,6,7,8,9};

	matrix.populate(v);
	M2.populate(v);

	// int r = matrix.add(&M2);
	// printf("%d\n", r);

	matrix.transpose();
	matrix.multiply(&M2);

	matrix.out();

	return 0;
}
