#include <stdafx.h>
#include <tchar.h>

#include <string>

#include "../Shared/SharedData.h"
#include <WindowsX.h>

#include "HookInput\HookInput.h"

static WNDPROC OldWndProc = 0;

#define MAKE_DWORD(LoWord,HiWord) (unsigned int)((LoWord) + ((HiWord)<<16))

extern SharedMemory g_SharedMemory;

LPARAM prevRawLparam = 0;

LRESULT CALLBACK NewWndProc(HWND Hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch(Message)
	{
		//case WM_NCMOUSEMOVE:

		/*
		case WM_SIZE:
			{
				int width = LOWORD(lParam);
				int height = HIWORD(lParam);

				if(width != g_SharedMemory.GetThumbnailData()->ClientSurfaceWidth ||
					height != g_SharedMemory.GetThumbnailData()->ClientSurfaceHeight)
				{
					return DefWindowProc(Hwnd, Message, wParam, lParam);
				}
			}
		break;
		*/

		case WM_INPUT:
			if(prevRawLparam == 13371337)
				HookInput::GetInstance()->PopMessage();

			prevRawLparam = lParam;
			break;

		case WM_NCMOUSELEAVE: //if not ignored some games (ex Starcraft2) will ignore some logic
			return 0;
			break;		
		
		case WM_ACTIVATE:
		case WM_ACTIVATEAPP:
			{
				switch(wParam)
				{
					case WA_INACTIVE:
						return 0;
					break;
				}
			}
			break;
	}

	return CallWindowProc(OldWndProc, Hwnd, Message, wParam, lParam);
}