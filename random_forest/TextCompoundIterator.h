#pragma once

#include "precompile_header.h"

#include "CompoundRecord.h"
#include "ICompoundIterator.h"
#include "TextCompoundReader.h"

class TextCompoundIterator: public boost::iterator_facade <TextCompoundIterator, CompoundRecord, boost::forward_traversal_tag>
{
   friend class TextCompoundReader;
   
protected:
   TextCompoundIterator();
   
   TextCompoundIterator(TextCompoundIterator& const);
   
   boost::filesystem::path _path;
   
   //implementation boost::iterator_facade <TextCompoundIterator, CompoundRecord, boost::forward_traversal_tag>
   friend class boost::iterator_core_access;
   
   void increment();
   
   bool equal(const TextCompoundIterator& other) const;
   
   CompoundRecord& dereference() const;
   
private:
   std::ifstream _inputFileStream;
   
   CompoundRecord _currentCompoundRecord;
   
};