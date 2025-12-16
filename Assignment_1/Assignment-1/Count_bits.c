#include<stdio.h>
int countsetbits(int n)
{
int count=0;
while(n>0)
{
count+=n & 1;
n=n>>1;
}
return count;
}
int main()
{
int num=13;
printf("Number of 1 bits:%d",countsetbits(num));
return 0;
}
