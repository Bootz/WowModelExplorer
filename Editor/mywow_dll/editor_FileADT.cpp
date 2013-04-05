#include "stdafx.h"

#include "editor_FileADT.h"

u32 FileADT_getM2Count( IFileADT* adt )
{
	return adt->NumM2FileNames;
}

u32 FileADT_getWMOCount( IFileADT* adt )
{
	return adt->NumWmoFileNames;
}

bool FileADT_getM2FileName( IFileADT* adt, u32 index, c8* path, u32 size, bool shortname )
{
	const c8* filename = adt->getM2FileName(index);
	if (shortname)
	{
		c8 sname[DEFAULT_SIZE];
		getFileNameA(filename, sname, DEFAULT_SIZE);
		strcpy_s(path, size, sname);
	}
	else
	{
		strcpy_s(path, size, filename);
	}
	
	return true;
}

bool FileADT_getWMOFileName( IFileADT* adt, u32 index, c8* path, u32 size, bool shortname )
{
	const c8* filename = adt->getWMOFileName(index);
	if (shortname)
	{
		c8 sname[DEFAULT_SIZE];
		getFileNameA(filename, sname, DEFAULT_SIZE);
		strcpy_s(path, size, sname);
	}
	else
	{
		strcpy_s(path, size, filename);
	}
	return true;
}
