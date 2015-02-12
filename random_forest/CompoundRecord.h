#pragma once

#include "precompile_header.h"

#include "CompoundId.h"

struct CompoundRecord
{
public:
   CompoundId _compoundId;
   
   std::vector <uint32_t> _features;
   
};

typedef boost::any_range <CompoundRecord, boost::forward_traversal_tag, CompoundRecord& const, std::ptrdiff_t> CompoundRecordRange;