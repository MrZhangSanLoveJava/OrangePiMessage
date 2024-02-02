#ifndef __MYOLED_H
#define __MYOLED_H

#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include "myfont.h"

#define I2CADDRESS 0x3C
#define DATA 0x40
#define CMD  0x00

void OLED_Init(int fd);
void OLED_showchar(int fd, unsigned char x, unsigned char y, unsigned char Char);
void OLED_ShowString(int fd, int x, int y, const char* str);
void OLED_clear(int fd);
void OLED_setcursor(int fd, unsigned char x, unsigned char y);

#endif
