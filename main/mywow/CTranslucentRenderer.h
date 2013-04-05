#pragma once

#include "ISceneRenderer.h"
#include <vector>

class CTransluscentRenderer : public ISceneRenderer
{
public:
	explicit CTransluscentRenderer(u32 quota);
	~CTransluscentRenderer();

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
			//����
			if (unit->distance != c.unit->distance)
				return unit->distance > c.unit->distance;			//��Զ����
			else if(unit->priority != c.unit->priority)
				return unit->priority > c.unit->priority;
			else if (unit->material.MaterialType != c.unit->material.MaterialType)
				return unit->material.MaterialType < c.unit->material.MaterialType;
			if (unit->material.VertexShader != c.unit->material.VertexShader)
				return unit->material.VertexShader < c.unit->material.VertexShader;
			if (unit->material.PsType != c.unit->material.PsType)
				return unit->material.PsType < c.unit->material.PsType;
			else
				return unit->sceneNode < c.unit->sceneNode;
		}
	};

private:
	std::vector<SRenderUnit>		RenderUnits;
	std::vector<SEntry>			RenderEntries;

	u32		Quota;
};