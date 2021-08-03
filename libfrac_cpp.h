
#include "drivers/matrix_obj_class.cpp"

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
