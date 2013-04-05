#pragma once

#include "base.h"
#include <d3d9.h>

class CD3D9VertexDeclaration
{
private:
	DISALLOW_COPY_AND_ASSIGN(CD3D9VertexDeclaration);
public:
	CD3D9VertexDeclaration() {}

public:
	static D3DVERTEXELEMENT9	Decl_P[];
	static D3DVERTEXELEMENT9	Decl_PC[];
	static D3DVERTEXELEMENT9	Decl_PCT[];
	static D3DVERTEXELEMENT9	Decl_PN[];
	static D3DVERTEXELEMENT9	Decl_PNC[];
	static D3DVERTEXELEMENT9	Decl_PNT[];
	static D3DVERTEXELEMENT9	Decl_PT[];
	static D3DVERTEXELEMENT9	Decl_PNCT[];
	static D3DVERTEXELEMENT9	Decl_PNCT2[];
	static D3DVERTEXELEMENT9	Decl_VertexModel_M[];
};