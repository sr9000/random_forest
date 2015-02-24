#include "precompile_header.h"

#include "CompoundId.h"

using namespace std;

CompoundId::CompoundId(const string& full_compound)
{
   vector <string> partsOfStringCompoundId;
   boost::split(partsOfStringCompoundId, full_compound, boost::is_any_of("-"));
   if (partsOfStringCompoundId.size() == 3)
   {
      _inchiCore = partsOfStringCompoundId[0];
      _inchiStereo = partsOfStringCompoundId[1];
      _inchiChecksum = partsOfStringCompoundId[2];
   }
   else
   {
      throw CompoundIdException();
   }
}

string CompoundId::to_string()
{
   return _inchiCore + "-" + _inchiStereo + "-" + _inchiChecksum;
}

CompoundId& CompoundId::operator=(const CompoundId& other)
{
   _inchiCore = other._inchiCore;
   _inchiStereo = other._inchiStereo;
   _inchiChecksum = other._inchiChecksum;
   return *this;
}