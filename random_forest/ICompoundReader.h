#pragma once

#include "precompile_header.h"

#include "CompoundRecord.h"
//#include "TextCompoundIterator.h"

template <typename TRecord>
class ICompoundReader
{
protected:
   //typedef boost::iterator_facade <TCompoundIterator, CompoundRecord, boost::forward_traversal_tag> iterator_type;
   typedef boost::any_range <TRecord, boost::forward_traversal_tag, TRecord& const, std::ptrdiff_t> range_type;
   
public:
   ICompoundReader(){}
   
   virtual ~ICompoundReader(){}
   
   //virtual iterator_type begin() = 0;
   
   //virtual iterator_type end() = 0;
   
   virtual range_type get_CompoundRange() = 0;
   
};

typedef boost::shared_ptr<ICompoundReader<CompoundRecord> > CompoundRecordReaderPtr;