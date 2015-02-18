#include "precompile_header.h"

#include "TextCompoundIterator.h"
#include "Macros.h"

using namespace TextCompoundIteratorState;
using namespace std;

void FillCompoundRecordOptional(CompoundRecordOptional&, const string&);

TextCompoundIterator::TextCompoundIterator(const boost::filesystem::path& path, TextCompoundIteratorStateEnum state):_path(path),_state(state)
{
   initialize();
}

TextCompoundIterator::TextCompoundIterator(const TextCompoundIterator& other):_path(other._path),_state(other._state)
{
   switch (other._state)
   {
   case Finish:
      break;
   case Begin:
      {
         _filePtr = TextCompoundIterator::mapped_file_ptr(new boost::iostreams::mapped_file_source(_path));//other._filePtr;
         _optionalCompoundRecord = other._optionalCompoundRecord;
         streampos pos = other._streamPtr->tellg();
         _streamPtr = mapped_file_stream_ptr(new mapped_file_stream());
         _streamPtr->open(*_filePtr);
         _streamPtr->seekg(pos);
      }
      break;
   case Proceed:
      THROWEXCEPTION("Wrong operation", "Copy constructor of \'TextCompoundIterator\'. You can not copy a \'TextCompoundIterator\' in the reading process.");
   case Unknown:
      THROWEXCEPTION("Wrong operation", "Copy constructor of \'TextCompoundIterator\'. Source iterator was not initialized.");
   default:
      THROWEXCEPTION("No implementation", "No case option");
   }
}

TextCompoundIterator::~TextCompoundIterator()
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

void TextCompoundIterator::increment()
{
   switch (_state)
   {
   case Begin:
      _state = Proceed;
   case Proceed:
      ReadCurrentCompoundRecord();
      break;
   case Finish:
      THROWEXCEPTION("Wrong operation", "Method \'void TextCompoundIterator::increment()\'. You can not increment end iterator.");
   case Unknown:
      THROWEXCEPTION("Wrong operation", "Method \'void TextCompoundIterator::increment()\'. You can not increment uninitialized iterator.");
   default:
      THROWEXCEPTION("No implementation", "No case option");
   }
}

bool TextCompoundIterator::equal(const TextCompoundIterator& other) const
{
   if (_state == Unknown)
   {
      THROWEXCEPTION("Wrong operation", "Method \'bool TextCompoundIterator::equalconst TextCompoundIterator& other) const\'. You can not compare uninitialized iterator with other iterators.");
   }
   switch (other._state)
   {
   case Begin:
   case Finish:
      return (_state == other._state && _path == other._path);
   case Proceed:
      return false;
   case Unknown:
      THROWEXCEPTION("Wrong operation", "Method \'bool TextCompoundIterator::equalconst TextCompoundIterator& other) const\'. You can not compare iterator with other uninitialized iterator.");
   default:
      THROWEXCEPTION("No implementation", "No case option");
   }
}

CompoundRecordOptional& TextCompoundIterator::dereference() const
{
   return _optionalCompoundRecord;
}

void TextCompoundIterator::initialize()
{
   switch (_state)
   {
   case Finish:
   case Proceed:
      break;
   case Begin:
      if (!_filePtr)
      {
         if (boost::filesystem::exists(_path))
         {
            _filePtr = TextCompoundIterator::mapped_file_ptr(new boost::iostreams::mapped_file_source(_path));
         }
         else
         {
            THROWEXCEPTION("Error", "Method \'void TextCompoundIterator::validate()\', file \'" + _path.generic_string() + "\' not found!");
         }
      }
      _streamPtr = mapped_file_stream_ptr(new mapped_file_stream());
      if (!_streamPtr->is_open())
      {
         _streamPtr->open(*_filePtr);
      }
      ReadCurrentCompoundRecord();
      break;
   case Unknown:
      THROWEXCEPTION("Wrong operation", "Method \'void TextCompoundIterator::validate()\'. You can not validate uninitialized iterator.");
   default:
      THROWEXCEPTION("No implementation", "No case option");
   }
}

void TextCompoundIterator::ReadCurrentCompoundRecord()
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
   
   rec._compoundId = partsOfStringCompoundRecord[0];
   partsOfStringCompoundRecord.erase(partsOfStringCompoundRecord.begin());
   
   rec._features.clear();
   bool fail = false;
   BOOST_FOREACH(const string& value, partsOfStringCompoundRecord)
   {
      try
      {
         rec._features.push_back(boost::lexical_cast<uint32_t>(value));
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