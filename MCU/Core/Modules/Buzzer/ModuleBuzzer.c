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

void ModuleBuzzer_OffBeep(ModuleBuzzer_st* moduleBuzzer){
	LED_SetIndication(moduleBuzzer->buzzer, LED_INDICATION_OFF, 1);
}


//-----Weak-----
__attribute__((weak)) void ModuleBuzzer_IndicationIsOver(ModuleBuzzer_st* moduleBuzzer, LedIndications_et indication, uint8_t repeatCounter){}
//-----Weak-----
