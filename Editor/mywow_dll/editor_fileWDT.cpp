#include "stdafx.h"
#include "editor_FileWDT.h"

u32 FileWDT_getTileCount( IFileWDT* wdt )
{
	return wdt->getTileCount();
}

bool FileWDT_getTile( IFileWDT* wdt, u32 index, u32* row, u32* col )
{
	STile* tile = wdt->getTile(index);
	if (!tile)
		return false;
	*row = tile->row;
	*col = tile->col;
	return true;
}

IFileADT* FileWDT_loadADT( IFileWDT* wdt, u32 row, u32 col, bool simple )
{
	STile* tile = wdt->getTile((u8)row, (u8)col);
	if (!tile)
		return NULL;

	if(wdt->loadADT(tile, simple))
	{
		return tile->fileAdt;
	}
	return NULL;
}

void FileWDT_unloadADT( IFileWDT* wdt, IFileADT* adt )
{
	for (u32 i=0; i<wdt->getTileCount(); ++i)
	{
		STile* tile = wdt->getTile(i);
		if (tile->fileAdt == adt && tile->fileAdt)
		{
			wdt->unloadADT(tile);
			break;
		}
	}
}
