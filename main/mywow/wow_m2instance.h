#pragma once

#include "core.h"
#include "wow_enums.h"
#include "IFileM2.h"
#include "SMaterial.h"

class ITexture;
class IVertexBuffer;
class CFileSkin;

struct CharTexturePart				//纹理组合
{
	c8  Name[MAX_PATH];
	s32 Region;
	s32 Layer;

	bool operator<(const CharTexturePart& c) const
	{
		return Layer < c.Layer;
	}
};

struct CharTexture				//使用临时内存
{
	CharTexture();
	~CharTexture();

	void addLayer(const c8* name, s32 region, s32 layer);
	bool addItemLayer(const c8* name, s32 region,  u32 gender, s32 layer);
	bool makeItemTexture(s32 region,  u32 gender, const c8* name, c8* outname);

	ITexture* compose(bool pandaren);

	static const int MAX_TEX_PART_SIZE = 40;

	CharTexturePart*		TextureParts;
	u32		TexPartCount;	
};

struct SDynGeoset
{
	~SDynGeoset()
	{
		for (u32 i=0; i<NumUnits; ++i)
		{
			delete Units[i].BoneMats;
			delete Units[i].BoneMatrixArray;
		}
		delete[] Units;
	}

	struct SUnit
	{
		bool		Enable;
		matrix4A16*		BoneMats;
		SBoneMatrixArray*		BoneMatrixArray;
	};

	LENTRY		Link;
	ITexture*		Texture0;
	SUnit*		Units;
	matrix4			TextureMatrix;
	SColor	emissive;
	u32		NumUnits;

	bool		NoAlpha;
	bool				UseTextureAnim;
};

struct SDynBone					//骨骼动态信息
{
	SDynBone()
		: transPivot(0,0,0), trans(0,0,0), scale(1,1,1), rot(0,0,0,1) {}
	matrix4 mat;
	vector3df		transPivot;

	//local
	vector3df trans, scale;
	quaternion rot;		
};

struct SAttachmentEntry
{
	SAttachmentEntry() : slot(-1), id(-1), attachIndex(-1), scale(1.0f), node(NULL)
	{
		::memset(modelpath, 0, MAX_PATH);
		::memset(texpath, 0, MAX_PATH);
		InitializeListHead(&Link);
	}

	LENTRY	Link;

	s16		slot;
	s16		id;
	s16		attachIndex;
	c8		modelpath[MAX_PATH];
	c8		texpath[MAX_PATH];
	f32		scale;
	void*		node;
};

//只有Character类型才有的信息
struct SCharacterInfo		 
{
	SCharacterInfo(bool npc) : IsNpc(npc)
	{
		HasRobe = false;
		DeathKnight = false;
		ShowCape = true;
		CapeID = 1;
		Race = 0;
		Gender = 0;
		Blink = false;
		CloseLHand = false;
		CloseRHand = false;

		SkinColor = 0;
		FaceType = 0;
		HairColor = 0;
		HairStyle = 1;
		FacialHair = 0;

		HelmHideFacial1 = false;
		HelmHideFacial2 = false;
		HelmHideFacial3 = false;
		HelmHideHair = false;

		::memset(Equipments, 0, sizeof(Equipments));
		::memset(Geosets, 0, sizeof(Geosets));
#ifdef EDITOR
		::memset(BodyTextureFileNames, 0, sizeof(BodyTextureFileNames));
#endif
	}

	u32		SkinColor;
	u32		FaceType;
	u32		HairColor;
	u32		HairStyle;
	u32		FacialHair;

	u32			CapeID;
	u32		Race;
	u32		Gender;

	bool		DeathKnight;
	bool		HelmHideFacial1;
	bool		HelmHideFacial2;
	bool		HelmHideFacial3;
	bool		HelmHideHair;			//头盔遮挡头发
	bool		ShowCape;
	bool		IsNpc;
	bool		HasRobe;
	bool		Blink;			//眨眼
	bool		CloseRHand;		//握右拳
	bool		CloseLHand;		//握左拳

	int		Equipments[NUM_CHAR_SLOTS];
	int		Geosets[NUM_GEOSETS];

#ifdef EDITOR
	c8			BodyTextureFileNames[NUM_REGIONS][MAX_PATH];
#endif
};

//在m2静态数据上的动态角色信息
class wow_m2instance
{
public:
	wow_m2instance(IFileM2* m2, bool npc);
	~wow_m2instance();

public:
	IFileM2* getMesh() const { return Mesh; }

	//character
	void updateCharacter();			//更新模型显示信息
	void animateBones(u32 anim, u32 time, u32 lastingtime, f32 blend, const matrix4* billboardRot);
	void disableBones();
	void animateColors(u32 anim, u32 time);
	void animateTextures(u32 anim, u32 time);
	void solidColors();

	//clothes
	void updateEquipments(s32 slot, s32 itemid);
	s32 getItemSlot(s32 itemid);

	//weapon, attachment
	bool slotHasModel(s32 slot);
	void setM2Equipment(s32 slot, s32 itemid, SAttachmentEntry* entry1, SAttachmentEntry* entry2);

	//startoutfit
	void dressStartOutfit(s32 startid);

	//set
	void dressSet(s32 setid);

	//npc
	bool updateNpc(s32 npcid);

	//item
	void setItemTexture(ITexture* tex) { setReplaceTexture(TEXTURE_ITEM, tex); }

	bool setGeosetMaterial(u32 subset, SMaterial& material);

	void buildVisibleGeosets();

public:
	SCharacterInfo*		CharacterInfo;

	SDynGeoset*	DynGeosets;			
	CFileSkin*		CurrentSkin;
	SDynBone*		DynBones;

	bool*			ShowAttachments;
	ITexture*		ReplaceTextures[NUM_TEXTURETYPE];				//可替换的纹理

	LENTRY		VisibleGeosetList;
	aabbox3df		AnimatedBox;

	//
	f32			ModelAlpha;
	SColor	ModelColor;

	bool		EnableModelAlpha;
	bool		EnableModelColor;
	bool			ShowParticles;
	bool			ShowRibbons;

private:
	void setReplaceTexture(ETextureTypes type, ITexture* texture);

	//character
	//设置服装类型的装备(不需要另外的模型)
	void addClothesEquipment(s32 slot, s32 itemnum, s32 layer, CharTexture& tex, bool lookup=true);
	void dressupCharacter(CharTexture& charTex);
	int getSlot(int type) const;
	static int getClothesSlotLayer( int slot )	;

	void calcBone(u8 i, u32 anim, u32 time, f32 blend, bool enableScale, const matrix4* billboardRot, aabbox3df* animatedBox=NULL);				//i: indexinGlobal

	bool isBlinkGeoset(u32 index) const;
	void getEquipScale(f32& shoulder, f32& weapon) const;

	void calcTextureAnim(u32 c, u32 anim, u32 time);

private:
	struct SHint
	{
		s32		transHint;
		s32		scaleHint;
		s32		rotHint;
	};

	struct SColorHint
	{
		s32		colorHint;
		s32		opacityHint;
		s32		transparencyHint;
	};

private:
	u32		LastBoneAnim, LastColorAnim, LastTextureAnim;
	u32		LastBoneTime, LastColorTime, LastTextureTime;

	IFileM2*		Mesh;
	SHint*		BoneHints;
	SHint*		TextureAnimHints;
	SColorHint*		ColorHints;
	bool*		Calcs;
};
