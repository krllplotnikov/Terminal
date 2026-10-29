#include "ModuleDisplay.h"

ModuleDisplay_st* moduleDisplayInstance = NULL;

void ModuleDisplay_Init(ModuleDisplay_st* moduleDisplay, ST7789_st* st7789, MicroGFX_st* gfx){
	moduleDisplayInstance = moduleDisplay;
	moduleDisplay->st7789 = st7789;
	moduleDisplay->gfx = gfx;
}

void ModuleDisplay_Run(ModuleDisplay_st* moduleDisplay){

}

void ModuleDisplay_DrawStartScreen(ModuleDisplay_st* moduleDisplay){
	MicroGFX_FillScreen(moduleDisplay->gfx, WHITE_RGB565);
	MicroGFX_DrawRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, 10, BLACK_RGB565);

	MicroGFX_DrawString(moduleDisplay->gfx, 5, 12, "1." NEW_GAME_STR, BLACK_RGB565, FONT_11X18);
	MicroGFX_DrawString(moduleDisplay->gfx, 5, 30, "2." CONTINUE_STR, GRAY_RGB565, FONT_11X18);
	MicroGFX_DrawString(moduleDisplay->gfx, 5, 48, "3." SETTINGS_STR, GRAY_RGB565, FONT_11X18);
}

void ModuleDisplay_DrawCardRegistrationScreen(ModuleDisplay_st* moduleDisplay){
	MicroGFX_FillScreen(moduleDisplay->gfx, WHITE_RGB565);
	MicroGFX_DrawRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, 10, BLACK_RGB565);

	MicroGFX_DrawString(moduleDisplay->gfx, 5, 12, REG_CARD_STR, BLACK_RGB565, FONT_11X18);
}

void ModuleDisplay_DrawRegisterPlayerCard(ModuleDisplay_st* moduleDisplay, uint8_t* uid, uint8_t playerNum){
	char str[32] = {0};
	sprintf(str, "Игрок %d: %02X %02X %02X %02X", playerNum, uid[0], uid[1], uid[2], uid[3]);
	MicroGFX_DrawString(moduleDisplay->gfx, 5, 12 + playerNum * 18, str, BLACK_RGB565, FONT_11X18);
}
