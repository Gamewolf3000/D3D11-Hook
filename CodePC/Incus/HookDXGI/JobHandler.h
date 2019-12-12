#pragma once

#include "SharedMemory.h"

enum JobType : unsigned char
{
	TEXTURE_JOB,
	VERTEX_BUFFER_JOB,
	CONSTANT_BUFFER_JOB,
	NULL_JOB
};

struct Job
{
	JobType type;
	unsigned long long data;
};

class JobHandler
{
private:

	static const unsigned char BUFFER_SLOTS = 64;
	static const unsigned int BUFFER_SIZE = sizeof(Job) * BUFFER_SLOTS + sizeof(unsigned long long) * 2;

	volatile unsigned long long* producedJobs;
	volatile unsigned long long* consumedJobs;

	SharedMemory sharedMemory;
	bool connectedToShared = false;

public:

	JobHandler(bool createSharedMemory);
	~JobHandler();

	void ProduceJob(JobType typeOfJob, unsigned long long jobData);
	bool CheckForJob();
	Job ConsumeJob();

};