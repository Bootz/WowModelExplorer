#pragma once

#include "editor_base.h"

MW_API  u32 FileADT_getM2Count(IFileADT* adt);
MW_API  u32 FileADT_getWMOCount(IFileADT* adt);

MW_API  bool FileADT_getM2FileName(IFileADT* adt, u32 index, c8* path, u32 size, bool shortname);
MW_API  bool FileADT_getWMOFileName(IFileADT* adt, u32 index, c8* path, u32 size, bool shortname);