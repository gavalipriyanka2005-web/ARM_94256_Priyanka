#include<stdio.h>
unsigned char make_even_parity(unsigned char x)
{
int count=0;
for(int i=0;i<8;i++)
if(x&(1<<i))
count++;
if(count%2!=0)
x|=0x80;
return x;
}
int main()
{
unsigned char data=0x12;
printf("Result=0x%x",make_even_parity(data));
return 0;
}

