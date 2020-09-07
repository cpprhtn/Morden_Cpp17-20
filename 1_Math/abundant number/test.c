#include <stdio.h>
int main()
{
    int x, y, z, k, sum, mok;
    scanf("%d %d %d %d",&x,&y,&z,&k);
    sum = (y/k) * (z/k);
    mok = x > sum ? sum : x;
    printf("%d",mok);
}