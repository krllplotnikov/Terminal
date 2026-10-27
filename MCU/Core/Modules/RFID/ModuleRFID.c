#include "ModuleRFID.h"

ModuleRFID_st* moduleRFIDInstance = NULL;

void ModuleRFID_Init(ModuleRFID_st* moduleRFID, RC522_st* rc522){
	moduleRFIDInstance = moduleRFID;
	moduleRFID->rc522 = rc522;
}

void ModuleRFID_Run(ModuleRFID_st* moduleRFID){
	RC522_Run(moduleRFID->rc522);
}
