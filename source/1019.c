/*
 * 直接在某位同学的坑爹程序上面改的，所以变量名有点奇怪
 */

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

long long int gcd(long long int a, long long int b){
    long long int t;
    while (b != 0){
        t = b;
        b = a % b;
        a = t;
    }
    return a;
}

int main(void)
{
    int *a, t, n, i;
    long long int x;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%d",&n);
        a = (int *)malloc(n * sizeof(int));
        for(i=0;i<n;i++)
        {
            scanf("%d",&a[i]);
        }
        x = a[0];
        for(i=1;i<n;i++)
        {
            
            x *= a[i] / gcd(a[i], x);
        }
        free(a);
        printf("%lld\n",x);
    }
    return 0;
}