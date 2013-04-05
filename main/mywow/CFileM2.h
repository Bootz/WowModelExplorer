#pragma once

#include "IFileM2.h"
#include <list>

class IVertexBuffer;
class CFileM2;

class CM2Loader
{
public:
	static bool isALoadableFileExtension( const c8* filename ) { return hasFileExtensionA(filename, "m2"); }

	IFileM2* loadM2( MPQFile* file );
};

class CFileSkin
{
private:
	DISALLOW_COPY_AND_ASSIGN(CFileSkin);

public:
	CFileSkin();
	~CFileSkin();

	bool loadFile(MPQFile* file, CFileM2* m2);

public:
	//ËÑ¼¯¹Ç÷À¶¥µã
	struct SBoneVertEntry
	{
		SVertex_A*		aVertices;
		u32		num;
	};

	typedef std::list<SBoneVertEntry, qzone_allocator<SBoneVertEntry>>		T_BoneVerticesList;

	static const u32 MAX_BONE_BLEND = 4;

public:
	u32		NumGeosets;
	u32		NumTexUnit;
	u32		NumIndices;
	u32		NumBoneVertices;

	CGeoset*		Geosets;
	u16*		Indices;
	SVertex_A*		AVertices;
	
	//vm
	IVertexBuffer*		GVertexBuffer;
	IVertexBuffer*		AVertexBuffer;
	IIndexBuffer*		IndexBuffer;
};

class CFileM2 : public IFileM2
{
private:
	CFileM2();
	~CFileM2();

	friend class CM2Loader;

public:
	virtual bool loadFile(MPQFile* file);
	virtual M2Type getType() const { return Type; }
	virtual const aabbox3df& getBoundingBox() const { return BoundingBox; }
	virtual s16 getAnimationIndex(const c8* name, u32 subIdx = 0);
	virtual u32 getAnimationCount(const c8* name);

	virtual bool buildVideoResources();
	virtual void releaseVideoResources();

	virtual void clearAllActions();
	virtual bool addAction(wow_m2Action* action);
	virtual wow_m2Action* getAction(const c8* name) const;

	u8* getFileData() const { return FileData; }

private:
	void clear();

	void loadVertices();
	void loadBounds();
	void loadTextures();
	void loadAttachments();
	void loadSequences();
	void loadColor();
	void loadTransparency();
	void loadTextureAnimation();
	void loadBones();
	void loadRenderFlags();
	void loadParticleSystems();
	void loadRibbonEmitters();
	void loadModelCameras();

	bool loadSkin(u32 idx);

	void setBoneType(s16 boneIdx);

private:
	u8*			FileData;

	aabbox3df		BoundingBox;
	M2Type		Type;

	typedef std::map<string64, s16, std::less<string64>, qzone_allocator<std::pair<string64, s16>>> T_AnimationLookup;
	T_AnimationLookup	AnimationNameLookup;

	//actions
	typedef std::map<string64, wow_m2Action*, std::less<string64>, qzone_allocator<std::pair<string64, wow_m2Action*>>> T_ActionMap;
	T_ActionMap	ActionMap;
};

