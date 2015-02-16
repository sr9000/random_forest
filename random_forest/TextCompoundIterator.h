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

class TextCompoundIterator: public boost::iterator_facade <TextCompoundIterator, CompoundRecord, boost::forward_traversal_tag, CompoundRecord&>
{
   friend class TextCompoundReader;
   
public:
   TextCompoundIterator();

   TextCompoundIterator(const TextCompoundIterator&);

protected:
   boost::filesystem::path _path;

   TextCompoundIteratorState::TextCompoundIteratorState _state;
   
   //implementation boost::iterator_facade <TextCompoundIterator, CompoundRecord, boost::forward_traversal_tag>
   friend class boost::iterator_core_access;
   
   void increment();
   
   bool equal(const TextCompoundIterator& other) const;
   
   CompoundRecord& dereference() const;
   
private:
   std::ifstream _inputFileStream;
   
   mutable CompoundRecord _currentCompoundRecord;

   void init();
   
};