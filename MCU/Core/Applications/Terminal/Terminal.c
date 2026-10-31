#include "Terminal.h"

Terminal_st* terminalInstance = NULL;

static uint8_t isCardExist(uint8_t* uid);
static uint8_t getPlayerIdByCardUID(uint8_t* uid);

void Terminal_Init(Terminal_st* terminal, ModuleBuzzer_st* moduleBuzzer, ModuleDisplay_st* moduleDisplay, ModuleKeyboard_st* modleKeyboard, ModuleRFID_st* moduleRFID){
	terminalInstance = terminal;
	terminal->moduleBuzzer = moduleBuzzer;
	terminal->moduleDisplay = moduleDisplay;
	terminal->modleKeyboard = modleKeyboard;
	terminal->moduleRFID = moduleRFID;

	ModuleDisplay_DrawStartScreen(terminal->moduleDisplay);
}

void Terminal_Run(Terminal_st* terminal){
	ModuleKeyboard_Run(terminal->modleKeyboard);
	ModuleRFID_Run(terminal->moduleRFID);
	ModuleBuzzer_Run(terminal->moduleBuzzer);
	ModuleDisplay_Run(terminal->moduleDisplay);
}

void ModuleKeyboard_Click(ModuleKeyboard_st* moduleKeyboard, KeyboardKey_et key){
	if(moduleKeyboard == terminalInstance->modleKeyboard){

		switch(terminalInstance->state){
		case TERMINAL_STATE_START:{
			if(key == KEYBOARD_KEY_1){
				ModuleBuzzer_SingleBeep(terminalInstance->moduleBuzzer);
				ModuleDisplay_DrawCardRegistrationScreen(terminalInstance->moduleDisplay);

				terminalInstance->state = TERMINAL_STATE_CARD_REGISTRATION;
			}
			break;
		}

		case TERMINAL_STATE_CARD_REGISTRATION:{
			if(key == KEYBOARD_KEY_SHARP){
				if(terminalInstance->playersNum >= 2){
					ModuleBuzzer_SingleBeep(terminalInstance->moduleBuzzer);
					ModuleDisplay_DrawStartAmountScreen(terminalInstance->moduleDisplay);

					terminalInstance->state = TERMINAL_STATE_ENTER_START_AMOUNT;
				}else{
					ModuleBuzzer_LongBeep(terminalInstance->moduleBuzzer);
				}
			}
			else if(key == KEYBOARD_KEY_STAR){
				ModuleBuzzer_SingleBeep(terminalInstance->moduleBuzzer);
				ModuleDisplay_DrawStartScreen(terminalInstance->moduleDisplay);

				terminalInstance->state = TERMINAL_STATE_START;
			}
			else{
				ModuleBuzzer_LongBeep(terminalInstance->moduleBuzzer);
			}
			break;
		}

		case TERMINAL_STATE_ENTER_START_AMOUNT:{
			if(key >= KEYBOARD_KEY_1 && key <= KEYBOARD_KEY_9){
				terminalInstance->tempData.startSumStr[strlen(terminalInstance->tempData.startSumStr)] = key + 48 + 1;
				ModuleDisplay_DrawStartAmountString(terminalInstance->moduleDisplay, terminalInstance->tempData.startSumStr);
			}
			else if(key == KEYBOARD_KEY_0){
				terminalInstance->tempData.startSumStr[strlen(terminalInstance->tempData.startSumStr)] = 48;
				ModuleDisplay_DrawStartAmountString(terminalInstance->moduleDisplay, terminalInstance->tempData.startSumStr);
			}
			else if(key == KEYBOARD_KEY_STAR){
				if(strlen(terminalInstance->tempData.startSumStr) >= 1){
					terminalInstance->tempData.startSumStr[strlen(terminalInstance->tempData.startSumStr) - 1] = 0;
					ModuleDisplay_DrawStartAmountString(terminalInstance->moduleDisplay, terminalInstance->tempData.startSumStr);
				}
				else{
					ModuleBuzzer_LongBeep(terminalInstance->moduleBuzzer);
					ModuleDisplay_DrawCardRegistrationScreen(terminalInstance->moduleDisplay);

					memset(terminalInstance->tempData.startSumStr, 0, MAX_TEMP_STR_LENGTH);

					for(uint8_t i = 0; i < MAX_PLAYERS; i++){
						memset(terminalInstance->players[i].cardUID, 0, CARD_UID_LENGTH);
					}

					terminalInstance->state = TERMINAL_STATE_CARD_REGISTRATION;
				}
			}
			else if(key == KEYBOARD_KEY_SHARP){
				uint32_t amount = atoi(terminalInstance->tempData.startSumStr);

				if(amount > 0 && amount <= 100000){
					ModuleBuzzer_SingleBeep(terminalInstance->moduleBuzzer);

					for(uint8_t i = 0; i < terminalInstance->playersNum; i++){
						terminalInstance->players[i].balance = amount;
					}
					ModuleDisplay_DrawWaitCardScreen(terminalInstance->moduleDisplay);

					memset(terminalInstance->tempData.startSumStr, 0, MAX_TEMP_STR_LENGTH);

					terminalInstance->state = TERMINAL_STATE_WAIT_CARD;
				}
				else{
					ModuleBuzzer_LongBeep(terminalInstance->moduleBuzzer);
				}
			}
			break;
		}

		case TERMINAL_STATE_CHOOSE_OPERATION:{
			if(key == KEYBOARD_KEY_1){
				ModuleBuzzer_SingleBeep(terminalInstance->moduleBuzzer);
				uint8_t id = getPlayerIdByCardUID(terminalInstance->tempData.currentCardUID);
				ModuleDisplay_DrawBalanceScreen(terminalInstance->moduleDisplay, terminalInstance->players[id].balance);
				ModuleDisplay_DrawCurrentPlayerID(terminalInstance->moduleDisplay, terminalInstance->tempData.currentPlayerID);

				terminalInstance->state = TERMINAL_STATE_BALANCE;
			}
			else if(key == KEYBOARD_KEY_2){
				ModuleBuzzer_SingleBeep(terminalInstance->moduleBuzzer);
				ModuleDisplay_DrawChoosePlayerScreen(terminalInstance->moduleDisplay, terminalInstance->playersNum);
				ModuleDisplay_DrawCurrentPlayerID(terminalInstance->moduleDisplay, terminalInstance->tempData.currentPlayerID);

				terminalInstance->state = TERMINAL_STATE_CHOOSE_PLAYER;
			}
			else if(key == KEYBOARD_KEY_STAR){
				ModuleBuzzer_SingleBeep(terminalInstance->moduleBuzzer);
				ModuleDisplay_DrawWaitCardScreen(terminalInstance->moduleDisplay);

				terminalInstance->state = TERMINAL_STATE_WAIT_CARD;
			}
			else{
				ModuleBuzzer_LongBeep(terminalInstance->moduleBuzzer);
			}
			break;
		}

		case TERMINAL_STATE_BALANCE:{
			if(key == KEYBOARD_KEY_STAR){
				ModuleBuzzer_SingleBeep(terminalInstance->moduleBuzzer);
				ModuleDisplay_DrawChooseOperationScreen(terminalInstance->moduleDisplay);
				ModuleDisplay_DrawCurrentPlayerID(terminalInstance->moduleDisplay, terminalInstance->tempData.currentPlayerID);

				terminalInstance->state = TERMINAL_STATE_CHOOSE_OPERATION;
			}
			else{
				ModuleBuzzer_LongBeep(terminalInstance->moduleBuzzer);
			}
			break;
		}

		case TERMINAL_STATE_CHOOSE_PLAYER:{
			if(key >= KEYBOARD_KEY_1 && key <= KEYBOARD_KEY_4){
				if(key <= terminalInstance->playersNum && key != terminalInstance->tempData.currentPlayerID){
					ModuleBuzzer_SingleBeep(terminalInstance->moduleBuzzer);
					ModuleDisplay_DrawTransactionAmountScreen(terminalInstance->moduleDisplay);
					ModuleDisplay_DrawCurrentPlayerID(terminalInstance->moduleDisplay, terminalInstance->tempData.currentPlayerID);

					terminalInstance->tempData.selectedPlayerID = key;
					terminalInstance->state = TERMINAL_STATE_ENTER_TRANSACTION_AMOUNT;
				}
				else{
					ModuleBuzzer_LongBeep(terminalInstance->moduleBuzzer);
				}
			}
			else if(key == KEYBOARD_KEY_STAR){
				ModuleBuzzer_SingleBeep(terminalInstance->moduleBuzzer);
				ModuleDisplay_DrawChooseOperationScreen(terminalInstance->moduleDisplay);
				ModuleDisplay_DrawCurrentPlayerID(terminalInstance->moduleDisplay, terminalInstance->tempData.currentPlayerID);

				terminalInstance->state = TERMINAL_STATE_CHOOSE_OPERATION;
			}
			else{
				ModuleBuzzer_LongBeep(terminalInstance->moduleBuzzer);
			}
			break;
		}

		case TERMINAL_STATE_ENTER_TRANSACTION_AMOUNT:{
			if(key >= KEYBOARD_KEY_1 && key <= KEYBOARD_KEY_9){
				terminalInstance->tempData.enterSumStr[strlen(terminalInstance->tempData.enterSumStr)] = key + 48 + 1;
				ModuleDisplay_DrawTransactionAmountString(terminalInstance->moduleDisplay, terminalInstance->tempData.enterSumStr);
			}
			else if(key == KEYBOARD_KEY_0){
				terminalInstance->tempData.enterSumStr[strlen(terminalInstance->tempData.enterSumStr)] = 48;
				ModuleDisplay_DrawTransactionAmountString(terminalInstance->moduleDisplay, terminalInstance->tempData.enterSumStr);
			}
			else if(key == KEYBOARD_KEY_STAR){
				if(strlen(terminalInstance->tempData.enterSumStr) >= 1){
					terminalInstance->tempData.enterSumStr[strlen(terminalInstance->tempData.enterSumStr) - 1] = 0;
					ModuleDisplay_DrawTransactionAmountString(terminalInstance->moduleDisplay, terminalInstance->tempData.enterSumStr);
				}
				else{
					ModuleBuzzer_LongBeep(terminalInstance->moduleBuzzer);
					ModuleDisplay_DrawChoosePlayerScreen(terminalInstance->moduleDisplay, terminalInstance->playersNum);
					ModuleDisplay_DrawCurrentPlayerID(terminalInstance->moduleDisplay, terminalInstance->tempData.currentPlayerID);

					memset(terminalInstance->tempData.enterSumStr, 0, MAX_TEMP_STR_LENGTH);

					terminalInstance->state = TERMINAL_STATE_CHOOSE_PLAYER;
				}
			}
			else if(key == KEYBOARD_KEY_SHARP){
				uint32_t amount = atoi(terminalInstance->tempData.enterSumStr);

				if(amount > 0 && amount <= terminalInstance->players[terminalInstance->tempData.currentPlayerID].balance){
					ModuleBuzzer_SingleBeep(terminalInstance->moduleBuzzer);

					terminalInstance->players[terminalInstance->tempData.currentPlayerID].balance -= amount;
					terminalInstance->players[terminalInstance->tempData.selectedPlayerID].balance += amount;

					ModuleDisplay_DrawWaitCardScreen(terminalInstance->moduleDisplay);

					memset(terminalInstance->tempData.enterSumStr, 0, MAX_TEMP_STR_LENGTH);

					terminalInstance->state = TERMINAL_STATE_WAIT_CARD;
				}
				else{
					ModuleBuzzer_LongBeep(terminalInstance->moduleBuzzer);
				}
			}
			break;
		}

		default: break;
		}
	}
}

void ModuleRFID_CardDetected(ModuleRFID_st* moduleRFID){
	if(moduleRFID == terminalInstance->moduleRFID){
		if(RC522_ReadUid(terminalInstance->moduleRFID->rc522, terminalInstance->tempData.currentCardUID) == RC522_STATUS_OK){
			switch(terminalInstance->state){
			case TERMINAL_STATE_CARD_REGISTRATION:{
				if(!isCardExist(terminalInstance->tempData.currentCardUID) && terminalInstance->playersNum < MAX_PLAYERS){
					memcpy(terminalInstance->players[terminalInstance->playersNum].cardUID, terminalInstance->tempData.currentCardUID, CARD_UID_LENGTH);
					ModuleDisplay_DrawRegisterPlayerCard(terminalInstance->moduleDisplay, terminalInstance->players[terminalInstance->playersNum].cardUID, terminalInstance->playersNum + 1);
					ModuleBuzzer_DoubleBeep(terminalInstance->moduleBuzzer);
					terminalInstance->playersNum++;
				}
				else{
					ModuleBuzzer_LongBeep(terminalInstance->moduleBuzzer);
				}
				break;
			}

			case TERMINAL_STATE_WAIT_CARD:{
				if(isCardExist(terminalInstance->tempData.currentCardUID)){
					terminalInstance->tempData.currentPlayerID = getPlayerIdByCardUID(terminalInstance->tempData.currentCardUID);

					ModuleBuzzer_DoubleBeep(terminalInstance->moduleBuzzer);
					ModuleDisplay_DrawChooseOperationScreen(terminalInstance->moduleDisplay);
					ModuleDisplay_DrawCurrentPlayerID(terminalInstance->moduleDisplay, terminalInstance->tempData.currentPlayerID);

					terminalInstance->state = TERMINAL_STATE_CHOOSE_OPERATION;
				}
				else{
					ModuleBuzzer_LongBeep(terminalInstance->moduleBuzzer);
				}
				break;
			}

			default: break;
			}
		}
	}
}

void ModuleBuzzer_IndicationIsOver(ModuleBuzzer_st* moduleBuzzer, LedIndications_et indication, uint8_t repeatCounter){
	if(moduleBuzzer == terminalInstance->moduleBuzzer){
		if(indication == LED_INDICATION_ON){
			ModuleBuzzer_OffBeep(moduleBuzzer);
		}
	}
}


static uint8_t isCardExist(uint8_t* uid){
	for(uint8_t i = 0; i < terminalInstance->playersNum; i++){
		if(!memcmp(uid, terminalInstance->players[i].cardUID, CARD_UID_LENGTH)){
			return 1;
		}
	}
	return 0;
}

static uint8_t getPlayerIdByCardUID(uint8_t* uid){
	for(uint8_t i = 0; i < terminalInstance->playersNum; i++){
		if(!memcmp(uid, terminalInstance->players[i].cardUID, CARD_UID_LENGTH)){
			return i;
		}
	}
	return 0;
}
