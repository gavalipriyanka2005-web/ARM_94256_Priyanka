/* USER CODE BEGIN Header */
/**
  **************************
  * @file           : main.c
  * @brief          : DHT11 with LCD
  **************************
  */
/* USER CODE END Header */

#include "main.h"
#include "dht11.h"
#include <stdio.h>
#include <string.h>

/* LCD Pin Definitions */
#define LCD_PORT GPIOB
#define LCD_RS GPIO_PIN_0
#define LCD_EN GPIO_PIN_1
#define LCD_D4 GPIO_PIN_2
#define LCD_D5 GPIO_PIN_3
#define LCD_D6 GPIO_PIN_4
#define LCD_D7 GPIO_PIN_5

/* Function Prototypes */
void SystemClock_Config(void);
static void MX_GPIO_Init(void);

/* LCD Functions */
void LCD_Command(uint8_t cmd);
void LCD_Data(uint8_t data);
void LCD_Init(void);
void LCD_String(char *str);
void LCD_SetCursor(uint8_t row, uint8_t col);

/* Variables */
uint8_t temperature = 0;
uint8_t humidity = 0;
char lcd_buf[16];

int main(void)
{
  HAL_Init();
  SystemClock_Config();
  MX_GPIO_Init();

  LCD_Init();
  DHT11_Init();

  LCD_SetCursor(0, 0);
  LCD_String("DHT11 READY");

  HAL_Delay(2000);
  LCD_Command(0x01); // clear LCD

  while (1)
  {
    if (DHT11_Read(&temperature, &humidity) == 0)
    {
      LCD_SetCursor(0, 0);
      sprintf(lcd_buf, "Temp: %d C ", temperature);
      LCD_String(lcd_buf);

      LCD_SetCursor(1, 0);
      sprintf(lcd_buf, "Hum : %d %%", humidity);
      LCD_String(lcd_buf);
    }
    else
    {
      LCD_SetCursor(0, 0);
      LCD_String("DHT11 ERROR ");
    }

    HAL_Delay(2000);
  }
}

/* ---------------- LCD FUNCTIONS ---------------- */

void LCD_Command(uint8_t cmd)
{
  HAL_GPIO_WritePin(LCD_PORT, LCD_RS, GPIO_PIN_RESET);

  HAL_GPIO_WritePin(LCD_PORT, LCD_D4, (cmd & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_PORT, LCD_D5, (cmd & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_PORT, LCD_D6, (cmd & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_PORT, LCD_D7, (cmd & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET);

  HAL_GPIO_WritePin(LCD_PORT, LCD_EN, GPIO_PIN_SET);
  HAL_Delay(1);
  HAL_GPIO_WritePin(LCD_PORT, LCD_EN, GPIO_PIN_RESET);

  cmd <<= 4;
  HAL_GPIO_WritePin(LCD_PORT, LCD_D4, (cmd & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_PORT, LCD_D5, (cmd & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_PORT, LCD_D6, (cmd & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_PORT, LCD_D7, (cmd & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET);

  HAL_GPIO_WritePin(LCD_PORT, LCD_EN, GPIO_PIN_SET);
  HAL_Delay(1);
  HAL_GPIO_WritePin(LCD_PORT, LCD_EN, GPIO_PIN_RESET);
}

void LCD_Data(uint8_t data)
{
  HAL_GPIO_WritePin(LCD_PORT, LCD_RS, GPIO_PIN_SET);

  HAL_GPIO_WritePin(LCD_PORT, LCD_D4, (data & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_PORT, LCD_D5, (data & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_PORT, LCD_D6, (data & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_PORT, LCD_D7, (data & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET);

  HAL_GPIO_WritePin(LCD_PORT, LCD_EN, GPIO_PIN_SET);
  HAL_Delay(1);
  HAL_GPIO_WritePin(LCD_PORT, LCD_EN, GPIO_PIN_RESET);

  data <<= 4;
  HAL_GPIO_WritePin(LCD_PORT, LCD_D4, (data & 0x10) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_PORT, LCD_D5, (data & 0x20) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_PORT, LCD_D6, (data & 0x40) ? GPIO_PIN_SET : GPIO_PIN_RESET);
  HAL_GPIO_WritePin(LCD_PORT, LCD_D7, (data & 0x80) ? GPIO_PIN_SET : GPIO_PIN_RESET);

  HAL_GPIO_WritePin(LCD_PORT, LCD_EN, GPIO_PIN_SET);
  HAL_Delay(1);
  HAL_GPIO_WritePin(LCD_PORT, LCD_EN, GPIO_PIN_RESET);
}

void LCD_Init(void)
{
  HAL_Delay(20);
  LCD_Command(0x02);
  LCD_Command(0x28);
  LCD_Command(0x0C);
  LCD_Command(0x06);
  LCD_Command(0x01);
}

void LCD_String(char *str)
{
  while (*str)
    LCD_Data(*str++);
}

void LCD_SetCursor(uint8_t row, uint8_t col)
{
  uint8_t pos = (row == 0) ? (0x80 + col) : (0xC0 + col);
  LCD_Command(pos);
}

/* ---------------- GPIO INIT ---------------- */

static void MX_GPIO_Init(void)
{
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  GPIO_InitStruct.Pin = LCD_RS | LCD_EN | LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(LCD_PORT, &GPIO_InitStruct);
}

void SystemClock_Config(void)
{
  /* Use CubeMX generated clock code */
}
