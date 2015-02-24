#pragma once

#include "precompile_header.h"

#include "CompoundId.h"

struct CompoundRecord
{
public:
   CompoundId _compoundId;
   
   std::vector <uint32_t> _features;
   
   CompoundRecord(){};
   
   CompoundRecord(const CompoundRecord& other)
      :_compoundId(other._compoundId),_features(other._features)
   {};
   
};

typedef boost::optional<CompoundRecord> CompoundRecordOptional;
typedef boost::any_range <CompoundRecordOptional, boost::forward_traversal_tag, const CompoundRecordOptional&, std::ptrdiff_t> CompoundRecordRange;