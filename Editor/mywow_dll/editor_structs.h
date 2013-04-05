#pragma once

 namespace editor
 {
	struct SItem
	{
		c16 name[DEFAULT_SIZE];
		s32 id;
		s32 type;
		s32 modelId;
		c16 subclassname[DEFAULT_SIZE];	
	};

	struct SNpc
	{
		c16 name[DEFAULT_SIZE];
		s32 modelDisplayId;
		s32 modelId;
		c16 type[DEFAULT_SIZE];
	};

	struct SEntry
	{
		c16 name[DEFAULT_SIZE];
		s32 id;
	};

	struct SMap
	{
		s32 id;
		c16 internalname[DEFAULT_SIZE];
		c16 name[DEFAULT_SIZE];
		s32 type;
	};

	struct SAnimation
	{
		c8  name[DEFAULT_SIZE];
		u32 subIndex;
		u32 length;
		u32 animIndex;
		s32	next;
	};

	struct SCharFeature
	{
		u32		skinColor;
		u32		faceType;
		u32		hairColor;
		u32		hairStyle;
		u32		facialHair;
	};

	enum E_SCENE_DEBUG_PART		//场景的debug信息
	{
		ESDP_BASE = 0,
		ESDP_M2_GEOSETS,
		ESDP_M2_PARTICLES,

		ESDP_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
	};

	enum E_MODEL_PART			//模型的显示/隐藏部分
	{
		EMP_ALL = 0,
		EMP_HEAD,
		EMP_CAPE,
		EMP_SHOULDER,
		EMP_LEFTHAND,
		EMP_RIGHTHAND,

		EMP_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
	};

	enum E_MODEL_EDIT_PART				//模型的编辑显示
	{
		EEP_MODEL = 0,
		EEP_PARTICLES,
		EEP_RIBBONS,
		EEP_BOUNDINGBOX,
		EEP_BONES,
		EEP_ATTACHMENTPOINTS,

		EEP_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
	};

	enum E_WMO_EDIT_PART
	{
		EWP_WMO = 0,
		EWP_DOODADS,
		EWP_BOUNDINGBOX,

		EWP_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
	};

	enum E_OVERRIDE_WIREFRAME
	{
		EOW_NONE = 0,
		EOW_WIREFRAME,
		EOW_WIREFRAME_SOLID,
		EOW_WIREFRAME_ONECOLOR,

		EOW_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
	};

	enum E_MODEL_REPLACE_TEXTURE				//模型的纹理
	{
		EMRT_BODY = 0,
		EMRT_CAPE,
		EMRT_HAIR,
		EMRT_FUR,
		EMRT_NPC1,
		EMRT_NPC2,
		EMRT_NPC3,
		EMRT_FORCE_32_BIT_DO_NOT_USE = 0x7fffffff
	};

	struct SFileM2
	{
		c8		name[DEFAULT_SIZE];
		c8		longname[256];
		u32		numVertices;
		u32		numBoundingVerts;
		u32		numBoundingTriangles;
		u32		numTextures;
		u32		numTexLookup;
		u32		numAttachLookup;
		u32		numGlobalSequences;
		u32		numColors;
		u32		numTransparencies;
		u32		numTransparencyLookup;
		u32		numTexAnim;
		u32		numAnimations;
		u32		numBones;
		u32		numRenderFlags;
		u32		numParticleSystems;
		u32		numRibbonEmitters;

		//skin
		u32		numGeosets;
		u32		numTexUnit;
	};

	struct SRenderFlag
	{
		u16	flags;
		u16 blend;

		bool lighting;
		bool zwrite;
	};

	struct SGeoset 
	{
		u32		VCount;
		u32		ICount;
		u32		GeoID;

		s16		TexID;
		u16		rfIndex;
		s16		ColorIndex;
		s16		TransIndex;
		s16		TexAnimIndex;
	};

	struct SM2ChildSceneNodes
	{
		IM2SceneNode* head;
		IM2SceneNode* leftShoulder;
		IM2SceneNode* rightShoulder;
		IM2SceneNode* leftHand;
		IM2SceneNode* rightHand;
	};

	struct SFileWMO
	{
		c8		name[DEFAULT_SIZE];
		c8		longname[256];
		u32		numMaterials;
		u32		numGroups;
		u32		numPortals;
		u32		numLights;
		u32		numModels;
		u32		numDoodads;
		u32		numDoodadSets;
		u32		wmoID;
	};

	struct SWMOGroup
	{
		c8	name[DEFAULT_SIZE];
		u32 numBatches;
		u32 numLights;
		u32 numDoodads;
		u32 ICount;
		u32 VCount;
	};

 }