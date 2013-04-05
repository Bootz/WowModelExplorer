#pragma once

#include "base.h"
#include <map>

class IVertexShader;

class CD3D11VertexDeclaration
{
public:
	static D3D11_INPUT_ELEMENT_DESC	Decl_P[];
	static D3D11_INPUT_ELEMENT_DESC	Decl_PC[];
	static D3D11_INPUT_ELEMENT_DESC	Decl_PCT[];
	static D3D11_INPUT_ELEMENT_DESC	Decl_PN[];
	static D3D11_INPUT_ELEMENT_DESC	Decl_PNC[];
	static D3D11_INPUT_ELEMENT_DESC	Decl_PNT[];
	static D3D11_INPUT_ELEMENT_DESC	Decl_PT[];
	static D3D11_INPUT_ELEMENT_DESC	Decl_PNCT[];
	static D3D11_INPUT_ELEMENT_DESC	Decl_PNCT2[];
	static D3D11_INPUT_ELEMENT_DESC	Decl_VertexModel[];

public:
	CD3D11VertexDeclaration(E_VERTEX_TYPE vtype);
	~CD3D11VertexDeclaration();

	ID3D11InputLayout* getInputLayout(IVertexShader* shader);

private:
	typedef std::map<const void*, ID3D11InputLayout*, std::less<const void*>, qzone_allocator<std::pair<const void*, ID3D11InputLayout*>>> T_LayoutMap;
	T_LayoutMap LayoutMap;

	D3D11_INPUT_ELEMENT_DESC* IAElements;
	u32 Size;
	E_VERTEX_TYPE VertexType;
};