#include <stdio.h>
#define MAXCOUNT 51

unsigned long long routeCount(unsigned int start, unsigned int end) {
	static unsigned long long counts[MAXCOUNT] = {1, 1};
	static unsigned int count = 2;
	if (end - start < count) return counts[end - start];
	for(;count <= MAXCOUNT && end - start >= count; count++)
		counts[count] = counts[count - 1] + counts[count - 2];
	return counts[end - start];
}

int main() {
	unsigned int n;
	scanf("%u", &n);
	while(n--) {
		unsigned int a, b;
		scanf("%u %u", &a, &b);
		printf("%llu\n", routeCount(a, b));
	}

	return 0;
}
