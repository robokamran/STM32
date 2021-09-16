#pragma once

/*
https://gist.github.com/fnky/458719343aabd01cfb17a3a4f7296797
https://github.com/sol-prog/ansi-escape-codes-windows-posix-terminals-c-programming-examples/blob/master/ansi_escapes.h
https://bluesock.org/~willkg/dev/ansi.html
http://ascii-table.com/ansi-escape-sequences.php
https://en.wikipedia.org/wiki/ANSI_escape_code
https://stackoverflow.com/questions/4842424/list-of-ansi-color-escape-sequences
https://www.lihaoyi.com/post/BuildyourownCommandLinewithANSIescapecodes.html
*/

#include "stdio.h"
#include "stdarg.h"
#include "usart.h"
#include "string.h"

#define UART_HANDLE &huart2
#define DYN_BUFFER_SIZE 256

enum ColorCodes
{
  T_Black,
  T_Red,
  T_Green,
  T_Yellow,
  T_Blue,
  T_Magenta,
  T_Cyan,
  T_White,
  T_Default
};

static inline void println(const char *format, ...)
{
  char buffer[DYN_BUFFER_SIZE];
  va_list args;
  va_start(args, format);
  int length = vsprintf(buffer, format, args);
  if (length >= 0)
  {
    strcat(buffer, "\r\n");
    HAL_UART_Transmit(UART_HANDLE, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
  }
  va_end(args);
}

static inline void print(const char *format, ...)
{
  char buffer[DYN_BUFFER_SIZE];
  va_list args;
  va_start(args, format);
  int length = vsprintf(buffer, format, args);
  if (length >= 0)
  {
    HAL_UART_Transmit(UART_HANDLE, (uint8_t *)buffer, length, HAL_MAX_DELAY);
  }
  va_end(args);
}

static inline void t_clear(void)
{
  print("\e[1J\e[3J\e[H");
}

static inline void t_report(int bg, int fg, const char *format, ...)
{
  int fg_code = fg == T_Default ? 0 : fg + 30;
  int bg_code = bg == T_Default ? 0 : bg + 40;
  print("\e[%d;%dm", fg_code, bg_code);

  char buffer[DYN_BUFFER_SIZE];
  va_list args;
  va_start(args, format);
  int length = vsprintf(buffer, format, args);
  if (length >= 0)
  {
    strcat(buffer, "\e[m\r\n");
    HAL_UART_Transmit(UART_HANDLE, (uint8_t *)buffer, strlen(buffer), HAL_MAX_DELAY);
  }
  va_end(args);
}
