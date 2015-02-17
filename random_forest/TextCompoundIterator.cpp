#include "precompile_header.h"

#include "TextCompoundIterator.h"

using namespace TextCompoundIteratorState;
using namespace std;

void fillCompoundRecord(CompoundRecord& rec, const string& str)
{
   vector<string> partsOfStringCompoundRecord;
   boost::split(partsOfStringCompoundRecord, str, boost::is_any_of(","));
   
   rec._compoundId = partsOfStringCompoundRecord[0];
   partsOfStringCompoundRecord.erase(partsOfStringCompoundRecord.begin());
   
   rec._features.clear();
   BOOST_FOREACH(const string& value, partsOfStringCompoundRecord)
   {
      rec._features.push_back(boost::lexical_cast<uint32_t>(value));
   }
}

TextCompoundIterator::TextCompoundIterator()
{
   set_State(Unknown);
}

TextCompoundIterator::TextCompoundIterator(const TextCompoundIterator& other)
{
   switch (other.get_State())
   {
   case Finish:
      set_Path(other.get_Path());
      set_State(Finish);
      break;
   case Begin:
      {
      set_Path(other.get_Path());
      set_State(Begin);
      _filePtr = TextCompoundIterator::mapped_file_ptr(new boost::iostreams::mapped_file_source(get_Path()));//other._filePtr;
      _currentCompoundRecord = other._currentCompoundRecord;
      streampos pos = other._streamPtr->tellg();
      _streamPtr = mapped_file_stream_ptr(new mapped_file_stream());
      _streamPtr->open(*_filePtr);
      _streamPtr->seekg(pos);
      
      }
      //validate();
      break;
   case Proceed:
      throw exception();
   case Unknown:
      throw exception();
   default:
      throw exception();
   }
}

TextCompoundIterator::TextCompoundIterator(const boost::filesystem::path& path, TextCompoundIteratorStateEnum state)
{
   set_Path(path);
   set_State(state);
   validate();
}

TextCompoundIterator::~TextCompoundIterator()
{
   if (_streamPtr && _streamPtr->is_open() && _filePtr.unique())
   {
      _streamPtr->close();
   }
}

void TextCompoundIterator::increment()
{
   string tmp;
   switch (get_State())
   {
   case Begin:
      set_State(Proceed);
   case Proceed:
      read_CurrentCompoundRecord();
      break;
   case Finish:
      throw exception();
   case Unknown:
      throw exception();
   default:
      throw exception();
   }
}

bool TextCompoundIterator::equal(const TextCompoundIterator& other) const
{
   switch (other.get_State())
   {
   case Begin:
   case Finish:
      return (_state == other._state && _path == other._path);
   case Proceed:
      return false;
   case Unknown:
      throw exception();
   default:
      throw exception();
   }
}

CompoundRecord& TextCompoundIterator::dereference() const
{
   return _currentCompoundRecord;
}

void TextCompoundIterator::validate()
{
   switch (get_State())
   {
   case Finish:
   case Proceed:
      break;
   case Begin:
      if (!_filePtr)
      {
         _filePtr = TextCompoundIterator::mapped_file_ptr(new boost::iostreams::mapped_file_source(get_Path()));
      }
      _streamPtr = mapped_file_stream_ptr(new mapped_file_stream());
      if (!_streamPtr->is_open())
      {
         _streamPtr->open(*_filePtr);
      }
      read_CurrentCompoundRecord();
      break;
   case Unknown:
      throw exception();
   default:
      throw exception();
   }
}

void TextCompoundIterator::read_CurrentCompoundRecord()
{
   string tmp;
   getline(*_streamPtr, tmp);
   boost::algorithm::trim_if(tmp, boost::is_any_of("\r"));
   if (tmp.empty())
   {
      _streamPtr->close();
      set_State(Finish);
   }
   else
   {
      fillCompoundRecord(_currentCompoundRecord, tmp);
   }
}

void TextCompoundIterator::set_Path(const boost::filesystem::path& path)
{
   _path = path;
}

void TextCompoundIterator::set_State(TextCompoundIteratorStateEnum state)
{
   _state = state;
}

const boost::filesystem::path& TextCompoundIterator::get_Path() const
{
   return _path;
}

const TextCompoundIteratorStateEnum TextCompoundIterator::get_State() const
{
   return _state;
}