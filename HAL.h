#ifndef HAL_H
#define HAL_H

#include <stdio.h>
#include <stdbool.h>

bool HAL_FileExist(const char *filename);
int HAL_FileRead(const char *filename, char *buf, size_t size);
int HAL_FileWrite(const char *filename, char *buf, size_t size);
bool HAL_TRNG(char *UN, size_t size);
unsigned long HAL_Tick();

#endif   // HAL_H
