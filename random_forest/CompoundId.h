#pragma once

#include "precompile_header.h"

struct CompoundId
{
public:
   std::string _inchiCore;
   std::string _inchiStereo;
   std::string _inchiChecksum;
   
   CompoundId(){};
   
   CompoundId(const CompoundId& other):_inchiCore(other._inchiCore),_inchiStereo(other._inchiStereo),_inchiChecksum(other._inchiChecksum){};
   
   CompoundId(const std::string& full_compound);
   
};