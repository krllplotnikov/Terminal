#ifndef MODULEKEYBOARD_H_
#define MODULEKEYBOARD_H_

#include <stddef.h>
#include <stdint.h>
#include "MatrixKeyboard.h"

typedef struct ModuleKeyboard ModuleKeyboard_st;

typedef enum KeyboardKey KeyboardKey_et;

enum KeyboardKey{
	KEYBOARD_KEY_1,
	KEYBOARD_KEY_2,
	KEYBOARD_KEY_3,
	KEYBOARD_KEY_4,
	KEYBOARD_KEY_5,
	KEYBOARD_KEY_6,
	KEYBOARD_KEY_7,
	KEYBOARD_KEY_8,
	KEYBOARD_KEY_9,
	KEYBOARD_KEY_STAR,
	KEYBOARD_KEY_0,
	KEYBOARD_KEY_SHARP,
};

struct ModuleKeyboard{
	MatrixKeyboard_st* keyboard;
};

#ifdef __cplusplus
extern "C" {
#endif

void ModuleKeyboard_Init(ModuleKeyboard_st* moduleKeyboard, MatrixKeyboard_st* keyboard);
void ModuleKeyboard_Run(ModuleKeyboard_st* moduleKeyboard);

//-----Weak-----
void ModuleKeyboard_Click(ModuleKeyboard_st* moduleKeyboard, KeyboardKey_et key);
//-----Weak-----

#ifdef __cplusplus
}
#endif

#endif
