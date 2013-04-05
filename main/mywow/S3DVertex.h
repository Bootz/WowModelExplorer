#pragma once

#include "base.h"
#include "core.h"
#include "SColor.h"

struct SVertex_P
{
	vector3df Pos;

	inline void set(const vector3df& p) { Pos = p; }
};

struct SVertex_PC
{
	vector3df	Pos;
	SColor		Color;

	inline void set(const vector3df& p, SColor c) { Pos = p; Color = c; }
};

struct SVertex_PCT
{
	vector3df Pos;
	SColor	Color;
	vector2df TCoords;

	inline void set(const vector3df& p, SColor c, const vector2df& t) { Pos = p; Color = c; TCoords = t; }
};

struct SVertex_PN
{
	vector3df	Pos;
	vector3df	Normal;

	inline void set(const vector3df& p, const vector3df& n) { Pos = p; Normal = n; }
};

struct SVertex_PNC
{
	vector3df	Pos;
	vector3df Normal;
	SColor Color;

	inline void set(const vector3df& p, const vector3df& n, SColor c) { Pos = p; Normal = n; Color = c;}
};

struct SVertex_PNT
{
	vector3df Pos;
	vector3df Normal;
	vector2df TCoords;

	inline void set(const vector3df& p, const vector3df& n, const vector2df& t) { Pos = p; Normal = n; TCoords = t; }
};

struct SVertex_PT 
{
	vector3df Pos;
	vector2df TCoords;

	inline void set(const vector3df& p, const vector2df& t) { Pos = p; TCoords = t; }
};

struct SVertex_PNCT
{
	vector3df	Pos;
	vector3df Normal;
	SColor Color;
	vector2df TCoords;

	inline void set(const vector3df& p, const vector3df& n, SColor c, const vector2df& t) { Pos = p; Normal = n; Color = c; TCoords = t; }
};

struct SVertex_PNCT2
{
	vector3df	Pos;
	vector3df Normal;
	SColor Color;
	vector2df TCoords0;
	vector2df TCoords1;

	inline void set(const vector3df& p, const vector3df& n, SColor c, const vector2df& t0, const vector2df& t1) { Pos = p; Normal = n; Color = c; TCoords0 = t0; TCoords1 = t1; }
};

struct SVertex_PNTW
{
	vector3df Pos;
	vector3df Normal;
	vector2df TCoords;
	f32		Weights[4];

	inline void set(const vector3df& p, const vector3df& n, const vector2df& t) { Pos = p; Normal = n; TCoords = t; }
};

struct SVertex_A
{
	u8		BoneIndices[4];
};


inline u32 getStreamPitchFromType(E_STREAM_TYPE type)
{
	switch (type)
	{
	case EST_P:
		return sizeof(SVertex_P);
	case EST_PC:
		return sizeof(SVertex_PC);
	case EST_PCT:
		return sizeof(SVertex_PCT);
	case EST_PN:
		return sizeof(SVertex_PN);
	case EST_PNC:
		return sizeof(SVertex_PNC);
	case EST_PNT:
		return sizeof(SVertex_PNT);
	case EST_PT:
		return sizeof(SVertex_PT);
	case EST_PNCT:
		return sizeof(SVertex_PNCT);
	case EST_PNCT2:
		return sizeof(SVertex_PNCT2);
	case EST_PNTW:
		return sizeof(SVertex_PNTW);
	case EST_A:
		return sizeof(SVertex_A);

	default:
		_ASSERT(false);
		return 0;
	}
}





