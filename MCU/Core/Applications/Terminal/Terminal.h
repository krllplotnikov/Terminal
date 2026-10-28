#ifndef TERMINAL_TERMINAL_H_
#define TERMINAL_TERMINAL_H_

#include "ModuleBuzzer.h"
#include "ModuleDisplay.h"
#include "ModuleKeyboard.h"
#include "ModuleRFID.h"

#include "StringsLocalisation.h"

typedef struct Terminal Terminal_st;

struct Controller{
	ModuleBuzzer_st*     moduleBuzzer;
	ModuleDisplay_st*    moduleLed;
	ModuleKeyboard_st*   modleKeyboard;
	ModuleRFID_st*       moduleRFID;
};

#ifdef __cplusplus
extern "C" {
#endif

void Terminal_Init(Terminal_st* terminal, ModuleBuzzer_st* moduleBuzzer, ModuleDisplay_st* moduleLed, ModuleKeyboard_st* modleKeyboard, ModuleRFID_st* moduleRFID);
void Terminal_Run(Terminal_st* terminal);

#ifdef __cplusplus
}
#endif

#endif
