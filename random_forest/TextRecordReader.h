#pragma once

#include "precompile_header.h"

#include "CompoundRecord.h"
#include "IRecordReader.h"
#include "TextRecordIterator.h"

template<typename TRecord>
class RecordReaderFactory;

template<FileFormat::FileFormatEnum formatHint, typename TRecord>
class TextRecordReader: public IRecordReader<TRecord>
{
   friend class RecordReaderFactory<TRecord>;
   
private:
   const boost::filesystem::path _path;
   
protected:
   TextRecordReader():_formatHint(FileFormat::Unknown){};
   
   TextRecordReader(const boost::filesystem::path& path)
      :_path(path)
   {};
   
public:
   ~TextRecordReader(){};
   
   //implementation IRecordReader<TRecord>
   virtual typename IRecordReader<TRecord>::RecordRange get_RecordRange()
   {
      return typename IRecordReader<TRecord>::RecordRange(TextRecordIterator<formatHint, TRecord>(_path, TextRecordIteratorState::Begin), TextRecordIterator<formatHint, TRecord>(_path, TextRecordIteratorState::Finish));
   }
   
};