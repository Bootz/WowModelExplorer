#pragma once

#include "ISceneRenderer.h"
#include <vector>

class CMeshRenderer : public ISceneRenderer
{
public:
	explicit CMeshRenderer(u32 quota);
	~CMeshRenderer();

public:
	virtual void addRenderUnit(const SRenderUnit* unit);
	virtual void render(SRenderUnit*& currentUnit, ICamera* cam);

	//��ʵ�ʵ���Ⱦǰ������fog, dlight, ambient
	virtual void begin_setupLightFog(ICamera* cam);
	virtual void end_setupLightFog();

private:
	struct SEntry
	{
		SRenderUnit* unit;

		bool operator<(const SEntry& c) const
		{
			if (unit->material.MaterialType != c.unit->material.MaterialType)
				return unit->material.MaterialType < c.unit->material.MaterialType;
			if (unit->material.VertexShader != c.unit->material.VertexShader)
				return unit->material.VertexShader < c.unit->material.VertexShader;
			if (unit->material.PsType != c.unit->material.PsType)
				return unit->material.PsType < c.unit->material.PsType;
			else if (unit->distance != c.unit->distance)
				return unit->distance < c.unit->distance;			//�ɽ���Զ
			else
				return unit->sceneNode < c.unit->sceneNode;
		}
	};

private:
	std::vector<SRenderUnit>		RenderUnits;
	std::vector<SEntry>			RenderEntries;

	u32		Quota;
};