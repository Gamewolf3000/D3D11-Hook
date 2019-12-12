#include "JobHandler.h"
#include "Windows.h"

JobHandler::JobHandler(bool createSharedMemory)
{
	if (createSharedMemory)
	{
		connectedToShared = sharedMemory.CreateSharedMemory(L"D3D11HOOKMEMORY", BUFFER_SIZE);
		auto memPtr = sharedMemory.GetPointer();
		producedJobs = ((unsigned long long*)memPtr);
		consumedJobs = (((unsigned long long*)memPtr) + 1);
		*producedJobs = 0;
		*consumedJobs = 0;
	}
	else
	{
		connectedToShared = sharedMemory.ConnectToSharedMemory(L"D3D11HOOKMEMORY", BUFFER_SIZE);
		auto memPtr = sharedMemory.GetPointer();
		producedJobs = ((unsigned long long*)memPtr);
		consumedJobs = (((unsigned long long*)memPtr) + 1);
	}
}

JobHandler::~JobHandler()
{
	
}

void JobHandler::ProduceJob(JobType typeOfJob, unsigned long long jobData)
{
	if (!connectedToShared)
		return;

	while (*producedJobs - *consumedJobs >= BUFFER_SLOTS)
	{
		//SPIN WAIT WHILE WE WAIT FOR THE CONSUMER TO CONSUME A JOB
	}

	Job* jobPos = (Job*)((unsigned long long*)(sharedMemory.GetPointer()) + 2) + *producedJobs % BUFFER_SLOTS;
	jobPos->type = typeOfJob;
	jobPos->data = jobData;
	++(*producedJobs);
}

bool JobHandler::CheckForJob()
{
	if (!connectedToShared)
		return false;

	return *producedJobs > *consumedJobs;
}

Job JobHandler::ConsumeJob()
{
	Job* jobPos = (Job*)((unsigned long long*)(sharedMemory.GetPointer()) + 2) + *consumedJobs % BUFFER_SLOTS;
	Job toReturn;
	toReturn.type = jobPos->type;
	toReturn.data = jobPos->data;
	*consumedJobs++;
	return toReturn;
}
