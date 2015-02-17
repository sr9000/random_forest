#pragma once

#include "precompile_header.h"

#include "CompoundRecord.h"

template <typename TRecord>
class ICompoundReader
{
protected:
   typedef boost::any_range <TRecord, boost::forward_traversal_tag, TRecord& const, std::ptrdiff_t> range_type;
   
public:
   ICompoundReader(){}
   
   virtual ~ICompoundReader(){}
   
   virtual range_type get_CompoundRecordRange() = 0;
   
};

typedef boost::shared_ptr<ICompoundReader<CompoundRecord> > CompoundRecordReaderPtr;