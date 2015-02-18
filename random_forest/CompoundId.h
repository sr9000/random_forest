#pragma once

#include "precompile_header.h"

struct CompoundId
{
private:
   std::string _inchiCore;
   std::string _inchiStereo;
   std::string _inchiChecksum;
public:
   CompoundId(){};
   
   CompoundId(const CompoundId& other):_inchiCore(other._inchiCore),_inchiStereo(other._inchiStereo),_inchiChecksum(other._inchiChecksum){};
   
   CompoundId(const std::string& full_compound);

   std::string to_string();
   
};