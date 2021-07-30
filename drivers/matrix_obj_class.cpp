#include <stdio.h>
#include <stdlib.h>
#include "fractional_obj_class.cpp"

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
 * add methods: determinant, invert and power 		*
 * add support for: fractional numbers          > DONE  	*/

#define					MAX_MATRIX_VECTOR_SIZE	2560

typedef struct {
	int 	  			w; 		// width of M
	int 	  			h;		// height of M
	fraction 		      **M;		// matrix
} 	matrix_struct;

class matrix {
	private:

		matrix_struct 		*M;
		int 			matrix_as_vector[MAX_MATRIX_VECTOR_SIZE];

		matrix_struct *get_mstruct(void) {
			matrix_struct *m_tmp = (matrix_struct *) malloc(sizeof(matrix_struct));
			m_tmp->M = new fraction *[M->h];
			for (int i = 0; i < M->h; i++) {
				m_tmp->M[i] = new fraction[M->w];
			}
			return m_tmp;
		}

		void copy(matrix_struct *tmp) {
			for (int i = 0; i < M->w; i++) {
				for (int j = 0; j < M->h; j++) {
					M->M[i][j].set(tmp->M[i][j].n, tmp->M[i][j].d);
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
			M->M = new fraction *[h];
			for (int i = 0; i < h; i++) {
				M->M[i] = new fraction[w];
			}
			M->w = width = w;
			M->h = height = h;
		}

		void populate(int v[]) {
		/* no sanity check! assumes that v[] has correct dimension */
			for (int i = 0, k = 0; i < M->h; i++) {
				for (int j = 0; j < M->w; j++) {
					M->M[i][j].set(v[k], 1);
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
			matrix_struct *m_tmp = get_mstruct();
			fraction dot, f_tmp;
			for (int i = 0; i < M->h; i++) {
				for (int j = 0; j < M->h; j++) {
					dot.set(0, 1);
					for (int k = 0; k < M->w; k++) {
						f_tmp.set(M->M[i][k].n, M->M[i][k].d);
						f_tmp.multiply(A->get(k, j));
						dot.add(&f_tmp);
						f_tmp.set(0, 1);
					}
					m_tmp->M[i][j].set(dot.n, dot.d);
				}
			}
			copy(m_tmp);
		}

		void multiply_n(int n) {
			fraction f;
			f.set(n, 1);
			for (int i = 0; i < M->h; i++) {
				for (int j = 0; j < M->w; j++) {
					M->M[i][j].multiply(&f);
				}
			}
		}

		void transpose(void) {
		/* transpose matrix M */
			matrix_struct *m_tmp = get_mstruct();
			for (int i = 0; i < M->w; i++) {
				for (int j = 0; j < M->h; j++) {
					m_tmp->M[j][i].set(M->M[i][j].n, M->M[i][j].d);
				}
			} 
			copy(m_tmp);
		}

		void out(void) {
			for (int i = 0; i < M->h; i++) {
				printf("%c", '[');
				for (int j = 0; j < M->w; j++) {
					if (M->M[i][j].d == 1)
						printf(" %ld ", M->M[i][j].n);
					else
						printf(" %ld/%ld ", M->M[i][j].n, M->M[i][j].d);
				}
				printf("%c\n", ']');
			}
		}
};


int main() {

	/* test and driver code */
	matrix M1;
	matrix M2;

	M1.construct(3, 3);
	M2.construct(3, 3);
	int v[9] = {1,2,3,4,5,6,7,8,9};

	M1.populate(v);
	M2.populate(v);

	//int r = M1.add(&M2);
	// printf("%d\n", r);

	//M1.transpose();
	M1.multiply(&M2);

	M1.out();

	return 0;
}
