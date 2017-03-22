/* array tests - 2. static array, var idx
 * returns 5 in return
 */

int array[3] = {1,2,3};
int result = 0;

int foo(int n) {
	int i;
  i = array[n];
  return i;
}

int main() {
  int k;
  k = foo(2);
  k += 2;
	result = k;
  return k;
}