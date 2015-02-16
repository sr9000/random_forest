#pragma once

#include "precompile_header.h"

#include "CompoundRecord.h"
#include "ICompoundIterator.h"
#include "TextCompoundReader.h"

namespace TextCompoundIteratorState
{
	enum TextCompoundIteratorState
	{
		Begin,
		Proceed,
		Finish,
		Unknown
	};
};

class TextCompoundIterator: public boost::iterator_facade <TextCompoundIterator, CompoundRecord, boost::forward_traversal_tag>
{
   friend class TextCompoundReader;
   
protected:
   TextCompoundIterator();
   
   TextCompoundIterator(const TextCompoundIterator&);
   
   boost::filesystem::path _path;

   TextCompoundIteratorState::TextCompoundIteratorState _state;
   
   //implementation boost::iterator_facade <TextCompoundIterator, CompoundRecord, boost::forward_traversal_tag>
   friend class boost::iterator_core_access;
   
   void increment();
   
   bool equal(const TextCompoundIterator& other) const;
   
   CompoundRecord& dereference();
   
private:
   std::ifstream _inputFileStream;
   
   CompoundRecord _currentCompoundRecord;

   void init();
   
};