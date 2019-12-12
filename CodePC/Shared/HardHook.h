#ifndef _HARDHOOK_H
#define _HARDHOOK_H

#include <windows.h>

typedef void *(*voidFunc)();

#ifdef _WIN64
const unsigned char HOOK_CODE[] = {0x48, 0xb8, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x50, 0xc3};
const unsigned int HookTrampolineAdressIndex = 2;
#else
const unsigned char HOOK_CODE[] = {0x68, 0x00, 0x00, 0x00, 0x00, 0xc3};
const unsigned int HookTrampolineAdressIndex = 1;
#endif

// Assembly stuff ^

const int NUM_HOOK_BYTES = ARRAYSIZE(HOOK_CODE);

struct HardHook {
	// Pointer to the place in the original code where replacements happen
	unsigned char originalBytes[NUM_HOOK_BYTES];
	unsigned char trampolineBytes[NUM_HOOK_BYTES];

	// Points to the (rest of the) original function when used from the injected function
	voidFunc call;

	HardHook();
	~HardHook();

	void Setup(voidFunc targetFunc, voidFunc trampolineFunc);
	void SetupInterface(IUnknown* intf, LONG funcoffset, voidFunc replacement);
	void Inject();
	void Restore();
};

#endif