#pragma once

#include "precompile_header.h"

struct CompoundId
{
public:
   CompoundId();
   
   CompoundId(const std::string& full_compound);
   
   std::string _inchiCore, _inchiStereo, _inchiChecksum;
   
};