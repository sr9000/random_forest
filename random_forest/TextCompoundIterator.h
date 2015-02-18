#pragma once

#include "precompile_header.h"

#include "CompoundRecord.h"

namespace TextCompoundIteratorState
{
   enum TextCompoundIteratorStateEnum
   {
      Begin,
      Proceed,
      Finish,
      Unknown
   };
};

class TextCompoundIterator: public boost::iterator_facade <TextCompoundIterator, CompoundRecordOptional, boost::forward_traversal_tag, CompoundRecordOptional&>
{
   friend class boost::iterator_core_access;
   
public:
   typedef boost::shared_ptr<boost::iostreams::mapped_file_source> mapped_file_ptr;

   typedef boost::iostreams::stream<boost::iostreams::mapped_file_source> mapped_file_stream;

   typedef boost::shared_ptr<mapped_file_stream > mapped_file_stream_ptr;

private:
   const boost::filesystem::path _path;
   
   TextCompoundIteratorState::TextCompoundIteratorStateEnum _state;
   
   mapped_file_ptr _filePtr;

   mapped_file_stream_ptr _streamPtr;
   
   mutable CompoundRecordOptional _optionalCompoundRecord;
   
public:
   TextCompoundIterator():_state(TextCompoundIteratorState::Unknown){};

   TextCompoundIterator(const boost::filesystem::path&, TextCompoundIteratorState::TextCompoundIteratorStateEnum);
   
   TextCompoundIterator(const TextCompoundIterator&);
   
   ~TextCompoundIterator();
   
   //implementation boost::iterator_facade <TextCompoundIterator, CompoundRecord, boost::forward_traversal_tag, CompoundRecord&>
   void increment();
   
   //implementation boost::iterator_facade <TextCompoundIterator, CompoundRecord, boost::forward_traversal_tag, CompoundRecord&>
   bool equal(const TextCompoundIterator& other) const;
   
   //implementation boost::iterator_facade <TextCompoundIterator, CompoundRecord, boost::forward_traversal_tag, CompoundRecord&>
   CompoundRecordOptional& dereference() const;
   
private:
   void validate();
   
   void ReadCurrentCompoundRecord();
   
};