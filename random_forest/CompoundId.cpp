#include "precompile_header.h"

#include "CompoundId.h"

using namespace std;

CompoundId::CompoundId(const string& full_compound)
{
   vector <string> partsOfStringCompoundId;
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

string CompoundId::to_string()
{
   return _inchiCore + "-" + _inchiStereo + "-" + _inchiChecksum;
}