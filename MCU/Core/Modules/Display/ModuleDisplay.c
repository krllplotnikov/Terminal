#include "ModuleDisplay.h"

ModuleDisplay_st* moduleDisplayInstance = NULL;

void ModuleDisplay_Init(ModuleDisplay_st* moduleDisplay, ST7789_st* st7789, MicroGFX_st* gfx){
	moduleDisplayInstance = moduleDisplay;
	moduleDisplay->st7789 = st7789;
	moduleDisplay->gfx = gfx;
}

void ModuleDisplay_Run(ModuleDisplay_st* moduleDisplay){

}
