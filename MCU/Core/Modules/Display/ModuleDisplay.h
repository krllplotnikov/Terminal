#ifndef MODULEDISPLAY_H_
#define MODULEDISPLAY_H_

#include <stddef.h>
#include <stdint.h>
#include "ST7789.h"
#include "MicroGFX.h"

#include "StringsLocalisation.h"

typedef struct ModuleDisplay ModuleDisplay_st;

struct ModuleDisplay{
	ST7789_st* st7789;
	MicroGFX_st* gfx;
};

#ifdef __cplusplus
extern "C" {
#endif

void ModuleDisplay_Init(ModuleDisplay_st* moduleDisplay, ST7789_st* st7789, MicroGFX_st* gfx);
void ModuleDisplay_Run(ModuleDisplay_st* moduleDisplay);

void ModuleDisplay_DrawStartScreen(ModuleDisplay_st* moduleDisplay);
void ModuleDisplay_DrawCardRegistrationScreen(ModuleDisplay_st* moduleDisplay);

void ModuleDisplay_DrawRegisterPlayerCard(ModuleDisplay_st* moduleDisplay, uint8_t* uid, uint8_t playerNum);

#ifdef __cplusplus
}
#endif

#endif
