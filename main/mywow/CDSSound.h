#pragma once

#include "ISound.h"
#include <dsound.h>

class IAudioInput;
struct SAudioSetting;

//��ʾһ����Ƶ�ļ���ds��������֣����ݲ�����CXXXInput��� 
class CDSSound : public ISound
{
public:
	CDSSound(LPDIRECTSOUND pIDS, E_SOUND_TYPE type, u32 index);
	~CDSSound();

public:
	virtual bool load(const c8* filename);
	virtual void unload();
	virtual bool play(bool loop, FN_SOUND_CALLBACK callback = NULL);
	virtual void stop();
	virtual void reset();
	virtual bool isPlaying() const;
	virtual bool isStopped() const;
	virtual void setVolume(f32 vol);
	virtual f32 getVolume() const { return Volume; }
	virtual u32 getIndex() const { return Index; }

protected:
	bool restoreBuffer(bool& restored, s32 timeout);
	bool handleStreamNotification();
	bool recreateDSBuffer(const SAudioSetting& setting);
	void fillBufferWithSilence();

protected:
	LPDIRECTSOUND		pIDSound;

	IAudioInput*		AudioInput;
	
	LPDIRECTSOUNDBUFFER		pIDSBuffer;
	HANDLE		NotificationEvent;
	LPDIRECTSOUNDNOTIFY		pIDNotify;
	DSBPOSITIONNOTIFY*	PosNotifyArray;

	FN_SOUND_CALLBACK	Callback;

	mutable CRITICAL_SECTION		cs;				

	u32  BufferSize;
	u32  NotifySize;
	u32	NextWriteOffset;
	u32	SilenceCount;
	u32		Index;

	f32		Volume;

	bool	Loop;
	bool	FillNextNotificationWithSilence;

	WAVEFORMATEX		WFX;
	WAVEFORMATEX		LastWFX;

	friend class CDSAudioPlayer;
};