#pragma once

#include "precompile_header.h"

#include "CompoundId.h"

struct PredRecord
{
public:
   CompoundId _compoundId;

   PredRecord(){};
   
   PredRecord(const PredRecord& other)
      :_compoundId(other._compoundId)
   {};
   
};

typedef boost::optional<PredRecord> PredRecordOptional;
typedef boost::any_range <PredRecordOptional, boost::forward_traversal_tag, const PredRecordOptional&, std::ptrdiff_t> PredRecordRange;