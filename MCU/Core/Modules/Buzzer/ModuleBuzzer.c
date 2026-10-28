#include "ModuleBuzzer.h"

ModuleBuzzer_st* moduleBuzzerInstance = NULL;

void ModuleBuzzer_Init(ModuleBuzzer_st* moduleBuzzer, LED_st* buzzer){
	moduleBuzzerInstance = moduleBuzzer;
	moduleBuzzer->buzzer = buzzer;
}

void ModuleBuzzer_Run(ModuleBuzzer_st* moduleBuzzer){
	LED_Run(moduleBuzzer->buzzer);
}

void ModuleBuzzer_LongBeep(ModuleBuzzer_st* moduleBuzzer){
	LED_SetIndication(moduleBuzzer->buzzer, LED_INDICATION_ON, 1);
}

void ModuleBuzzer_SingleBeep(ModuleBuzzer_st* moduleBuzzer){
	LED_SetIndication(moduleBuzzer->buzzer, LED_INDICATION_SINGLE_BLINK, 1);
}

void ModuleBuzzer_DoubleBeep(ModuleBuzzer_st* moduleBuzzer){
	LED_SetIndication(moduleBuzzer->buzzer, LED_INDICATION_DOUBLE_BLINK, 1);
}

void ModuleBuzzer_TripleBeep(ModuleBuzzer_st* moduleBuzzer){
	LED_SetIndication(moduleBuzzer->buzzer, LED_INDICATION_TRIPLE_BLINK, 1);
}
