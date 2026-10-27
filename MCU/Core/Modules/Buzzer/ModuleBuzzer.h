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

#ifdef __cplusplus
}
#endif

#endif
