#include "SharedMemory.h"
#include <Windows.h>

SharedMemory::SharedMemory()
{
	
}

SharedMemory::SharedMemory(const wchar_t * identifier, unsigned int sizeOfArea, bool create)
{
	if (create)
		CreateSharedMemory(identifier, sizeOfArea);
	else
		ConnectToSharedMemory(identifier, sizeOfArea);
}

SharedMemory::~SharedMemory()
{
	if (hMapFile)
	{
		UnmapViewOfFile(data);
		CloseHandle(hMapFile);
	}
}

bool SharedMemory::CreateSharedMemory(const wchar_t * identifier, unsigned int sizeOfArea)
{
	hMapFile = CreateFileMapping(
		INVALID_HANDLE_VALUE,    // use paging file
		NULL,                    // default security
		PAGE_READWRITE,          // read/write access
		0,                       // maximum object size (high-order DWORD)
		sizeOfArea,                // maximum object size (low-order DWORD)
		identifier);                 // name of mapping object


	if (hMapFile == NULL)
	{
		return false;
	}
	data = MapViewOfFile(hMapFile,   // handle to map object
		FILE_MAP_ALL_ACCESS, // read/write permission
		0,
		0,
		sizeOfArea);

	if (data == nullptr)
	{
		CloseHandle(hMapFile);
		return false;
	}

	return true;
}

bool SharedMemory::ConnectToSharedMemory(const wchar_t * identifier, unsigned int sizeOfArea)
{

	hMapFile = OpenFileMapping(
		FILE_MAP_ALL_ACCESS,   // read/write access
		FALSE,                 // do not inherit the name
		identifier);               // name of mapping object

	if (hMapFile == NULL)
	{
		return false;
	}

	data = MapViewOfFile(hMapFile, // handle to map object
		FILE_MAP_ALL_ACCESS,  // read/write permission
		0,
		0,
		sizeOfArea);

	if (data == NULL)
	{
		CloseHandle(hMapFile);
		return false;
	}

	return true;
}

void* SharedMemory::GetPointer()
{
	return data;
}
