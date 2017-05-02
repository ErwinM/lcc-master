int fib(int n) {
	if (n < 2) {
		return n;
  }
	return (fib(n-1) + fib(n-2));
}

int main() {
	int i = 0;
	return(fib(10));
}