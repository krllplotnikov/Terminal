#include "ModuleKeyboard.h"

ModuleKeyboard_st* moduleKeyboardInstance = NULL;

void ModuleKeyboard_Init(ModuleKeyboard_st* moduleKeyboard, MatrixKeyboard_st* keyboard){
	moduleKeyboardInstance = moduleKeyboard;
	moduleKeyboard->keyboard = keyboard;
}

void ModuleKeyboard_Run(ModuleKeyboard_st* moduleKeyboard){
	MatrixKeyboard_Run(moduleKeyboard->keyboard);
}



//-----Weak-----
__attribute__((weak)) void ModuleKeyboard_Click(ModuleKeyboard_st* moduleKeyboard){}
//-----Weak-----
