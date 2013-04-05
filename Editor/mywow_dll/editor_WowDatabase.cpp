#include "stdafx.h"
#include "editor_WowDatabase.h"

u32  WowDatabase_getItemCount()
{
	return g_Engine->getWowDatabase()->getItemCount();
}

bool  WowDatabase_getItem( u32 i, editor::SItem* item )
{
	const SItemRecord* r = g_Engine->getWowDatabase()->getItem(i);
	if (!r || wcslen(r->name) > 63)
	{
//		MessageBoxW(NULL, r->name, L"", 0);
		return false;
	}

	wcscpy_s(item->name, DEFAULT_SIZE, r->name);
	item->id = r->id;
	item->type = r->type;
	item->modelId = r->model;
	g_Engine->getWowDatabase()->getSubClassName(r->itemclass, r->subclass, item->subclassname, DEFAULT_SIZE);

	return true;
}

bool WowDatabase_getItemById( s32 id, editor::SItem* item )
{
	const SItemRecord* r = g_Engine->getWowDatabase()->getItemById(id);
	if (!r || wcslen(r->name) > 63)
		return false;

	wcscpy_s(item->name, DEFAULT_SIZE, r->name);
	item->id = r->id;
	item->type = r->type;
	item->modelId = r->model;
	g_Engine->getWowDatabase()->getSubClassName(r->itemclass, r->subclass, item->subclassname, DEFAULT_SIZE);

	return true;
}

u32  WowDatabase_getNpcCount()
{
	return g_Engine->getWowDatabase()->getNpcCount();
}

bool  WowDatabase_getNpc( u32 i, editor::SNpc* npc )
{
	const SNPCRecord* r = g_Engine->getWowDatabase()->getNPC(i);
	if (!r || wcslen(r->name) > 63)
	{
//		MessageBoxW(NULL, r->name, L"", 0);
		return false;
	}

	wcscpy_s(npc->name, DEFAULT_SIZE, r->name);
	npc->modelDisplayId = r->model;
	npc->modelId = g_Engine->getWowDatabase()->getNpcModelId(r->model);
	g_Engine->getWowDatabase()->getNpcTypeName(r->type, npc->type, DEFAULT_SIZE);

	return true;
}

bool  WowDatabase_getRaceId( const c8* racename, u32* id )
{
	return g_Engine->getWowDatabase()->getRaceId(racename, *id);
}

void  WowDatabase_buildItems()
{
	g_Engine->getWowDatabase()->buildItems();
}

bool  WowDatabase_buildNpcs( const c8* filename )
{
	return g_Engine->getWowDatabase()->buildNpcs(filename);
}

void  WowDatabase_buildStartOutfitClass()
{
	g_Engine->getWowDatabase()->buildStartOutfitClass();
}

void WowDatabase_buildMaps()
{
	g_Engine->getWowDatabase()->buildMaps();
}

bool  WowDatabase_getCharacterPath( const c8* raceName, bool female, c8* path, u32 size )
{
	return g_Engine->getWowDatabase()->getCharacterPath(raceName, female, path, size);
}

bool  WowDatabase_itemIsCorrectType( s32 type, s32 slot )
{
	return isCorrectType(type, slot);
}

u32  WowDatabase_getStartOutfitCount( u32 race, bool female )
{
	return g_Engine->getWowDatabase()->getNumStartOutfits(race, female);
}

bool  WowDatabase_getStartOutfit( u32 race, bool female, u32 i, SEntry* entry )
{
	const SStartOutfitEntry* ent = g_Engine->getWowDatabase()->getStartOutfit(race, female, i);
	if (!ent)
		return false;
	
	entry->id = ent->id;
	wcscpy_s(entry->name, DEFAULT_SIZE, ent->name); 
	return true;
}

u32  WowDatabase_getSetCount()
{
	return g_Engine->getWowDatabase()->getItemSetDB()->getNumRecords();
}

bool  WowDatabase_getSet(u32 i, editor::SEntry* entry)
{
	return g_Engine->getWowDatabase()->getSet(i, entry->id, entry->name, DEFAULT_SIZE);
}


u32  WowDatabase_getMapCount()
{
	return g_Engine->getWowDatabase()->getMapDB()->getNumRecords();
}

bool  WowDatabase_getMap( u32 i, editor::SMap* map )
{
	dbc::record r = g_Engine->getWowDatabase()->getMapDB()->getRecord(i);
	if (!r.isValid())
		return false;

	map->id = r.getInt(mapDB::ID);
	str8to16(r.getString(mapDB::InternalName), map->internalname, DEFAULT_SIZE);
	map->type = r.getInt(mapDB::AreaType);
	utf8to16(r.getString(mapDB::Name), map->name, DEFAULT_SIZE);
	return true;
}

u32  WowDatabase_getSpellVisualEffectCount()
{
	return g_Engine->getWowDatabase()->getSpellVisualEffectNameDB()->getNumRecords();
}

bool  WowDatabase_getSpellVisualEffectId( u32 i, int* id )
{
	dbc::record r = g_Engine->getWowDatabase()->getSpellVisualEffectNameDB()->getRecord(i);
	if (!r.isValid())
		return false;

	*id = r.getInt(spellVisualEffectNameDB::ID);
	return true;
}

void  WowDatabase_getMaxCharFeature( u32 race, bool female, SCharFeature* feature )
{
	wowDatabase* wdb = g_Engine->getWowDatabase();
	feature->skinColor = wdb->getMaxSkinColor(race, female);
	feature->faceType = wdb->getMaxFaceType(race, female);
	feature->hairColor = wdb->getMaxHairColor(race, female);
	feature->hairStyle = wdb->getMaxHairStyle(race, female);
	feature->facialHair = wdb->getMaxFacialHairStyle(race, female);
}

bool  WowDatabase_getNpcPath( s32 npcid, c8* path, u32 size )
{
	return g_Engine->getWowDatabase()->getNpcPath(npcid, path, size);
}

bool  WowDatabase_getItemVisualPath( s32 visualId, c8* path, u32 size )
{
	if (visualId == 0)
		return false;

	return g_Engine->getWowDatabase()->getItemVisualPath(visualId, path, size);
}

bool  WowDatabase_getSpellVisualEffectName( s32 visualId, c8* path, u32 size )
{
	dbc::record r = g_Engine->getWowDatabase()->getSpellVisualEffectNameDB()->getByID(visualId);
	if (!r.isValid())
		return false;

	const c8* name = r.getString(spellVisualEffectNameDB::Name);
	if (size < strlen(name) + 1)
		return false;

	strcpy_s(path, size, name);
	path[size-1] =  '\0';

	return true;
}

bool  WowDatabase_getSpellVisualEffectPath( s32 visualId, c8* path, u32 size )
{
	if (visualId == 0)
		return false;

	return g_Engine->getWowDatabase()->getEffectVisualPath(visualId, path, size);
}


