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

class TextCompoundIterator: public boost::iterator_facade <TextCompoundIterator, CompoundRecord, boost::forward_traversal_tag, CompoundRecord&>
{
   friend class boost::iterator_core_access;
   
public:
   typedef boost::shared_ptr<boost::iostreams::mapped_file_source> mapped_file_ptr;

   typedef boost::iostreams::stream<boost::iostreams::mapped_file_source> mapped_file_stream;

   typedef boost::shared_ptr<mapped_file_stream > mapped_file_stream_ptr;

private:
   boost::filesystem::path _path;
   
   TextCompoundIteratorState::TextCompoundIteratorStateEnum _state;
   
   mapped_file_ptr _filePtr;

   mapped_file_stream_ptr _streamPtr;
   
   mutable CompoundRecord _currentCompoundRecord;
   
public:
   TextCompoundIterator();
   
   TextCompoundIterator(const TextCompoundIterator&);
   
   TextCompoundIterator(const boost::filesystem::path&, TextCompoundIteratorState::TextCompoundIteratorStateEnum);
   
   ~TextCompoundIterator();
   
   //implementation boost::iterator_facade <TextCompoundIterator, CompoundRecord, boost::forward_traversal_tag, CompoundRecord&>
   void increment();
   
   //implementation boost::iterator_facade <TextCompoundIterator, CompoundRecord, boost::forward_traversal_tag, CompoundRecord&>
   bool equal(const TextCompoundIterator& other) const;
   
   //implementation boost::iterator_facade <TextCompoundIterator, CompoundRecord, boost::forward_traversal_tag, CompoundRecord&>
   CompoundRecord& dereference() const;
   
private:
   void validate();
   
   void read_CurrentCompoundRecord();
   
   void set_Path(const boost::filesystem::path&);
   
   void set_State(TextCompoundIteratorState::TextCompoundIteratorStateEnum);
   
   const boost::filesystem::path& get_Path() const;
   
   const TextCompoundIteratorState::TextCompoundIteratorStateEnum get_State() const;
   
};