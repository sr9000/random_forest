#include "precompile_header.h"

#include "CompoundId.h"

CompoundId::CompoundId(const std::string& full_compound)
{
   std::vector <std::string> partsOfStringCompoundId;
   boost::split(partsOfStringCompoundId, full_compound, boost::is_any_of("-"));

   if (partsOfStringCompoundId.size() > 0)
      _inchiCore = partsOfStringCompoundId[0];
   else
      _inchiCore = "";

   if (partsOfStringCompoundId.size() > 1)
      _inchiStereo = partsOfStringCompoundId[1];
   else
      _inchiStereo = "";

   if (partsOfStringCompoundId.size() > 2)
      _inchiChecksum = partsOfStringCompoundId[2];
   else
      _inchiChecksum = "";
}