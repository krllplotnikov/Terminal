#include "Terminal.h"

Terminal_st* terminalInstance = NULL;

static uint8_t isCardExist(uint8_t* uid);

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
				ModuleDisplay_DrawCardRegistrationScreen(terminalInstance->moduleDisplay);
				ModuleBuzzer_SingleBeep(terminalInstance->moduleBuzzer);

				terminalInstance->state = TERMINAL_STATE_CARD_REGISTRATION;
			}
			break;
		}

		case TERMINAL_STATE_CARD_REGISTRATION:{
			if(key == KEYBOARD_KEY_SHARP){
				if(terminalInstance->playersNum >= 2){
					ModuleBuzzer_SingleBeep(terminalInstance->moduleBuzzer);

					terminalInstance->state = TERMINAL_STATE_ENTER_START_AMOUNT;
				}else{
					ModuleBuzzer_LongBeep(terminalInstance->moduleBuzzer);
				}
			}
			break;
		}

		case TERMINAL_STATE_ENTER_START_AMOUNT:{
			if(key == KEYBOARD_KEY_SHARP){

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


			default: break;
			}
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
