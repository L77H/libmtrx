*** libmtrx ***

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
   
