#pragma once

#include "base.h"

class CTimer
{
private:
	DISALLOW_COPY_AND_ASSIGN(CTimer);

public:
	CTimer() : timelastframe(0), timeSinceStart(0), timeSinceLastFrame(0)
		, FrameInterval(0)
	{
		Caluating = false;
		DebugCount = 0;

		::QueryPerformanceFrequency(&PerfFreq);
	}

public:
	void beginPerf(bool enable)
	{
		if(enable)
			QueryPerformanceCounter(&PerfStart);
	}

	void endPerf(bool enble, u32& time)
	{
		if (enble)
		{
			QueryPerformanceCounter(&PerfEnd);
			time = (u32)((PerfEnd.QuadPart - PerfStart.QuadPart) * 1000000 / PerfFreq.QuadPart);
		}
	}

	inline u32 getMillisecond() const
	{
		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);
		return (u32)(time.QuadPart * 1000 / PerfFreq.QuadPart);
	}

	inline u32 getMicrosecond() const
	{
		LARGE_INTEGER time;
		QueryPerformanceCounter(&time);
		return (u32)(time.QuadPart * 1000000 / PerfFreq.QuadPart);
	}
	
	void calculateTime();

	u32 getTimeSinceStart() const { return timeSinceStart; }

	u32 getTimeSinceLastFrame() const { return timeSinceLastFrame; }

	bool checkFrameLimit(s32 limit);

public:
	//count
	bool		Caluating;
	u32		DebugCount;

private:
	LARGE_INTEGER	PerfFreq;
	LARGE_INTEGER	PerfStart;
	LARGE_INTEGER	PerfEnd;

	u32		timelastframe;
	u32		timeSinceStart, timeSinceLastFrame;

	u32		FrameInterval;
};