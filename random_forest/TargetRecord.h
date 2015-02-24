#pragma once

#include "precompile_header.h"

#include "CompoundId.h"

struct TargetRecord
{
public:
   CompoundId _compoundId;

   uint8_t _target;

   TargetRecord(){};
   
   TargetRecord(const TargetRecord& other)
      :_compoundId(other._compoundId),_target(other._target)
   {};
   
};

typedef boost::optional<TargetRecord> TargetRecordOptional;
typedef boost::any_range <TargetRecordOptional, boost::forward_traversal_tag, const TargetRecordOptional&, std::ptrdiff_t> TargetRecordRange;