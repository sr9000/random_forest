#pragma once

#include "precompile_header.h"

#include "ITextRecordIterator.h"

template<FileFormat::FileFormatEnum formatHint, typename TRecord, typename TDevice = boost::iostreams::mapped_file_source>
class TextRecordIterator
{
private:
   TextRecordIterator(){};
};