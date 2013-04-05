#pragma once

#include "base.h"
#include "core.h"

class IFileSystem;
class MPQArchive;
class MPQFile;

class wowEnvironment
{
public:
	wowEnvironment(IFileSystem* fs);
	~wowEnvironment();

public:
	MPQFile* openFile(const c8* filename, bool tempfile = true);

	bool exists(const c8* filename);
	s32 getSize(const c8* filename);

	const c8* getLocale() const { return Locale.c_str(); }
	const c8* getLocalePath() const { return LocalePath; }

	typedef void (*MPQFILECALLBACK)(const c8* filename, void* param);

	void iterateFiles(const c8* ext, MPQFILECALLBACK callback, void* param);

private:
	bool loadWowArchives(IFileSystem* fs);
	void unloadWowArchives();

private:
	LENTRY	MpqArchiveList;

	string8	Locale;

	c8		LocalePath[MAX_PATH];

};
