#include "stdafx.h"
#include "editor_SceneEnvironment.h"

f32 SceneEnvironment_getSpecularStrength()
{
	return g_Engine->getSceneEnvironment()->SpecularStrength;
}

void SceneEnvironment_setSpecularStrength( f32 specularStrength )
{
	g_Engine->getSceneEnvironment()->SpecularStrength = clamp_(specularStrength, 0.0f, 1.0f);
}