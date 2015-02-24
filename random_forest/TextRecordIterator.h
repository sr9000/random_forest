#pragma once

#include "precompile_header.h"

#include "TemplateTextRecordIterator.h"

template<typename TRecord, typename TDevice = boost::iostreams::mapped_file_source>
class TextRecordIterator<FileFormat::EndOfLineSeparator>
   :public ITextRecordIterator<TRecord, TDevice>,
    public boost::iterator_facade<TextRecordIterator<FileFormat::EndOfLineSeparator, TRecord, TDevice>, TRecord const, boost::forward_traversal_tag>
{
   friend class boost::iterator_core_access;

public:
   TextRecordIterator()
      :_state(TextRecordIteratorState::Unknown)
   {};

   TextRecordIterator(const boost::filesystem::path&, TextRecordIteratorState::TextRecordIteratorStateEnum);
   
   TextRecordIterator(const TextRecordIterator&);
   
   ~TextRecordIterator();
   
private:
   virtual void ReadCurrentRecord();
   
   bool equal(TextRecordIterator<FileFormat::EndOfLineSeparator, TRecord, TDevice> const& other) const;
   
};