int con = 3;

int foo(int n) {
  int i;
  i = n + con;
  return i;
}

int main() {
  int k;
  k = foo(2);
  return k;
}