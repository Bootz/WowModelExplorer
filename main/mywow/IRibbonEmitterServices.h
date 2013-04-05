#pragma once

#include "base.h"
#include "wow_particle.h"
#include "S3DVertex.h"
#include "VertexIndexBuffer.h"

//给ribbon提供segment池和硬件缓存
class IRibbonEmitterServices
{
public:
	IRibbonEmitterServices() : CurrentOffset(0) { Vertices = NULL; BufferParam.clear(); BufferParam.vType = EVT_PCT; }
	virtual ~IRibbonEmitterServices() {}

	virtual void updateVertices(u32 numVertices, s32& baseVertIndex) = 0;
	virtual RibbonSegment* getSegment()= 0;
	virtual void putSegment(RibbonSegment* s) = 0;

	virtual u32 getActiveSegmentsCount() const = 0;

public:
	SBufferParam	BufferParam;

	SVertex_PCT*		Vertices;
	u32		CurrentOffset;
};