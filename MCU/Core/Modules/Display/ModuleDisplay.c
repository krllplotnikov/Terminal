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
	MicroGFX_FillScreen(moduleDisplay->gfx, BACKGROUND_COLOR);
	MicroGFX_DrawRoundRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, moduleDisplay->st7789->descriptor.height, 42, GREEN_RGB565);

	char str[32] = {0};
	sprintf(str, "ÌÅÍÞ");

	uint16_t x = moduleDisplay->st7789->descriptor.width / 2 - strlen(str) * FONT_WIDTH / 2;
	uint16_t y = 4;
	MicroGFX_DrawString(moduleDisplay->gfx, x, y, str, FONT_COLOR_MAIN, FONT_11X18);

	MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * 0, "1." NEW_GAME_STR, FONT_COLOR_MAIN, FONT_11X18);
	MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * 1, "2." CONTINUE_STR, FONT_COLOR_UNAVAILABLE, FONT_11X18);
	MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * 2, "3." SETTINGS_STR, FONT_COLOR_UNAVAILABLE, FONT_11X18);
}

void ModuleDisplay_DrawCardRegistrationScreen(ModuleDisplay_st* moduleDisplay){
	MicroGFX_FillScreen(moduleDisplay->gfx, BACKGROUND_COLOR);
	MicroGFX_DrawRoundRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, moduleDisplay->st7789->descriptor.height, 42, GREEN_RGB565);

	char str[32] = {0};
	sprintf(str, "ÐÅÃÈÑÒÐÀÖÈß");
	uint16_t x = moduleDisplay->st7789->descriptor.width / 2 - strlen(str) * FONT_WIDTH / 2;
	uint16_t y = 4;
	MicroGFX_DrawString(moduleDisplay->gfx, x, y, str, FONT_COLOR_MAIN, FONT_11X18);
	sprintf(str, "ÊÀÐÒÛ");
	x = moduleDisplay->st7789->descriptor.width / 2 - strlen(str) * FONT_WIDTH / 2;
	y = 22;
	MicroGFX_DrawString(moduleDisplay->gfx, x, y, str, FONT_COLOR_MAIN, FONT_11X18);

	//MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET, REG_CARD_STR, FONT_COLOR_MAIN, FONT_11X18);
}

void ModuleDisplay_DrawStartAmountScreen(ModuleDisplay_st* moduleDisplay){
	MicroGFX_FillScreen(moduleDisplay->gfx, BACKGROUND_COLOR);
	MicroGFX_DrawRoundRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, moduleDisplay->st7789->descriptor.height, 42, GREEN_RGB565);

	char str[32] = {0};
	sprintf(str, "ÑÒÀÐÒÎÂÀß ÑÓÌÌÀ");
	uint16_t x = moduleDisplay->st7789->descriptor.width / 2 - strlen(str) * FONT_WIDTH / 2;
	uint16_t y = 4;
	MicroGFX_DrawString(moduleDisplay->gfx, x, y, str, FONT_COLOR_MAIN, FONT_11X18);

	//MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * 0, ENTER_START_SUM_STR, FONT_COLOR_MAIN, FONT_11X18);
	MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * 1, "Ñóììà: ", FONT_COLOR_MAIN, FONT_11X18);
}

void ModuleDisplay_DrawWaitCardScreen(ModuleDisplay_st* moduleDisplay){
	MicroGFX_FillScreen(moduleDisplay->gfx, BACKGROUND_COLOR);
	MicroGFX_DrawRoundRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, moduleDisplay->st7789->descriptor.height, 42, GREEN_RGB565);

	char str[32] = {0};
	sprintf(str, "ÎÆÈÄÀÍÈÅ ÊÀÐÒÛ");
	uint16_t x = moduleDisplay->st7789->descriptor.width / 2 - strlen(str) * FONT_WIDTH / 2;
	uint16_t y = 4;
	MicroGFX_DrawString(moduleDisplay->gfx, x, y, str, FONT_COLOR_MAIN, FONT_11X18);

	//MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET, WAIT_CARD_STR, FONT_COLOR_MAIN, FONT_11X18);
}

void ModuleDisplay_DrawChooseOperationScreen(ModuleDisplay_st* moduleDisplay){
	MicroGFX_FillScreen(moduleDisplay->gfx, BACKGROUND_COLOR);
	MicroGFX_DrawRoundRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, moduleDisplay->st7789->descriptor.height, 42, GREEN_RGB565);

	char str[32] = {0};
	sprintf(str, "ÂÛÁÅÐÅÒÅ ÎÏÅÐÀÖÈÞ");
	uint16_t x = moduleDisplay->st7789->descriptor.width / 2 - strlen(str) * FONT_WIDTH / 2;
	uint16_t y = 4;
	MicroGFX_DrawString(moduleDisplay->gfx, x, y, str, FONT_COLOR_MAIN, FONT_11X18);

	//MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * 0, CHOOSE_OP_STR, FONT_COLOR_MAIN, FONT_11X18);
	MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * 1, "1." CHECK_BALANCE_STR, FONT_COLOR_MAIN, FONT_11X18);
	MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * 2, "2." SEND_TO_PLAYER_STR, FONT_COLOR_MAIN, FONT_11X18);
	MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * 3, "3." SEND_TO_BANK_STR, FONT_COLOR_UNAVAILABLE, FONT_11X18);
}

void ModuleDisplay_DrawBalanceScreen(ModuleDisplay_st* moduleDisplay, uint32_t balance){
	MicroGFX_FillScreen(moduleDisplay->gfx, BACKGROUND_COLOR);
	MicroGFX_DrawRoundRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, moduleDisplay->st7789->descriptor.height, 42, GREEN_RGB565);

	char str[32] = {0};
	sprintf(str, "ÁÀËÀÍÑ");
	uint16_t x = moduleDisplay->st7789->descriptor.width / 2 - strlen(str) * FONT_WIDTH / 2;
	uint16_t y = 4;
	MicroGFX_DrawString(moduleDisplay->gfx, x, y, str, FONT_COLOR_MAIN, FONT_11X18);

	sprintf(str, "Áàëàíñ: %ld", balance);
	MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET, str, FONT_COLOR_MAIN, FONT_11X18);
}

void ModuleDisplay_DrawTransactionAmountScreen(ModuleDisplay_st* moduleDisplay){
	MicroGFX_FillScreen(moduleDisplay->gfx, BACKGROUND_COLOR);
	MicroGFX_DrawRoundRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, moduleDisplay->st7789->descriptor.height, 42, GREEN_RGB565);

	char str[32] = {0};
	sprintf(str, "ÏÅÐÅÂÎÄ ÍÀ ÊÀÐÒÓ");
	uint16_t x = moduleDisplay->st7789->descriptor.width / 2 - strlen(str) * FONT_WIDTH / 2;
	uint16_t y = 4;
	MicroGFX_DrawString(moduleDisplay->gfx, x, y, str, FONT_COLOR_MAIN, FONT_11X18);
	sprintf(str, "ÄÐÓÃÎÃÎ ÈÃÐÎÊÀ");
	x = moduleDisplay->st7789->descriptor.width / 2 - strlen(str) * FONT_WIDTH / 2;
	y = 22;
	MicroGFX_DrawString(moduleDisplay->gfx, x, y, str, FONT_COLOR_MAIN, FONT_11X18);

	//MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * 0, ENTER_SUM_STR, FONT_COLOR_MAIN, FONT_11X18);
	MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * 1, "Ñóììà : ", FONT_COLOR_MAIN, FONT_11X18);
}

void ModuleDisplay_DrawChoosePlayerScreen(ModuleDisplay_st* moduleDisplay, uint8_t playerNum){
	MicroGFX_FillScreen(moduleDisplay->gfx, BACKGROUND_COLOR);
	MicroGFX_DrawRoundRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, moduleDisplay->st7789->descriptor.height, 42, GREEN_RGB565);

	char str[32] = {0};
	sprintf(str, "ÂÛÁÅÐÒÅ ÈÃÐÎÊÀ");
	uint16_t x = moduleDisplay->st7789->descriptor.width / 2 - strlen(str) * FONT_WIDTH / 2;
	uint16_t y = 4;
	MicroGFX_DrawString(moduleDisplay->gfx, x, y, str, FONT_COLOR_MAIN, FONT_11X18);

	//MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET, CHOOSE_PLAYER_STR, FONT_COLOR_MAIN, FONT_11X18);
	for(uint8_t i = 1; i <= playerNum; i++){
		char str[32] = {0};
		sprintf(str, "%d.Èãðîê %d", i, i);
		MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * i, str, FONT_COLOR_MAIN, FONT_11X18);
	}
}

void ModuleDisplay_DrawCompleteScreen(ModuleDisplay_st* moduleDisplay){
	MicroGFX_FillScreen(moduleDisplay->gfx, BACKGROUND_COLOR);
	MicroGFX_DrawRoundRect(moduleDisplay->gfx, 0, 0, moduleDisplay->st7789->descriptor.width, moduleDisplay->st7789->descriptor.height, 42, GREEN_RGB565);

	char str[32] = {0};
	sprintf(str, "ÏÅÐÅÂÎÄ ÍÀ ÊÀÐÒÓ");
	uint16_t x = moduleDisplay->st7789->descriptor.width / 2 - strlen(str) * FONT_WIDTH / 2;
	uint16_t y = 4;
	MicroGFX_DrawString(moduleDisplay->gfx, x, y, str, FONT_COLOR_MAIN, FONT_11X18);
	sprintf(str, "ÄÐÓÃÎÃÎ ÈÃÐÎÊÀ");
	x = moduleDisplay->st7789->descriptor.width / 2 - strlen(str) * FONT_WIDTH / 2;
	y = 22;
	MicroGFX_DrawString(moduleDisplay->gfx, x, y, str, FONT_COLOR_MAIN, FONT_11X18);

	sprintf(str, "Óñïåøíî!");
	MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * 1, str, FONT_COLOR_MAIN, FONT_11X18);
}





void ModuleDisplay_DrawRegisterPlayerCard(ModuleDisplay_st* moduleDisplay, uint8_t* uid, uint8_t playerNum){
	char str[32] = {0};
	sprintf(str, "Èãðîê %d: %02X %02X %02X %02X", playerNum, uid[0], uid[1], uid[2], uid[3]);
	MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * playerNum, str, FONT_COLOR_MAIN, FONT_11X18);
}

void ModuleDisplay_DrawStartAmountString(ModuleDisplay_st* moduleDisplay, char* amount){
	char str[32] = {0};
	sprintf(str, "Ñóììà: %s", amount);

	MicroGFX_DrawRectFill(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * 1, strlen(str) * FONT_WIDTH + FONT_WIDTH, FONT_HEIGHT, BACKGROUND_COLOR);
	MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * 1, str, FONT_COLOR_MAIN, FONT_11X18);
}

void ModuleDisplay_DrawTransactionAmountString(ModuleDisplay_st* moduleDisplay, char* amount){
	char str[32] = {0};
	sprintf(str, "Ñóììà: %s", amount);

	MicroGFX_DrawRectFill(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * 1, strlen(str) * FONT_WIDTH + FONT_WIDTH, FONT_HEIGHT, BACKGROUND_COLOR);
	MicroGFX_DrawString(moduleDisplay->gfx, START_X_OFFSET, START_Y_OFFSET + FONT_HEIGHT * 1, str, FONT_COLOR_MAIN, FONT_11X18);
}

void ModuleDisplay_DrawCurrentPlayerID(ModuleDisplay_st* moduleDisplay, uint8_t id){
	char str[32] = {0};
	sprintf(str, "Èãðîê %d", id + 1);

	uint16_t x = moduleDisplay->st7789->descriptor.width / 2 - strlen(str) * FONT_WIDTH / 2;

	MicroGFX_DrawRectFill(moduleDisplay->gfx, x, 260, strlen(str) * FONT_WIDTH, FONT_HEIGHT, BACKGROUND_COLOR);
	MicroGFX_DrawString(moduleDisplay->gfx, x, 260, str, FONT_COLOR_MAIN, FONT_11X18);
}
