#include <limits.h>
#include <stdio.h>

void func(unsigned long x) {
	printf("%lu\n", x);
}

int main() {
	func(-1);
}
