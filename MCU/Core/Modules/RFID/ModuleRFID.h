#ifndef MODULERFID_H_
#define MODULERFID_H_

#include <stddef.h>
#include <stdint.h>
#include "RC522.h"

typedef struct ModuleRFID ModuleRFID_st;

struct ModuleRFID{
	RC522_st* rc522;
};

#ifdef __cplusplus
extern "C" {
#endif

void ModuleRFID_Init(ModuleRFID_st* moduleRFID, RC522_st* rc522);
void ModuleRFID_Run(ModuleRFID_st* moduleRFID);

#ifdef __cplusplus
}
#endif

#endif
