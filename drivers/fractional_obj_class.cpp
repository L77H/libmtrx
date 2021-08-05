#ifndef _STDIO_H
	#include <stdio.h>
#endif
#ifndef _STDLIB_H
	#include <stdlib.h>
#endif

/* very basic fractional number handling *
 * class. For C++ projects.              *
 * Available methods:                    *
 *		- set(num, denom)        *	
 *		- decimal(void)          *
 *		- gcd(void)              *
 *		- simplify(void)         *
 *		- add(f)         	 *
 *		- subtract(f)		 *
 *		- multiply(f)         	 *
 *		- flip(void)         	 *
 *		- out(void)              */

typedef struct {
	long int 				numerator;
	long int 				denominator;
} fraction_struct;

class fraction {
	private:

		fraction_struct 	*frac;

		long int GCD(long int n, long int d) {
			if (n == 0) 
				return d;
			return GCD(d % n, n);
		}

	public:

		long int 			d; 		// denominator
		long int 			n; 		// numerator
		long double			dec;	        // decimal

		fraction(int num = 0, int denom = 1) {
		// allows for fraction v[2] = {fraction(1,2), fraction(1,3)}
			frac = (fraction_struct *) malloc(sizeof(fraction_struct));
			frac->numerator = n = num;
			frac->denominator = d = denom;
			dec = 0.0;
		}

		void set(long int num, long int denom) {
			frac->numerator = n = num;
			frac->denominator = d = denom;
			dec = (long double) num / denom; 
		}

		long double decimal(void) {
			if (dec == 0.0) 
				dec = (long double) frac->numerator / frac->denominator;
			return dec;
		}
	
		void flip(void) {
			long int tmp = frac->denominator;
			frac->denominator = frac->numerator;
			frac->numerator = tmp;
		}

		long int gcd(void) {
			return GCD(frac->numerator, frac->denominator);
		}

		void simplify(void) {
			long int g = GCD(frac->numerator, frac->denominator);
			set(frac->numerator / g, frac->denominator / g);
		}
	
		void add(fraction *f) {
			set(frac->numerator * f->frac->denominator + f->frac->numerator * frac->denominator, 
						frac->denominator *= f->frac->denominator);

		}

		void subtract(fraction *f) {
			set(frac->numerator * f->frac->denominator - f->frac->numerator * frac->denominator, 
						frac->denominator *= f->frac->denominator);	
		}

		void multiply(fraction *f) {
			set(frac->numerator * f->frac->numerator, frac->denominator * f->frac->denominator);
		}

		void out(void) {
			if (d == 1) 
				printf("%ld\n%Lf\n", n, dec);
			else
				printf("%ld/%ld\n%Lf\n", (d < 0) ? n * -1 : n, (d < 0) ? d * -1 : d, dec);
		}
};
