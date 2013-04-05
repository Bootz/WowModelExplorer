#pragma once

#include "CResourceLoader.h"

class CD3D9ResourceLoader : public CResourceLoader
{
public:
	explicit CD3D9ResourceLoader(bool multithread);
};