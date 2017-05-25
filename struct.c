struct Sname {
	int i;
	int j;
	int k;
} globl_s;

struct Sname foo(struct Sname p){
	p.j = 1;
	return p;
}

int main() {
	struct Sname p;
	p = foo(p);
}