#pragma once

#include "CResourceLoader.h"

class CD3D11ResourceLoader : public CResourceLoader
{
public:
	CD3D11ResourceLoader(bool multithread);
};