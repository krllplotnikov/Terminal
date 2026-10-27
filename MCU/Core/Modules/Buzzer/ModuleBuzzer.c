#include "ModuleBuzzer.h"

ModuleBuzzer_st* moduleBuzzerInstance = NULL;

void ModuleBuzzer_Init(ModuleBuzzer_st* moduleBuzzer, LED_st* buzzer){
	moduleBuzzerInstance = moduleBuzzer;
	moduleBuzzer->buzzer = buzzer;
}

void ModuleBuzzer_Run(ModuleBuzzer_st* moduleBuzzer){
	LED_Run(moduleBuzzer->buzzer);
}
