#pragma once

#include "ISceneRenderer.h"
#include <vector>

class CTerrainRenderer : public ISceneRenderer
{
public:
	CTerrainRenderer(u32 lowresQuota, u32 highresQuota);
	~CTerrainRenderer();

public:
	virtual void addRenderUnit(const SRenderUnit* unit);
	virtual void render(SRenderUnit*& currentUnit, ICamera* cam);

	//在实际的渲染前后设置fog, dlight, ambient
	virtual void begin_setupLightFog(ICamera* cam);
	virtual void end_setupLightFog();

private:
	struct SEntry
	{
		SRenderUnit* unit;

		bool operator<(const SEntry& c) const
		{
			if (unit->bufferParam.vbuffer0 != c.unit->bufferParam.vbuffer0)
				return unit->bufferParam.vbuffer0 < c.unit->bufferParam.vbuffer0;			//相同adt的vbuffer相同，可减少切换
			else
				return unit->sceneNode < c.unit->sceneNode;
		}
	};

private:
	std::vector<SRenderUnit>		RenderUnits;
	std::vector<SEntry>			LowRenderEntries;
	std::vector<SEntry>			HighRenderEntries;

	u32		LowResQuota;
	u32		HighResQuota;
};