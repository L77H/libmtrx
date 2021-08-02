
#include "drivers/matrix_obj_class.cpp"


/* *																					   * *
 *																						     *
 *  	LIBMTRX CPP OBJECT CLASS															 *
 *																						     *												
 *  libmtrx allows to create a matrix object and manipulate it according to your needs. The  *
 *  below methods allow you to add, subtract, multiply, transpose, reduce, invert and raise  *
 *  to a power. All of these methods manipulate the matrix object in place.                  *
 *                                                                                           *									   
 *  Please read the below documentation before including and using libmtrx in your project.  *
 *  Following drivers are required: drivers/matrix_obj_class.cpp,                            *
 *  drivers/fractional_obj_class.cpp, drivers/base_operations.h                              *
 *  libmtrx_cpp.h is  intended  to  be used in  C++ and is incompatible  with C,  refer  to  *
 *  libmtrxf.h for the C version of libmtrx.                                                 *
 *                                                                                           *
 * example code:                                                                             *

 		// create matrices and vectors
 		matrix M1; int V1[6] = {1,2,3,4,5,6};
 		matrix M2; int V2[6] = {7,8,9,10,11,12};

 		// create and fill matrices
 		M1.construct(3, 2); M1.populate(V1); 
 		M2.construct(2, 3); M2.populate(V2);

 		// multiply M1 and M2
 		M1.multiply(&M2);

 		// redefine M1
 		M1.construct(3, 3); int V1[9] = {1,2,3,4,5,6,7,8,9};
 		M1.populate(V3); 

 		// invert M1 and raise to 3th power 
 		M1.invert();
 		M1.topower(3);

 *                                                                                          *
 * method specifications:                                                                   *
 *                                                                                          *
 * 		void matrix::construct(int h, int w)                                                *
 *			method used to sepcify the desired dimensions of the matrix.                    *
 *                                                                                          *
 *		void matrix::populate(const int v[])                                                *
 *			fill the before constructed (h x w) matrix with  the values  of the  patameter  *
 *			array v. v has to be of size h * w.                                             *
 *                                                                                          *
 *		void matrix::identity(void)                                                         *
 *			make an identity  matrix out  of the before constructed (h x w) matrix. Values  *
 *			not on the diagonal are not overwritten!                                        *
 *                                                                                          *
 *		matrix matrix::duplicate(void)                                                      *
 *			duplicate the matrix object into a new matrix object.                           *
 *                                                                                          *
 *		fraction matrix::*get(int h, int w)                                                 *
 *			get the value, as a fraction object, at position (h, w).                        *
 *                                                                                          *
 *		int matrix::add(matrix *A)                                                          *
 *			add matrix object A to the matrix. Returns 0 on success, -1 on failure.         *
 *                                                                                          *
 *		int matrix::subtract(matrix *A)	                                                    *
 *			subtract matrix object A from the matrix. Returns 0 on success, -1 on failure.  *
 *                                                                                          *
 *		int matrix::multiply(matrix *A)                                                     *
 *			mulitply matrix object A with the matrix. Returns 0 on success, -1 on failure.  *
 *                                                                                          *
 *		void matrix::multiply_n(int n)                                                      *
 *			multiply the matrix with an integer n.                                          *
 *                                                                                          *
 *		void matrix::multiply_f(fraction f)                                                 *
 *			multiply the matrix with a fraction object f.                                   *
 *                                                                                          *
 *		void matrix::transpose(void)                                                        *
 *			transpose the matrix.                                                           *
 *                                                                                          *
 *		fraction matrix::determinant()                                                      *
 *			calculate the determinant of the matrix. Returns the determinant as a fraction  *
 *			object.                                                                         *
 *                                                                                          *
 * 		void matrix::reduce(int w, int h)                                                   *
 *			reduce the matrix to (w - 1 x h - 1). Removes column at w and row at h.         *
 *                                                                                          *
 *		void matrix::invert(void)                                                           *
 *			invert the matrix if non 0 determinant otherwise  keep original  state of  the  *
 *			matrix (still performs majority of work).                                       *
 *                                                                                          *
 *		int matrix::is_identical(matrix *A)                                                 *
 *			are the matrix and matrix A identical? Returns bool.                            *
 *                                                                                          *
 *		int matrix::is_commutator(matrix *A)                                                *
 *			is matrix A a commutator of the matrix? Returns bool.                           *
 *                                                                                          *
 *		void matrix::topower(int n)                                                         *
 *			raise the matrix to power n.                                                    *
 *                                                                                          *
 *		void matrix::out(void)                                                              *
 *			print the matrix, usefull for debugging.                                        *
 * *																					  * */																						
