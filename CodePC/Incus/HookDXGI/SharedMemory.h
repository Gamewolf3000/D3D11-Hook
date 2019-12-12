#pragma once

class SharedMemory
{
private:
	void* data = nullptr;
	unsigned int size = 0;
	void* hMapFile;


public:
	SharedMemory();
	SharedMemory(const wchar_t* identifier, unsigned int sizeOfArea, bool create);
	~SharedMemory();

	bool CreateSharedMemory(const wchar_t* identifier, unsigned int sizeOfArea);
	bool ConnectToSharedMemory(const wchar_t* identifier, unsigned int sizeOfArea);
	void* GetPointer();
	//void WriteData(char* data, unsigned int amount, unsigned int offsetInBuffer);
};