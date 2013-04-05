#pragma once

#include "base.h"
#include "wow_particle.h"
#include "S3DVertex.h"
#include "VertexIndexBuffer.h"

//������ϵͳ�ṩ���ӳغ�Ӳ������
class IParticleSystemServices
{
public:
	IParticleSystemServices() : CurrentOffset(0) { Vertices=NULL; BufferParam.clear(); BufferParam.vType = EVT_PCT; }
	virtual ~IParticleSystemServices() {}

	virtual void updateVertices(u32 numVertices, s32& baseVertIndex) = 0;
	virtual Particle* getParticle()= 0;
	virtual void putParticle(Particle* p) = 0;

	virtual void setParticleDensity(float density) = 0;		//���ӷ����ܶ�
	virtual float getParticleDensity() const = 0;
	virtual f32 getParticleDynamicDensity() const = 0;

	virtual u32 getActiveParticlesCount() const = 0;

	virtual void adjustParticles() = 0;		//ÿ֡������������

public:
	SBufferParam		BufferParam;

	SVertex_PCT*		Vertices;

	u32		CurrentOffset;
	
};