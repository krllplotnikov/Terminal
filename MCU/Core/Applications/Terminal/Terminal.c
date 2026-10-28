#include "Terminal.h"

Terminal_st* terminalInstance = NULL;

void Terminal_Init(Terminal_st* terminal, ModuleBuzzer_st* moduleBuzzer, ModuleDisplay_st* moduleDisplay, ModuleKeyboard_st* modleKeyboard, ModuleRFID_st* moduleRFID){
	terminalInstance = terminal;
	terminal->moduleBuzzer = moduleBuzzer;
	terminal->moduleDisplay = moduleDisplay;
	terminal->modleKeyboard = modleKeyboard;
	terminal->moduleRFID = moduleRFID;
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
	}
}

void ModuleRFID_CardDetected(ModuleRFID_st* moduleRFID){
	if(moduleRFID == terminalInstance->moduleRFID){
		ModuleBuzzer_DoubleBeep(terminalInstance->moduleBuzzer);
	}
}
