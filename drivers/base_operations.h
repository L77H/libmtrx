/* base operation functions ported from libmtrx.c       *
 *  int power(const int x, const int n)                 *
 *  unsigned long long factorial(unsigned long long n)  */

int power(const int x, const int n) {
	int pow = 1;
	for (int i = 0; i < n; i++) {
		pow *= x;
	}
	return pow;
}

unsigned long long factorial(unsigned long long n) {
	if (n == 0) {
		return 1;
	} else {
		n *= factorial(n - 1);
	}
	return n;
}

#define swap(A, B) {int tmp = *A; *A = *B; *B = tmp;}
