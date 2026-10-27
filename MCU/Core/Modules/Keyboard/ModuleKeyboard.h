#ifndef MODULEKEYBOARD_H_
#define MODULEKEYBOARD_H_

#include <stddef.h>
#include <stdint.h>
#include "MatrixKeyboard.h"

typedef struct ModuleKeyboard ModuleKeyboard_st;

struct ModuleKeyboard{
	MatrixKeyboard_st* keyboard;
};

#ifdef __cplusplus
extern "C" {
#endif

void ModuleKeyboard_Init(ModuleKeyboard_st* moduleKeyboard, MatrixKeyboard_st* keyboard);
void ModuleKeyboard_Run(ModuleKeyboard_st* moduleKeyboard);

//-----Weak-----
void ModuleKeyboard_Click(ModuleKeyboard_st* moduleKeyboard);
//-----Weak-----

#ifdef __cplusplus
}
#endif

#endif
