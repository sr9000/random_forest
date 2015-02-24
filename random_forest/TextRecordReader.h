#pragma once

#include "precompile_header.h"

#include "DeclareReaderFactory.h"
#include "IRecordReader.h"
#include "CompoundRecord.h"
#include "ITextRecordIterator.h"

template<typename TRecord>
class TextRecordReader: public IRecordReader<TRecord>
{
   friend class ReaderFactory;
   
private:
   typedef IRecordReader<TRecord>::RecordRange range;
   
   const boost::filesystem::path _path;

   const FileFormat::FileFormatEnum _formatHint;
   
protected:
   TextRecordReader():_formatHint(FileFormat::Unknown){};
   
   TextRecordReader(const boost::filesystem::path& path, const FileFormat::FileFormatEnum formatHint)
      :_path(path),_formatHint(formatHint)
   {};
   
public:
   ~TextCompoundRecordReader(){};
   
   //implementation IRecordReader<RecordOptional>
   virtual IRecordReaderType:: get_RecordRange();
   
};