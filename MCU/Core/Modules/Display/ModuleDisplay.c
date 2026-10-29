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

void ModuleDisplay_DrawStartAmountScreen(ModuleDisplay_st* moduleDisplay){
	MicroGFX_FillScreen(moduleDisplay->gfx, WHITE_RGB565);
	MicroGFX_DrawRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, 10, BLACK_RGB565);

	MicroGFX_DrawString(moduleDisplay->gfx, 5, 12, ENTER_START_SUM_STR, BLACK_RGB565, FONT_11X18);
	MicroGFX_DrawString(moduleDisplay->gfx, 5, 30, "Сумма : ", BLACK_RGB565, FONT_11X18);
}

void ModuleDisplay_DrawWaitCardScreen(ModuleDisplay_st* moduleDisplay){
	MicroGFX_FillScreen(moduleDisplay->gfx, WHITE_RGB565);
	MicroGFX_DrawRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, 10, BLACK_RGB565);

	MicroGFX_DrawString(moduleDisplay->gfx, 5, 12, WAIT_CARD_STR, BLACK_RGB565, FONT_11X18);
}

void ModuleDisplay_DrawChooseOperationScreen(ModuleDisplay_st* moduleDisplay){
	MicroGFX_FillScreen(moduleDisplay->gfx, WHITE_RGB565);
	MicroGFX_DrawRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, 10, BLACK_RGB565);

	MicroGFX_DrawString(moduleDisplay->gfx, 5, 12, CHOOSE_OP_STR, BLACK_RGB565, FONT_11X18);
	MicroGFX_DrawString(moduleDisplay->gfx, 5, 30, "1." CHECK_BALANCE_STR, BLACK_RGB565, FONT_11X18);
	MicroGFX_DrawString(moduleDisplay->gfx, 5, 48, "2." SEND_TO_PLAYER_STR, BLACK_RGB565, FONT_11X18);
	MicroGFX_DrawString(moduleDisplay->gfx, 5, 66, "3." SEND_TO_BANK_STR, GRAY_RGB565, FONT_11X18);
}

void ModuleDisplay_DrawBalanceScreen(ModuleDisplay_st* moduleDisplay, uint32_t balance){
	MicroGFX_FillScreen(moduleDisplay->gfx, WHITE_RGB565);
	MicroGFX_DrawRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, 10, BLACK_RGB565);

	char str[32] = {0};
	sprintf(str, "Баланс : %ld", balance);
	MicroGFX_DrawString(moduleDisplay->gfx, 5, 12, str, BLACK_RGB565, FONT_11X18);
}

void ModuleDisplay_DrawTransactionAmountScreen(ModuleDisplay_st* moduleDisplay){
	MicroGFX_FillScreen(moduleDisplay->gfx, WHITE_RGB565);
	MicroGFX_DrawRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, 10, BLACK_RGB565);

	MicroGFX_DrawString(moduleDisplay->gfx, 5, 12, ENTER_SUM_STR, BLACK_RGB565, FONT_11X18);
	MicroGFX_DrawString(moduleDisplay->gfx, 5, 30, "Сумма : ", BLACK_RGB565, FONT_11X18);
}

void ModuleDisplay_DrawChoosePlayerScreen(ModuleDisplay_st* moduleDisplay, uint8_t playerNum){
	MicroGFX_FillScreen(moduleDisplay->gfx, WHITE_RGB565);
	MicroGFX_DrawRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, 10, BLACK_RGB565);

	MicroGFX_DrawString(moduleDisplay->gfx, 5, 12, CHOOSE_PLAYER_STR, BLACK_RGB565, FONT_11X18);
	for(uint8_t i = 1; i <= playerNum; i++){
		char str[32] = {0};
		sprintf(str, "%d.Игрок %d", i, i);
		MicroGFX_DrawString(moduleDisplay->gfx, 5, 12 + 18 * i, str, BLACK_RGB565, FONT_11X18);
	}
}

void ModuleDisplay_DrawRegisterPlayerCard(ModuleDisplay_st* moduleDisplay, uint8_t* uid, uint8_t playerNum){
	char str[32] = {0};
	sprintf(str, "Игрок %d: %02X %02X %02X %02X", playerNum, uid[0], uid[1], uid[2], uid[3]);
	MicroGFX_DrawString(moduleDisplay->gfx, 5, 12 + playerNum * 18, str, BLACK_RGB565, FONT_11X18);
}
