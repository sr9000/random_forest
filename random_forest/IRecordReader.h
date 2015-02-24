#pragma once

#include "precompile_header.h"

template <typename TRecord>
class IRecordReader
{
public:
   typedef boost::any_range <TRecord, boost::forward_traversal_tag, const TRecord&, std::ptrdiff_t> RecordRange;
   
   typedef boost::shared_ptr<IRecordReader<TRecord> > RecordReaderPtr;

   IRecordReader(){}
   
   virtual ~IRecordReader(){}
   
   virtual RecordRange get_RecordRange() = 0;
   
};