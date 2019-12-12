#pragma once
#include <windows.h>

typedef struct
{
    LARGE_INTEGER start;
    LARGE_INTEGER stop;
} stopWatch;

class Timer
{
private:
	stopWatch timer;
	LARGE_INTEGER frequency;

	double LIToSecs(LARGE_INTEGER& L)
	{
		return ((double)L.QuadPart / (double)frequency.QuadPart);
	}
public:

	Timer()
	{
		timer.start.QuadPart = 0;
		timer.stop.QuadPart = 0;	
		QueryPerformanceFrequency(&frequency);
	}

	void Start()
	{
		QueryPerformanceCounter(&timer.start);
	}

	void Stop()
	{
		QueryPerformanceCounter(&timer.stop);
	}

	double GetElapsedTime()
	{
		LARGE_INTEGER time;
		time.QuadPart = timer.stop.QuadPart - timer.start.QuadPart;
		return LIToSecs(time) * 1000.0;
	}
};