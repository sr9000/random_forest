#pragma once

#include "precompile_header.h"

#include "ITextRecordIterator.h"

template<FileFormat::FileFormatEnum formatHint, typename TRecord, typename TDevice = boost::iostreams::mapped_file_source>
class TextRecordIterator
   :public boost::iterator_facade<TextRecordIterator<formatHint, TRecord, TDevice>, const TRecord, boost::forward_traversal_tag, const TRecord&>,
   public ITextRecordIterator<TRecord, TDevice>
{
private:
   TextRecordIterator(){};
};