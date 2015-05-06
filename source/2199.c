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

/* problem config */
#define RANGE_MIN 0.0
#define RANGE_MAX 100.0
#define EPS 1e-4

double fabs(double x) {
	/* abs */
	return (x>0 ? x : -x);
}

double f(double x, double y) {
	/* Original function */
	return (8*x*x*x*x + 7*x*x*x + 2*x*x + 3*x + 6 - y);
}

double df(double x) {
	/* The directive of original function */
	return (32*x*x*x + 21*x*x + 4*x + 3);
}

double iterate_next_x(double last_x, double y) {
	/* iterator based on Newton's method */
	return (last_x - f(last_x, y)/df(last_x));
}

bool has_solution_in_range(double lower_limit, double upper_limit, double y) {
	/* Since f'(x)>0 in 0<x<100, we can safely assume this. */
	return (f(lower_limit, y)*f(upper_limit, y) < 0);
}

double guess_iterate_start_value(double lower_limit, double upper_limit, double y) {
	/* It will always be 50 before I find a better way */
	return ((lower_limit + upper_limit) / 2);
}

bool is_acceptable_solution(double x, double y) {
	return (fabs(f(x, y)) <= EPS);
}

bool solve(double y, double *solution) {
	/* returns if there is an solution */
	/* check args */
	if ( solution == NULL ) return (false);
	
	/* check input value border */
	if ( !has_solution_in_range(RANGE_MIN, RANGE_MAX, y) ) return (false);
	if ( is_acceptable_solution((RANGE_MIN), y) == true ) { *solution = (RANGE_MIN); return (true); }
	if ( is_acceptable_solution((RANGE_MAX), y) == true ) { *solution = (RANGE_MAX); return (true); }
	
	/* iteration */
	double current_x = guess_iterate_start_value((RANGE_MIN), (RANGE_MAX), y);
	while ( !is_acceptable_solution(current_x, y) ) {
		current_x = iterate_next_x(current_x, y);
	}
	
	/* check result border */
	if ( current_x > (RANGE_MAX) || current_x < (RANGE_MIN) ) return (false);
	
	*solution = current_x;
	return (true);
}

int main(void) {
	unsigned int t; /* repeat times */
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