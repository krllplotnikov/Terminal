#ifndef MODULEBUZZER_H_
#define MODULEBUZZER_H_

#include <stddef.h>
#include <stdint.h>
#include "LED.h"

typedef struct ModuleBuzzer ModuleBuzzer_st;

struct ModuleBuzzer{
	LED_st* buzzer;
};

#ifdef __cplusplus
extern "C" {
#endif

void ModuleBuzzer_Init(ModuleBuzzer_st* moduleBuzzer, LED_st* buzzer);
void ModuleBuzzer_Run(ModuleBuzzer_st* moduleBuzzer);

void ModuleBuzzer_LongBeep(ModuleBuzzer_st* moduleBuzzer);
void ModuleBuzzer_SingleBeep(ModuleBuzzer_st* moduleBuzzer);
void ModuleBuzzer_DoubleBeep(ModuleBuzzer_st* moduleBuzzer);
void ModuleBuzzer_TripleBeep(ModuleBuzzer_st* moduleBuzzer);
void ModuleBuzzer_OffBeep(ModuleBuzzer_st* moduleBuzzer);

//-----Weak-----
void ModuleBuzzer_IndicationIsOver(ModuleBuzzer_st* moduleBuzzer, LedIndications_et indication, uint8_t repeatCounter);
//-----Weak-----

#ifdef __cplusplus
}
#endif

#endif
