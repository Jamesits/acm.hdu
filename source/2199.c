/*
http://acm.hdu.edu.cn/showproblem.php?pid=2199

# Question: Can you solve this equation?

## Problem Description
Now,given the equation 8*x^4 + 7*x^3 + 2*x^2 + 3*x + 6 == Y,can you find its solution between 0 and 100;
Now please try your lucky.
 
## Input
The first line of the input contains an integer T(1<=T<=100) which means the number of test cases. Then T lines follow, each line has a real number Y (fabs(Y) <= 1e10);
 
## Output
For each test case, you should just output one real number(accurate up to 4 decimal places),which is the solution of the equation,or “No solution!”,if there is no solution for the equation between 0 and 100.
 
## Sample Input
2
100
-4
 
## Sample Output
1.6152
No solution!

Written by James Swineson. 2015-05-06
*/

#include <stdio.h>

/* #include <stdbool.h> */
#define bool _Bool
#define true 1
#define false 0

/* #include <math.h> */
#define fabs(X) ((X)>0 ? (X) : -(X))

/* 问题的参数：解范围和允许的误差 */
#define RANGE_MIN 0
#define RANGE_MAX 100
#define EPS 1e-4

double f(double x, double y) {
	/* 原函数求值 */
	return (8*x*x*x*x + 7*x*x*x + 2*x*x + 3*x + 6 - y);
}

double df(double x) {
	/* 原函数的导数 */
	return (32*x*x*x + 21*x*x + 4*x + 3);
}

double iterate_next_x(double last_x, double y) {
	/* 牛顿法迭代：x(n+1) = x(n) - f(x(n))/f'(x(n)) */
	return (last_x - f(last_x, y)/df(last_x));
}

bool has_solution_in_range(double lower_limit, double upper_limit, double y) {
	/* 判断在给定的范围内是否存在解 */
	/* f(x) 在 [0, 100] 单增，所以可以这样判断 */
	return (f(lower_limit, y)*f(upper_limit, y) < 0);
}

double guess_iterate_start_value(double lower_limit, double upper_limit, double y) {
	/* 计算迭代初值 x(0)。在找到更好的办法之前就设为 50 好了。 */
	return ((lower_limit + upper_limit) / 2);
}

bool is_acceptable_solution(double x, double y) {
	/* 检查当前迭代结果的误差是否小于给定误差 */
	return (fabs(f(x, y)) <= EPS);
}

bool solve(double y, double *solution) {
	/* 在找到符合题意的解时返回 true 并把解的数值赋给 *solution，反之返回 false（此时 *solution 的值未定义） */
	
	/* 检查指针 */
	if ( solution == NULL ) return (false);
	
	/* 检查输入值和边界条件 */
	if ( !has_solution_in_range(RANGE_MIN, RANGE_MAX, y) ) return (false);
	if ( is_acceptable_solution((RANGE_MIN), y) == (true) ) { *solution = (RANGE_MIN); return (true); }
	if ( is_acceptable_solution((RANGE_MAX), y) == (true) ) { *solution = (RANGE_MAX); return (true); }
	
	/* 迭代 */
	/* 注意迭代时中间值可能超出给定范围，暂时不做判断等迭代结束 */
	double current_x = guess_iterate_start_value((RANGE_MIN), (RANGE_MAX), y);
	while ( !is_acceptable_solution(current_x, y) ) {
		current_x = iterate_next_x(current_x, y);
	}
	
	/* 检查结果是否在给定范围内 */
	if ( current_x > (RANGE_MAX) || current_x < (RANGE_MIN) ) return (false);
	
	*solution = current_x;
	return (true);
}

int main(void) {
	unsigned int t; /* 重复次数 */
	scanf("%u", &t);
	
	while (t--) {
		double y;
		scanf("%lf", &y);
		double solution;
		if ( solve(y, &solution) == (true) ) {
			printf("%.4lf\n", solution);
		} else {
			puts("No solution!");
		}
	}
	
	return 0;
}