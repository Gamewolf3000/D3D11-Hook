#pragma once

#include <Windows.h>
#include <tchar.h>

class Mutex
{
protected:
	HANDLE _mutex;

public:
	Mutex()
	{
		_mutex = 0; 
	}

	~Mutex()
	{
		Unlock();
		Destroy();
	}

	bool Create(TCHAR* name)
	{
		Destroy();
		_mutex = CreateMutex(NULL, FALSE, name);
	
		return _mutex != NULL;
	}

	bool IsCreated()
	{
		return _mutex != NULL;
	}

	bool Destroy()
	{
		return CloseHandle(_mutex) == TRUE;
	}

	void Lock()
	{
		WaitForSingleObject(_mutex, INFINITE);
	}

	void Unlock()
	{
		ReleaseMutex(_mutex);
	}
};