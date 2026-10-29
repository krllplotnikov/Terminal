#include "Terminal.h"

Terminal_st* terminalInstance = NULL;

static uint8_t isArrayEmpty(uint8_t* arr, size_t size);

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
		ModuleBuzzer_SingleBeep(terminalInstance->moduleBuzzer);

		switch(terminalInstance->state){
		case TERMINAL_STATE_START:{
			if(key == KEYBOARD_KEY_1){


				terminalInstance->state = TERMINAL_STATE_CARD_REGISTRATION;
			}
			break;
		}


		default: break;
		}
	}
}

void ModuleRFID_CardDetected(ModuleRFID_st* moduleRFID){
	if(moduleRFID == terminalInstance->moduleRFID){
		ModuleBuzzer_DoubleBeep(terminalInstance->moduleBuzzer);

		if(RC522_ReadUid(terminalInstance->moduleRFID->rc522, terminalInstance->tempData.currentCardUID) == RC522_STATUS_OK){

		}
	}
}




static uint8_t isArrayEmpty(uint8_t* arr, size_t size){
	for(size_t i = 0; i < size; i++){
		if(arr[i] != 0){
			return 0;
		}
	}
	return 1;
}
