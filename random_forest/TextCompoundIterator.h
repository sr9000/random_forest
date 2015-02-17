#pragma once

#include "precompile_header.h"

#include "CompoundRecord.h"
#include "DirectedIstream.h"

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
   
private:
   boost::filesystem::path _path;
   
   TextCompoundIteratorState::TextCompoundIteratorStateEnum _state;
   
   boost::iostreams::mapped_file _file;

   DirectedIstreamPtr _istreamPtr;
   
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