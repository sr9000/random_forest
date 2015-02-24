#include "precompile_header.h"

#include "TextRecordIterator.h"
#include "Macros.h"

using namespace TextRecordIteratorState;
using namespace std;

template<TRecord, TDevice>
TextRecordIterator<TRecord, TDevice>::TextRecordIterator(const boost::filesystem::path& path, TextRecordIteratorStateEnum state, TextRecordIterator<TRecord, TDevice>::func_ptr pred)
   :_path(path),_state(state),_fillRecord(
{
   initialize();
}

TextRecordIterator<>::TextRecordIterator(const TextRecordIterator& other)
   :_path(other._path),_state(other._state)
{
   switch (other._state)
   {
   case Finish:
      break;
   case Begin:
      {
         _filePtr = TextRecordIterator::mapped_file_ptr(new boost::iostreams::mapped_file_source(_path));//other._filePtr;
         _optionalCompoundRecord = other._optionalCompoundRecord;
         streampos pos = other._streamPtr->tellg();
         _streamPtr = mapped_file_stream_ptr(new mapped_file_stream());
         _streamPtr->open(*_filePtr);
         _streamPtr->seekg(pos);
      }
      break;
   case Proceed:
      THROWEXCEPTION("Wrong operation", "Copy constructor of \'TextRecordIterator\'. You can not copy a \'TextRecordIterator\' in the reading process.");
   case Unknown:
      THROWEXCEPTION("Wrong operation", "Copy constructor of \'TextRecordIterator\'. Source iterator was not initialized.");
   default:
      THROWEXCEPTION("No implementation", "No case option");
   }
}

TextRecordIterator<>::~TextRecordIterator()
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

template<>
void TextRecordIterator<>::increment()
{
   switch (_state)
   {
   case Begin:
      _state = Proceed;
   case Proceed:
      ReadCurrentCompoundRecord();
      break;
   case Finish:
      THROWEXCEPTION("Wrong operation", "Method \'void TextRecordIterator::increment()\'. You can not increment end iterator.");
   case Unknown:
      THROWEXCEPTION("Wrong operation", "Method \'void TextRecordIterator::increment()\'. You can not increment uninitialized iterator.");
   default:
      THROWEXCEPTION("No implementation", "No case option");
   }
}

template<>
bool TextRecordIterator<>::equal(const TextRecordIterator& other) const
{
   if (_state == Unknown)
   {
      THROWEXCEPTION("Wrong operation", "Method \'bool TextRecordIterator::equalconst TextRecordIterator& other) const\'. You can not compare uninitialized iterator with other iterators.");
   }
   switch (other._state)
   {
   case Begin:
   case Finish:
      return (_state == other._state && _path == other._path);
   case Proceed:
      return false;
   case Unknown:
      THROWEXCEPTION("Wrong operation", "Method \'bool TextRecordIterator::equalconst TextRecordIterator& other) const\'. You can not compare iterator with other uninitialized iterator.");
   default:
      THROWEXCEPTION("No implementation", "No case option");
   }
}

template<>
CompoundRecordOptional& TextRecordIterator<>::dereference() const
{
   return _optionalCompoundRecord;
}

template<>
void TextRecordIterator<>::initialize()
{
   switch (_state)
   {
   case Finish:
   case Proceed:
      break;
   case Begin:
      if (!_filePtr)
      {
         if (!boost::filesystem::exists(_path))
            THROWEXCEPTION("Error", "Method \'void TextRecordIterator::validate()\', file \'" + _path.generic_string() + "\' not found!");

         _filePtr = TextRecordIterator::mapped_file_ptr(new boost::iostreams::mapped_file_source(_path));
      }
      _streamPtr = mapped_file_stream_ptr(new mapped_file_stream());
      if (!_streamPtr->is_open())
      {
         _streamPtr->open(*_filePtr);
      }
      ReadCurrentCompoundRecord();
      break;
   case Unknown:
      THROWEXCEPTION("Wrong operation", "Method \'void TextRecordIterator::validate()\'. You can not validate uninitialized iterator.");
   default:
      THROWEXCEPTION("No implementation", "No case option");
   }
}

template<>
void TextRecordIterator<>::ReadCurrentCompoundRecord()
{
   string tmp;
   getline(*_streamPtr, tmp);
   boost::algorithm::trim_if(tmp, boost::is_any_of("\r"));
   boost::algorithm::trim(tmp);
   if (tmp.empty())
   {
      if (_streamPtr->eof())
      {
         _streamPtr->close();
         _state = Finish;
      }
      else
      {
         _optionalCompoundRecord.reset();
      }
   }
   else
   {
      FillCompoundRecordOptional(_optionalCompoundRecord, tmp);
   }
}

void FillCompoundRecordOptional(CompoundRecordOptional& opRec, const string& str)
{
   CompoundRecord rec;

   opRec.reset();

   vector<string> partsOfStringCompoundRecord;
   boost::split(partsOfStringCompoundRecord, str, boost::is_any_of(","));
   if (partsOfStringCompoundRecord.size() < 2)
      return;

   try
   {
      rec._compoundId = partsOfStringCompoundRecord[0];
   }
   catch(const CompoundIdException&)
   {
      return;
   }
   
   
   rec._features.resize(partsOfStringCompoundRecord.size() - 1);
   bool fail = false;
   for (vector<string>::iterator itr = partsOfStringCompoundRecord.begin() + 1; itr != partsOfStringCompoundRecord.end(); ++itr)
   {
      try
      {
         rec._features.push_back(boost::lexical_cast<uint32_t>(*itr));
      }
      catch(const boost::bad_lexical_cast &)
      {
         fail = true;
         break;
      }
   }
   if (!fail)
   {
      opRec = rec;
   }
}