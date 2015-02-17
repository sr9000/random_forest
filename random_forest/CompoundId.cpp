#include "precompile_header.h"

#include "CompoundId.h"

CompoundId::CompoundId(const std::string& full_compound)
{
   std::vector <std::string> partsOfStringCompoundId;
   boost::split(partsOfStringCompoundId, full_compound, boost::is_any_of("-"));
   _inchiCore = partsOfStringCompoundId[0];
   _inchiStereo = partsOfStringCompoundId[1];
   _inchiChecksum = partsOfStringCompoundId[2];
}