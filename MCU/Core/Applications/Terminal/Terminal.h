#ifndef TERMINAL_TERMINAL_H_
#define TERMINAL_TERMINAL_H_

#include "ModuleBuzzer.h"
#include "ModuleDisplay.h"
#include "ModuleKeyboard.h"
#include "ModuleRFID.h"

#include "StringsLocalisation.h"

#define MAX_PLAYERS         4
#define MAX_TEMP_STR_LENGTH 16

typedef enum TerminalState TerminalState_et;

typedef struct Terminal Terminal_st;
typedef struct TempData TempData_st;
typedef struct Player Player_st;

enum TerminalState{
	TERMINAL_STATE_START,
	TERMINAL_STATE_CARD_REGISTRATION,
};

struct Player{
	uint8_t ID;
	uint8_t cardUID[CARD_UID_LENGTH];
	uint8_t balance;
};

struct TempData{
	uint8_t currentUID[CARD_UID_LENGTH];
	uint8_t currentPlayerID;
	char startSumStr[MAX_TEMP_STR_LENGTH];
	char enterSumStr[MAX_TEMP_STR_LENGTH];
};

struct Terminal{
	ModuleBuzzer_st*     moduleBuzzer;
	ModuleDisplay_st*    moduleDisplay;
	ModuleKeyboard_st*   modleKeyboard;
	ModuleRFID_st*       moduleRFID;

	TerminalState_et state;
	Player_st players[MAX_PLAYERS];
};

#ifdef __cplusplus
extern "C" {
#endif

void Terminal_Init(Terminal_st* terminal, ModuleBuzzer_st* moduleBuzzer, ModuleDisplay_st* moduleDisplay, ModuleKeyboard_st* modleKeyboard, ModuleRFID_st* moduleRFID);
void Terminal_Run(Terminal_st* terminal);

#ifdef __cplusplus
}
#endif

#endif
