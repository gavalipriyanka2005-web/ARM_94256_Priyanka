#include<stdio.h>
#include<stdint.h>
int main(void)
{
uint8_t value = 5;
uint8_t leftShift = value << 2;
uint8_t rightShift = value >> 1;
printf("Original value: %d\n ",value);
printf("After left shift by 2: %d\n ",leftShift);
printf("After right shift by 1: %d\n ",rightShift);
return 0;
}
