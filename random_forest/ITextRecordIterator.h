#pragma once

#include "precompile_header.h"

#include "RecordParser.h"

namespace TextRecordIteratorState
{
   enum TextRecordIteratorStateEnum
   {
      Begin,
      Proceed,
      Finish,
      Unknown
   };
};

template<typename TRecord, typename TDevice = boost::iostreams::mapped_file_source>
class ITextRecordIterator
{
public:
   typedef boost::shared_ptr<TDevice> file_ptr;

   typedef boost::iostreams::stream<TDevice> file_stream;

   typedef boost::shared_ptr<file_stream> file_stream_ptr;
   
private:
   const boost::filesystem::path _path;
   
   TextRecordIteratorState::TextRecordIteratorStateEnum _state;
   
   file_ptr _filePtr;

   file_stream_ptr _streamPtr;
   
   mutable TRecord _optionalRecord;
   
public:
   void initialize();
   
   virtual void ReadCurrentRecord() = 0;
   
   void ParseCurrentRecord(const string& rawRecord);
   
   void increment();
   
   const TRecord& dereference() const;
   
};
