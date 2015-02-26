#pragma once

#include "precompile_header.h"

#include "TemplateTextRecordIterator.h"

template<typename TRecord, typename TDevice>
class TextRecordIterator<FileFormat::EndOfLineSeparator, TRecord, TDevice>
   :public boost::iterator_facade<TextRecordIterator<FileFormat::EndOfLineSeparator, TRecord, TDevice>, const TRecord, boost::forward_traversal_tag, const TRecord&>,
   public ITextRecordIterator<TRecord, TDevice>
    
{
   friend class boost::iterator_core_access;

public:
   TextRecordIterator()
      :ITextRecordIterator()
   {};

   TextRecordIterator(const boost::filesystem::path& path, const TextRecordIteratorState::TextRecordIteratorStateEnum state)
      :ITextRecordIterator(path, state)
   {
      initialize();
   };
   
   TextRecordIterator(const TextRecordIterator<FileFormat::EndOfLineSeparator, TRecord, TDevice>& other)
      :ITextRecordIterator(other._path, other._state)
   {
      switch (other._state)
      {
      case TextRecordIteratorState::Finish:
         break;
      case TextRecordIteratorState::Begin:
         {
            _filePtr = file_ptr(new TDevice(_path));
            _record = other._record;
            std::streampos pos = other._streamPtr->tellg();
            _streamPtr = file_stream_ptr(new file_stream());
            _streamPtr->open(*_filePtr);
            _streamPtr->seekg(pos);
         }
         break;
      case TextRecordIteratorState::Proceed:
         THROWEXCEPTION("Wrong operation", "Copy constructor of \'TextRecordIterator<FileFormat::EndOfLineSeparator, TRecord, TDevice>\'. You can not copy a \'TextRecordIterator\' in the \'Proceed\' state.");
      case TextRecordIteratorState::Unknown:
         THROWEXCEPTION("Wrong operation", "Copy constructor of \'TextRecordIterator<FileFormat::EndOfLineSeparator, TRecord, TDevice>\'. Source iterator was in \'Unknown\' state.");
      default:
         THROWEXCEPTION("No implementation", "No case option");
      }
   }
   
   ~TextRecordIterator()
   {
      if (_streamPtr && _streamPtr->is_open())
      {
         _streamPtr->close();
      }
      if (_filePtr && _filePtr->is_open())
      {
         _filePtr->close();
      }
   }
   
private:
   virtual void ReadCurrentRecord()
   {
      std::string tmp;
      std::getline(*_streamPtr, tmp);
      boost::algorithm::trim_if(tmp, boost::is_any_of("\r"));
      boost::algorithm::trim(tmp);
      if (tmp.empty())
      {
         if (_streamPtr->eof())
         {
            _streamPtr->close();
            _state = TextRecordIteratorState::Finish;
         }
         else
         {
            _record.reset();
         }
      }
      else
      {
         FormatHintRawRecordParser<FileFormat::EndOfLineSeparator, TRecord>::parse(_record, tmp);
      }
   }
   
   bool equal(TextRecordIterator<FileFormat::EndOfLineSeparator, TRecord, TDevice> const& other) const
   {
      if (_state == TextRecordIteratorState::Unknown)
      {
         THROWEXCEPTION("Wrong operation", "Method \'bool TextRecordIterator<FileFormat::EndOfLineSeparator, TRecord, TDevice>::equal(const TextRecordIterator<FileFormat::EndOfLineSeparator, TRecord, TDevice>& other) const\'. You can not compare iterator in \'Unknown\' state with other iterators.");
      }
      switch (other._state)
      {
      case TextRecordIteratorState::Begin:
      case TextRecordIteratorState::Finish:
         return (_state == other._state && _path == other._path);
      case TextRecordIteratorState::Proceed:
         return false;
      case TextRecordIteratorState::Unknown:
         THROWEXCEPTION("Wrong operation", "Method \'bool TextRecordIterator<FileFormat::EndOfLineSeparator, TRecord, TDevice>::equal(const TextRecordIterator<FileFormat::EndOfLineSeparator, TRecord, TDevice>& other) const\'. You can not compare iterator with other iterator in \'Unknown\'.");
      default:
         THROWEXCEPTION("No implementation", "No case option");
      }
   }
   
};