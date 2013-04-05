#pragma once

#pragma comment(lib, "stormlib.lib")
#pragma comment(lib, "freetype.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")
#pragma comment(lib, "lua.lib")
#pragma comment(lib, "Opcode.lib")
#pragma comment(lib, "libmad.lib")
#pragma comment(lib, "libogg.lib")
#pragma comment(lib, "libvorbis.lib")
#pragma comment(lib, "libmad.lib")
#pragma comment(lib, "dsound.lib")

#include "q_memory.h"
#include "temp_memory.h"
#include "core.h"
#include "io.h"
#include "video.h"
#include "wow.h"
#include "scene.h"
#include "renderer.h"
#include "input.h"
#include "audio.h"
#include "collision.h"
#include "ai.h"

#include "CTimer.h"
#include "enginesetting.h"
#include "engine.h"

void createEngine();

void destroyEngine();
