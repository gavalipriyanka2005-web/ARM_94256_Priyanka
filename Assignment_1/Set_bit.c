#include<stdio.h>
#include<stdint.h>
int main(void)
{
uint8_t reg=0x2A;
int bit=4,i;
if((reg &  (1<<4)) ==0 )
{
reg = reg | (1<<4);
}
else
{
reg = reg;
}
printf("Hex:0x%02x\n",reg);
printf("Binary:");
for(int i=7;i>=0;i--)
printf("%d",(reg>>i) & 1);
}
