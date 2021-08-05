```
*** libmtrx ***

 ** documentation **
  * version 290721 *
  
  * inlcude libmtrxf.h into your project to make use of the functions below *
  
 ** high level functions **
 
  * print only functions, input; string formatted matrix *
  
   void add(char *a, char *b) 
   void subtract(char *a, char *b)
   void mulitply(char *a, char *b)
   void transpose(char *a)
   void invert(char *a)
   void determinant(char *a)
   void topower(char *a, int n)
   void show(matrix *m)
   
  * functions which return a 'matrix' object, input; string formatted matrix *
 
   matrix *create(char *s)
   matrix *add_r(char *a, char *b)
   matrix *subtract_r(char *a, char *b)
   matrix *mulitply_r(char *a, char *b)
   matrix *transpose_r(char *a)
   matrix *invert_r(char *a) 
   int determinant_r(char *a)
   matrix *topower_r(char *a, int n)
  
  * functions which return a 'matrix' object, input; 'matrix' object *
  
   matrix *add_raw(matrix *a, matrix *b)
   matrix *subtract_raw(matrix *a, matrix *b)
   matrix *mulitply_raw(matrix *a, matrix *b)
   matrix *transpose_raw(matrix *a)
   matrix *invert_raw(matrix *a)
   matrix *topower_raw(matrix *a, int n)
   int determinant_raw(matrix *a)
  
  
 ** driver functions **

 ** determinant **
  * calculate  square  matrix  determinant  using  Leibniz method *
  
   void d(int *V, const int n, const int s, const int x, frac *D, const frac M[][x], const unsigned long long f, const short r)
   
    - V: changing permutation vector 
    - n: changing vector length	
    - s: initial vector length
    - x: real width of M 
    - D: changing determinant value
    - M: matrix	
    - f: factorial of s
    - r: reset c and D to 0 if true
    
 ** invert **
  * invert any non singular matrix with adjugated matrix *
  
   void i(const int w, const frac M[][w], frac R[][w])
   
    - w: width/height of M 				 	
    - M: matrix to invert 				
    - R: resulting matrix		
    
   int is_invertable(const int w, const frac M[][w])
    
    - w: width of M
    - M: matrix
    
 ** power **
  * raise raise matrix M to power of n *
  
   void p(const int w, frac M[][w], frac R[][w], int n)
   
    - w: width and height of M 			
    - M: matrix to raise to power 			
    - R: resulting matrix				
    - n: power to raise to				
  
 ** reduce **
  * create reduced matrices for calculation of Minors and Cofactors *
  
   void reduce(const int w, const frac M[][w], const int x, const int y, frac R[][w])
    
    - w: width of M 				 	
    - M: matrix to reduce 				
    - x: row to remove 					
    - y: column to remove 				
    - R: resulting matrix			
    
 ** commuting **
  * check if matrix A and B are commute *
  
   int commutator(int w, frac A[][w], frac B[][w])
   
    - w: width/height of A or B
    - A: matrix
    - B: matrix
    
 ** addition **
  * add matrix A and B *
  
   #define a(A, y, x, B)
   
 ** multiplication **
  * multiply matrix A and B, result in C*
  
   #define m(A, y, x, B, C)
   
  * multiply matrix A with n *
  
   #define mn(A, x, y, n)
   
 ** transposition **
  * transpose matrix A, result in C *
  
   #define t(A, x, y, C)
   
```


```
/* *                                                                                       * *
 *                                                                                           *
 *   LIBFRAC CPP OBJECT CLASS                                                                *
 *                                                                                           *
 *  libfrac allows to work with fraction types. The core struct consists of  2 long int for  *
 *  numerator and denominator, and one long double for the decimal value.                    *
 *                                                                                           *
 *  Please read the below documentation before including and using libfrac in your project.  *
 *  Following drivers are required: drivers/fractional_obj_class.cpp,                        *
 *  libfrac_cpp.h is intended to be used in C++ and is incompatible with C.                  *
 *                                                                                           *
 * example code:                                                                             *
 		// create fraction
 		fraction F1;
 		fraction F2;
 		// set the fraction
 		F1.set(2, 3);
 		F2.set(15, 60);
 		// simplify F2 and add it to F1
 		F2.simplify();
 		F1.add(&F2);
 *                                                                                           *
 * method specifications:                                                                    *
 *                                                                                           *
 *   void fraction::set(long int num, long int denom)                                        *
 *     method used to set numerator value num and denominator value denom.                   *
 *                                                                                           *
 *   void fraction::flip(void)                                                               *
 *      switch denominator and numerator value in place.                                     *
 *                                                                                           *
 *   long double fraction::decimal(void)                                                     *
 *      returns the decimal value of the fraction.                                           *
 *                                                                                           *
 *   long int fraction::gcd(void)                                                            *
 *      returns the greatest common denominator.                                             *
 *                                                                                           *
 *   void fraction::simplify(void)                                                           *
 *      simplify the fraction using GCD.                                                     *
 *                                                                                           *
 *   void fraction::add(fraction *f)                                                         *
 *      add fraction object f to the fraction.                                               *
 *                                                                                           *
 *   void fraction::subtract(fraction *f)                                                    * 
 *      subtract fraction object f from the fraction.                                        *
 *                                                                                           *
 *   void fraction::multiply(fraction *f)                                                    *
 *      mulitply fraction object f with the fraction.                                        *
 *                                                                                           *
 *   void fraction::out(void)                                                                *
 *      print the fraction and decimal value, usefull for debugging.                         *
 * *                                                                                       * */	
```


```
/* *                                                                                       * *
 *                                                                                           *
 *   LIBMTRX CPP OBJECT CLASS                                                                *
 *                                                                                           *												
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
 *                                                                                           *
 * method specifications:                                                                    *
 *                                                                                           *
 *   void matrix::construct(int h, int w)                                                    *
 *     method used to sepcify the desired dimensions of the matrix.                          *
 *                                                                                           *
 *   void matrix::populate(const int v[])                                                    *
 *      fill the before constructed (h x w) matrix with  the values  of the  patameter       *
 *      array v. v has to be of size h * w.                                                  *
 *                                                                                           *
 *   void matrix::identity(void)                                                             *
 *      make an identity  matrix out  of the before constructed (h x w) matrix. Values       *
 *      not on the diagonal are not overwritten!                                             *
 *                                                                                           *
 *   matrix matrix::duplicate(void)                                                          *
 *      duplicate the matrix object into a new matrix object.                                *
 *                                                                                           *
 *   fraction matrix::*get(int h, int w)                                                     *
 *      get the value, as a fraction object, at position (h, w).                             *
 *                                                                                           *
 *   int matrix::add(matrix *A)                                                              *
 *      add matrix object A to the matrix. Returns 0 on success, -1 on failure.              *
 *                                                                                           *
 *   int matrix::subtract(matrix *A)                                                         *
 *      subtract matrix object A from the matrix. Returns 0 on success, -1 on failure.       *
 *                                                                                           *
 *   int matrix::multiply(matrix *A)                                                         *
 *      mulitply matrix object A with the matrix. Returns 0 on success, -1 on failure.       *
 *                                                                                           * 
 *   void matrix::multiply_n(int n)                                                          *
 *      multiply the matrix with an integer n.                                               *
 *                                                                                           *
 *   void matrix::multiply_f(fraction f)                                                     *
 *      multiply the matrix with a fraction object f.                                        *
 *                                                                                           *
 *   void matrix::transpose(void)                                                            *
 *      transpose the matrix.                                                                *
 *                                                                                           *
 *   fraction matrix::determinant()                                                          *
 *      calculate the determinant of the matrix. Returns the determinant as a fraction       *   
 *      object.                                                                              *
 *                                                                                           *
 *   void matrix::reduce(int w, int h)                                                       *
 *      reduce the matrix to (w - 1 x h - 1). Removes column at w and row at h.              *
 *                                                                                           *
 *   void matrix::invert(void)                                                               *
 *      invert the matrix if non 0 determinant otherwise  keep original  state of  the       *
 *      matrix (still performs majority of work).                                            *
 *                                                                                           *
 *   int matrix::is_identical(matrix *A)                                                     *
 *      are the matrix and matrix A identical? Returns bool.                                 * 
 *                                                                                           *
 *   int matrix::is_commutator(matrix *A)                                                    *
 *      is matrix A a commutator of the matrix? Returns bool.                                *
 *                                                                                           *
 *   void matrix::topower(int n)                                                             *
 *      raise the matrix to power n.                                                         *
 *                                                                                           *
 *   void matrix::out(void)                                                                  *
 *      print the matrix, usefull for debugging.                                             *
 * *                                                                                       * */	
 ```
