
/* 									*
 *		header code for libmtrx		*/

struct true_value {
	long int numerator;
	long int denominator;
	long double floatpoint;
} true_value_default = {0, 1, 0.0};

typedef struct true_value frac;

#define max(A, B) (A > B) ? A : B

static short nlength(int n) {
	short i = 0;
	if (n < 0) {
		n *= -1;
		i++;
	}
	do {
		n /= 10;
		i++;
	} while (n > 0);
	return i;
}

void printfrac(const frac f) {
	short taps = 10;
	short maxdepth;
	if (f.denominator == 1 || f.numerator == 0) {
		maxdepth = max(10 - nlength(f.numerator), 0);
		for (short i = 0; i < max(10 - nlength(f.numerator), 0); i++) {
			printf(" ");
		}
		printf("%ld", f.numerator);
	} else {
		maxdepth = max(10 - (nlength(f.numerator) + nlength(f.denominator) + 1), 0);
		for (short i = 0; i < maxdepth; i++) {
			printf(" ");
		}
		printf("%ld/%ld", (f.denominator < 0) ? f.numerator * -1 : f.numerator, 
				  (f.denominator < 0) ? f.denominator * -1 : f.denominator);
	}
}

static long int GCD(long int n, long int d) {
	if (n == 0) 
		return d;
	return GCD(d % n, n);
}

void simplify(frac *f) {
	long int gcd = GCD(f->numerator, f->denominator);
	f->numerator /= gcd;
	f->denominator /= gcd;
}

void function_assert(int condition, char *s) {
	if (!condition) {
		printf("[ASSERT] %s\n", s);
		exit(1);
	}
}

static int is_int(char c) {
	return c > 47 && c < 58;
}

int *parse_matrix_size(char *s) {

	unsigned short l1, l2, wdone;
	int w, h;
	l1 = l2 = wdone = 0;
	w = h = 1;

	int *pair = (int *) malloc(sizeof(int)*2);

	for (int i = 0; *s != '\0'; i++, s++) {

		if (*s == '{') {
			if (!l1)
				l1 = 1;
			else if (!l2)
				l2 = 1;
			continue;
		}

		if (*s == '}') {
			if (l2) {
				l2 = 0;
				if (!wdone)
					wdone = 1;
			} else if (l1)
				l1 = 0;
			continue;
		}

		if (*s == ',') {
			if (l2 && !wdone)
				w++;
			else if (l1 && !l2)
				h++;
		}
	}

	pair[0] = h;
	pair[1] = w;

	return pair;
}

void parse_matrix_string(char *s, int w, frac M[][w]) {
/* parse a matrix string of the following format: 			*
 * {{x, x, ..., x}, {x, x, ..., x}, ..., {x, x, ..., x}}	*
 * and put the result in M, floating  points  are 			*
 * not yet supported. TODO: add floating  points!			*/

	unsigned short l1, l2, denom;
	l1 = l2 = denom = 0;

	for (int x = 0, y = 0; *s != '\0'; s++) {
		if (*s == ' ')
			continue;

		if (*s == '{') {
			if (!l1)
				l1 = 1;
			else if (!l2)
				l2 = 1;
			continue;
		}

		if (*s == '}') {
			if (l2) 
				l2 = 0;
			else if (l1)
				l1 = 0;

			if (denom)
				denom = 0;
			continue;
		}

		if (*s == ',') {
			if (l2)
				x++;
			else {
				x = 0;
				y++;
			}

			if (denom)
				denom = 0;
			continue;
		}

		if (*s == '/') {
			denom = 1;
			continue;
		}

		function_assert(is_int(*s), "unhandled char reached in parse_matrix.");

		if (!denom)
			M[y][x].numerator = 0;
		else if (denom)
			M[y][x].denominator = 0;

		while (is_int(*s)) {
			if (!denom) {
				M[y][x].numerator *= 10;
				M[y][x].numerator += *s - '0';
				M[y][x].denominator = 1;
			} else if (denom) {
				M[y][x].denominator *= 10;
				M[y][x].denominator += *s - '0';	
			}
			s++;
		}
		s--;
	}
}

frac (*parse_matrix(char *s))[] {
/* parse a matrix string of the following format: 			*
 * {{x, x, ..., x}, {x, x, ..., x}, ..., {x, x, ..., x}}	*
 * returning a pointer  to a new  frac  2d array 			*/

/* floating points are not yet  supported (TODO)!			*
 * iow x from above ex must  be ints or fractions			*/

	int *size = parse_matrix_size(s);

	frac (*M)[size[1]] = (frac (*)[size[1]]) malloc(sizeof(frac[size[0]][size[1]]));

	parse_matrix_string(s, size[1], M);

	return M;
}
