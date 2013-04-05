#pragma once

#include "q_memory.h"

#include <stddef.h>
#include <assert.h>
#include <windows.h>

extern CRITICAL_SECTION g_tempCS;

void* Z_AllocateTempMemory( int size );
void Z_FreeTempMemory( void *buf );

inline void* Z_AllocateTempMemory( int size )
{
	void* p = NULL;

	::EnterCriticalSection(&g_tempCS);
	if (Z_AvailableTempMemory() > size)
		p = T_TagMalloc(size, TAG_TEMP);
	::LeaveCriticalSection(&g_tempCS);

	if (p)
		return p;

	return malloc(size);
}

inline void Z_FreeTempMemory( void *buf )
{
	bool ret;
	::EnterCriticalSection(&g_tempCS);
	ret = T_Free(buf);
	::LeaveCriticalSection(&g_tempCS);

	if (!ret)
		free(buf);
}