#pragma once

#include "base.h"
#include "IFileSystem.h"
#include <map>

class CFileSystem : public IFileSystem
{
private:
	DISALLOW_COPY_AND_ASSIGN(CFileSystem);

public:
	CFileSystem();
	~CFileSystem();

public:
	virtual IReadFile* createAndOpenFile( const c8* filename, bool binary );
	virtual IWriteFile* createAndWriteFile( const c8* filename, bool binary, bool append = false);

	virtual const c8* getInitialWorkingDirectory() const { return InitialWorkingDirectory; }

	virtual bool createDirectory(const c8* dirname);
	virtual bool deleteDirectory(const c8* dirname);
	virtual bool iterateFiles(const c8* dirname, const c8* ext, ITERATEFILECALLBACK callback, void* args);

	virtual void getAbsolutePath(const c8* filename, c8* outfilename, u32 size );

	virtual const c8* getBaseDirectory() const { return BaseDirectory; }
	virtual const c8* getMpqDirectory() const { return MpqDirectory; }
	virtual bool isFileExists(const c8* filename);
	virtual const c8* getShaderBaseDirectory() const { return ShaderBaseDirectory; }

	virtual void writeLog(E_LOG_TYPE type, const c8* format, ...);

	virtual const c8* getSetting(const c8* key) const;

private:
	void readSetting();
	bool createLogFiles();

	const c8* getLogFileName(E_LOG_TYPE type) const;

private:
	c8		WorkingDirectory[MAX_PATH];
	c8		InitialWorkingDirectory[MAX_PATH];
	c8		BaseDirectory[MAX_PATH];
	c8		MpqDirectory[MAX_PATH];
	c8		ShaderBaseDirectory[MAX_PATH];
	c8		LogDirectory[MAX_PATH];

	IReadFile* SettingFile;
	IWriteFile* LogGxFile;
	IWriteFile* LogResFile;

	std::map<string64, string64>	SettingMap;

	c8		LogString[512];
};