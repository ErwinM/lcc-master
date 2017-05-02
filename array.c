int result = 5;

int foo(int i) {
	int ar[3];
	ar[0] = 0xa;
	ar[1] = 0;
	ar[2] = 0xc;

	return ar[i];
}

int main() {
	result = foo(1);
	return 0;
}