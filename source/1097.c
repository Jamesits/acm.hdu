/*
 * 删掉所有注释再提交，不然有可能编译出错。
 */

#include <stdio.h>

const int power_table[10][4] =
	{
		{0, 0, 0, 0},	// 0, 0, 0, 0
		{1, 1, 1, 1},	// 1, 1, 1, 1
		{6, 2, 4, 8},	// 2, 4, 8, 16
		{1, 3, 9, 7},	// 3, 9, 27, 81
		{6, 4, 6, 4},	// 4, 16, 64, 256
		{5, 5, 5, 5},	// 5, 25, 125, 625
		{6, 6, 6, 6},	// 6, 36, 216, 1296
		{1, 7, 9, 3},	// 7, 49, 343, 2401
		{6, 8, 4, 2},	// 8, 64, 512, 4096
		{1, 9, 1, 9},	// 9, 81, 729, 6561
	};

/*
int print_power_result_test()
{
	int i, j;
	for (i = 1; i <= 10; i++)
		{
			for (j = 0; j <= 9; j++)
				printf("%d ", (int)pow(i, j));
			printf("\n");
		}
	return 0;
}
*/

int main()
{
	unsigned int a, b;
	while(scanf("%u %u", &a, &b) != EOF)
		{
			a = a - a / 10 * 10;	// 取个位数
			if (0 == a && 0 == b)	// 0 ^ 0 无定义
				return 1;
			else if (0 == b)		// n ^ 0 当 n != 0 时为 1
				printf("1\n");
			else					// 	其余情况当然直接查表啦 ^o^
				printf("%d\n", power_table[a][b % 4]);
		}
	return 0;
}
