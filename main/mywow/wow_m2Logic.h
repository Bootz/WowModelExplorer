#pragma once

#include "core.h"
#include <map>
#include "wow_m2action.h"
#include "wow_m2State.h"

class IFileM2;
class IM2SceneNode;

//�漰����m2����϶�������ͷ���Ƶ��߼����ݣ���m2ʹ��
//ʵ����Ϸ�п�����Ϊ�ļ���ȡ��������
class wowM2Logic
{
private:
	DISALLOW_COPY_AND_ASSIGN(wowM2Logic);

public:
	wowM2Logic();
	~wowM2Logic();

public:
	void buildActions(IFileM2* filem2);

private:
	bool addAction(IFileM2* filem2, E_ACTION act, wow_m2Action::E_PLAY_TYPE playType, s32 maxPlaytime, wow_m2Action::SAnimationEntry* entries, u32 count);

	void buildStandAction(IFileM2* fileM2);	
};