#pragma once

#include "IWMOSceneNode.h"

struct SWMOGroup;
struct SWMOMaterial;
struct SMaterial;

class CWMOSceneNode : public IWMOSceneNode
{
public:
	CWMOSceneNode(IFileWMO* wmo, ISceneNode* parent);
	virtual ~CWMOSceneNode();

public:
	//IWMOSceneNode
	virtual IFileWMO* getFileWMO() const { return Wmo; }
	virtual void enableFog(bool enable);

	//ISceneNode
	virtual void registerSceneNode(bool frustumcheck = true);
	virtual aabbox3df getBoundingBox() const;
	virtual void render();
	virtual bool isNodeEligible() const;
	virtual void onUpdated();

protected:
	struct	SDynBatch
	{
		SDynBatch() : visible(false) {}

		aabbox3df worldbox;
		bool visible;
	};

	struct SDynGroup
	{
		SDynGroup() : visible(false), distancesq(0.0f), batches(NULL) {}
		~SDynGroup() { delete[] batches; }

		aabbox3df		worldbox;
		f32	 distancesq;

		SDynBatch*		batches;
		bool visible;
	};

protected:
	void renderWMOGroup(u32 groupIndex, u32 batchIndex);

	void setMaterial(const SWMOMaterial* material, SMaterial& mat);

protected:
	IFileWMO*  Wmo;
	SDynGroup*		DynGroups;

	bool EnableFog;
};