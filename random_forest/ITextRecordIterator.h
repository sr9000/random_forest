#pragma once

#include "precompile_header.h"

#include "RecordParser.h"
#include "Macros.h"

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
   
protected:
   const boost::filesystem::path _path;
   
   TextRecordIteratorState::TextRecordIteratorStateEnum _state;
   
   file_ptr _filePtr;

   file_stream_ptr _streamPtr;
   
   mutable TRecord _record;
   
public:
   ITextRecordIterator()
      :_state(TextRecordIteratorState::Unknown)
   {};

   ITextRecordIterator(const boost::filesystem::path& path, const TextRecordIteratorState::TextRecordIteratorStateEnum state)
      :_path(path),_state(state)
   {};

   virtual void ReadCurrentRecord() = 0;
   
   void initialize()
   {
      using namespace TextRecordIteratorState;

      switch (_state)
      {
      case Finish:
      case Proceed:
         break;
      case Begin:
         if (!_filePtr)
         {
            if (!boost::filesystem::exists(_path))
               THROWEXCEPTION("Error", "Method \'void ITextRecordIterator<TRecord, TDevice>::initialize()\', file \'" + _path.generic_string() + "\' not found!");

            _filePtr = ITextRecordIterator<TRecord, TDevice>::file_ptr(new TDevice(_path));
         }
         _streamPtr = file_stream_ptr(new file_stream());
         if (!_streamPtr->is_open())
         {
            _streamPtr->open(*_filePtr);
         }
         ReadCurrentRecord();
         break;
      case Unknown:
         THROWEXCEPTION("Wrong operation", "Method \'void ITextRecordIterator<TRecord, TDevice>::initialize()\'. You can not initialize iterator in \'Unknown\' state.");
      default:
         THROWEXCEPTION("No implementation", "No case option");
      }
   }
   
   void increment()
   {
      using namespace TextRecordIteratorState;

      switch (_state)
      {
      case Begin:
         _state = Proceed;
      case Proceed:
         ReadCurrentRecord();
         break;
      case Finish:
         THROWEXCEPTION("Wrong operation", "Method \'void ITextRecordIterator<TRecord, TDevice>::increment()\'. You can not increment end iterator.");
      case Unknown:
         THROWEXCEPTION("Wrong operation", "Method \'void ITextRecordIterator<TRecord, TDevice>::increment()\'. You can not increment iterator in \'Unknown\' state.");
      default:
         THROWEXCEPTION("No implementation", "No case option");
      }
   }
   
   const TRecord& dereference() const
   {
     return _record;
   }
   
};
