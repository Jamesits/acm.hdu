#include <stdio.h>
#include <string.h>

int hash[2000001];
int main(void)
{
	int a, b, c, d, sum, i, j, x;
	while (scanf("%d %d %d %d", &a, &b, &c, &d) != EOF)
	{
		if ((a>0 && b>0 && c>0 && d>0) || (a<0 && b<0 && c<0 && d<0))
		{
			printf("0\n");
			continue;
		}
		sum = 0;
		memset(hash, 0, sizeof(hash));
		for (i = 1; i <= 100; i++)
		{
			x = a*i*i;
			for (j = 1; j <= 100; j++)
			{
				hash[x + b*j*j + 1000000]++;
			}
		}
		for (i = 1; i <= 100; i++)
		{
			x = -c*i*i;
			for (j = 1; j <= 100; j++)
			{
				sum += hash[x - d*j*j + 1000000];
			}
		}
		printf("%d\n", sum * 16);
	}
	return 0;
}