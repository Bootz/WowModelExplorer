#pragma once

#include "IFileADT.h"
#include "S3DVertex.h"
#include "VertexIndexBuffer.h"

class CADTLoader
{
public:
	static bool isALoadableFileExtension( const c8* filename ) { return hasFileExtensionA(filename, "adt"); }

	IFileADT* loadADT( MPQFile* file, bool simple );
};

class CFileADT : public IFileADT
{
private:
	CFileADT();
	~CFileADT();

	friend class CADTLoader;

public:
	virtual bool loadFile(MPQFile* file);
	virtual bool loadFileSimple(MPQFile* file);				//load obj only
	virtual u8* getFileData() const { return FileData; }
	virtual const CMapChunk* getChunk(u8 row, u8 col) const;
	virtual aabbox3df getBoundingBox() const { return Box; }

	virtual const c8* getM2FileName(u32 index) const;
	virtual const c8* getWMOFileName(u32 index) const;

	virtual bool buildVideoResources();
	virtual void releaseVideoResources();

	virtual IVertexBuffer* getVBuffer() const { return VertexBuffer; }
	virtual E_VERTEX_TYPE getVertexType() const { return EVT_PNCT2; }
	virtual u32 getChunkVerticesOffset(u8 row, u8 col) const { return (row * 16 + col) * 145; }
	virtual ITexture* getBlendMap() const { return BlendMap; }

	virtual const SM2Instance* getM2Instance(u32 index) const { return &M2Instances[index]; }
	virtual const SWmoInstance* getWMOInstance(u32 index) const { return &WmoInstances[index]; }

private:
	void readChunk( MPQFile* file, u8 row, u8 col, u32 lastpos); 
	
	void loadObj0();

	bool loadFileSimple();

	bool loadTex(u32 n);

	void buildTexcoords();

private:
	struct SChunkM2List
	{
		std::vector<u32>		m2InstList;
	};

	struct STex
	{
		STex(ITexture* tex, bool spec) : texture(tex), specular(spec) {}
		ITexture* texture;
		bool	specular;
	};

private:
	u8*			FileData;

	//chunk
	SVertex_PNCT2*		Vertices;
	IVertexBuffer*		VertexBuffer;
	ITexture*		BlendMap;				//整个adt的blend map,由16 X 16个chunk的map合成

	aabbox3df	Box;

	CMapChunk		Chunks[16][16];

	std::vector<STex>		Textures;
	
	//小物体
	SChunkM2List		LittleChunkM2List[16][16];
	//大物体
	SChunkM2List		BigChunkM2List;
};