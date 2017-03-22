/* array tests - 1. static array, static idx */

int array[3] = {1,2,3};
int result = 0;

int foo(int n) {
	int i;
  i = array[0] + array[2];
  return i;
}

int main() {
  int k;
  k = foo(2);
  k++;
	result = k;
  return k;
}