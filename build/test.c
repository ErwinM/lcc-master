int result = 0;

int foo(int n) {
  int i;
  i = n + 4;
  return i;
}

int main() {
  int k;
  k = foo(2);
  k++;
  result = k;
  return 0;
}