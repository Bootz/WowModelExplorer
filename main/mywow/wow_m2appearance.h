#pragma once

#include "core.h"
#include "SColor.h"

class IM2SceneNode;
class wow_m2instance;

//IM2SceneNode的外观部分
class wow_m2appearance
{
public:
	wow_m2appearance(IM2SceneNode* node);

public:
	void onAnimationEnd();

	bool takeItem(s32 itemid, s32* itemslot);
	void loadStartOutfit(s32 startid, bool deathknight);
	void loadSet(s32 setid);

	void showHelm(bool show);
	void showCape(bool show);

	bool isShowHelm() const;
	bool isShowCape() const;

private:
	IM2SceneNode*			M2SceneNode;
	wow_m2instance*		M2Instance;

public:
	IM2SceneNode*		HelmNode;
	bool HideHelmHair;
	bool HideHelmFacial1;
	bool HideHelmFacial2;
	bool HideHelmFacial3;
};