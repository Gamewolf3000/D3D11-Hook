#ifndef _CONSOLE__H
#define _CONSOLE__H

#include <Windows.h>
#include <iostream>
#include <io.h>
#include <fcntl.h> // for _O_TEXT
void AddConsole()
{
	int hCrt;
	FILE *hf;

	AllocConsole();
	hCrt = _open_osfhandle((long) GetStdHandle(STD_OUTPUT_HANDLE), _O_TEXT);
	
	hf = _fdopen( hCrt, "w" );
	
	*stdout = *hf;
	
	int i = setvbuf( stdout, NULL, _IONBF, 0 );
}

#endif