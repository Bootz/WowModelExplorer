#pragma once

#include <windows.h>
#include <crtdbg.h>

class CMutex
{
public:
	explicit CMutex(HANDLE mutex) : Mutex(mutex), Multithread(true)
	{
		if (WAIT_OBJECT_0 != ::WaitForSingleObject(Mutex, INFINITE))			
		{ _ASSERT(false); }
	}

	CMutex(HANDLE mutex, bool multithread) : Mutex(mutex), Multithread(multithread)
	{
		if (Multithread)
		{
			if (WAIT_OBJECT_0 != ::WaitForSingleObject(Mutex, INFINITE))			
			{ _ASSERT(false); }
		}
	}

	~CMutex()
	{
		if(Multithread)
			::ReleaseMutex(Mutex);
	}
private:
	HANDLE Mutex;
	bool Multithread;
};