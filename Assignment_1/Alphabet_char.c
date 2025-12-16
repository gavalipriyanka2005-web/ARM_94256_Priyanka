#include<stdio.h>
void checkChar(char ch)
{
if((ch >= 'A' && ch <= 'Z')|| (ch >= 'a' && ch <= 'z'))
printf("After XOR with 32 : %c\n",ch^32);
else
printf("Not an alphabet");
}
int main()
{
char c= 'A';
checkChar(c);
return 0;
}
