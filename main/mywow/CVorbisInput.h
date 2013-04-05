#pragma once

#include "IAudioInput.h"
//libvorbis
#include "vorbis\vorbisfile.h"

class IReadFile;
class MPQFile;

class CVorbisInput : public IAudioInput
{
private:
	DISALLOW_COPY_AND_ASSIGN(CVorbisInput);

public:
	CVorbisInput();
	~CVorbisInput();

public:
	virtual bool reset();

	virtual bool openFile(const c8* filename);
	virtual void closeFile();

	virtual u32 fillBuffer(void* buffer, u32 size);

private:

#ifdef MPQ_AUDIOINPUT
	MPQFile*		File;
#else
	IReadFile*		File;
#endif

	OggVorbis_File		OggFile;
};