#include "HardHook.h"

#include <cstdio>

HardHook::HardHook() : call(0) 
{
	memset(originalBytes, 0, NUM_HOOK_BYTES);
	memset(trampolineBytes, 0, NUM_HOOK_BYTES);
}

HardHook::~HardHook()
{
	Restore();
}

void HardHook::Setup(voidFunc targetFunc, voidFunc trampolineFunc)
{
	if (call == NULL)
	{
		DWORD oldProtect, restoreProtect;

		call = targetFunc; // The function that we are replacing?

		if(VirtualProtect(call, NUM_HOOK_BYTES, PAGE_EXECUTE_READ, &oldProtect)) // Make sure that we can change the memory of the function?
		{
			memcpy(trampolineBytes, HOOK_CODE, NUM_HOOK_BYTES);
			unsigned char** iptr = reinterpret_cast<unsigned char**>(&trampolineBytes[HookTrampolineAdressIndex]); // ???
			*iptr = reinterpret_cast<unsigned char*>(trampolineFunc); // ???

			memcpy(originalBytes, call, NUM_HOOK_BYTES); // Store the original part

			Inject();

			VirtualProtect(call, NUM_HOOK_BYTES, oldProtect, &restoreProtect); // Set the old bytes back
		}
		else
		{
			MessageBoxA(0, "Failed vprotect", "Hook setup error", 0);
		}
	}
	else
	{
		//MessageBoxA(0, "Call was not null!", "Hook setup error", 0);
	}
}

void HardHook::SetupInterface(IUnknown* unkn, LONG funcoffset, voidFunc replacement)
{
	//fods("HardHook: Replacing %p function #%ld", unkn, funcoffset);
	void** ptr = reinterpret_cast<void**>(unkn);
	ptr = reinterpret_cast<void**>(ptr[0]);
	Setup(reinterpret_cast<voidFunc>(ptr[funcoffset]), replacement);
}

void HardHook::Inject()
{
	DWORD oldProtect, restoreProtect;

	if (call && VirtualProtect(call, NUM_HOOK_BYTES, PAGE_EXECUTE_READWRITE, &oldProtect))	// Check so that we have a function to work with and set the access allowance
	{
		memcpy(call, trampolineBytes, NUM_HOOK_BYTES); // Overwrite the first piece of code with our trampoline part
	
		VirtualProtect(call, NUM_HOOK_BYTES, oldProtect, &restoreProtect); // Restore the old protection

		//Flush instruction cache. May be required on some architectures which
		//don't feature strong cache coherency guarantees, though not on neither
		//x86, x64 nor AMD64.
		FlushInstructionCache(GetCurrentProcess(),call, NUM_HOOK_BYTES);
	}
}

void HardHook::Restore()
{
	if(call) // if we have a function stored
	{
		DWORD oldProtect, restoreProtect;
		if (VirtualProtect(call, NUM_HOOK_BYTES, PAGE_EXECUTE_READWRITE, &oldProtect)) // Set the access level
		{
			memcpy(call, originalBytes, NUM_HOOK_BYTES); // Change the first bit back to the original so that we do not jump back when we call it
		
			VirtualProtect(call, NUM_HOOK_BYTES, oldProtect, &restoreProtect); // Set the access to the old level

			//Flush instruction cache. May be required on some architectures which
			//don't feature strong cache coherency guarantees, though not on neither
			//x86, x64 nor AMD64.
			FlushInstructionCache(GetCurrentProcess(),call, NUM_HOOK_BYTES);
		}
	}
}
