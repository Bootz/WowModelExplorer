#pragma once

class CMiniDump
{
public:
	static void begin();
	static void end();

private:
	static LONG WINAPI TopLevelFilter( struct _EXCEPTION_POINTERS *pExceptionInfo );
};