#include "precompile_header.h"

#include "TextCompoundIterator.h"

TextCompoundIterator::TextCompoundIterator()
{
	_state = TextCompoundIteratorState::Unknown;
}

TextCompoundIterator::TextCompoundIterator(const TextCompoundIterator& other)
{
	switch (other._state)
	{
	case TextCompoundIteratorState::Begin:
	case TextCompoundIteratorState::Finish:
		_path = other._path;
		break;
	case TextCompoundIteratorState::Proceed:
		throw std::exception();
		break;
	case TextCompoundIteratorState::Unknown:
		throw std::exception();
		break;
	default:
		throw std::exception();
		break;
	}
}

void fillCompoundRecord(CompoundRecord& rec, const std::string& str)
{
	std::vector<std::string> partsOfStringCompoundRecord;
   boost::split(partsOfStringCompoundRecord, str, boost::is_any_of(" "));
   partsOfStringCompoundRecord.pop_back();

   rec._compoundId = partsOfStringCompoundRecord[0];
   partsOfStringCompoundRecord.erase(partsOfStringCompoundRecord.begin());

   rec._features.clear();
   BOOST_FOREACH(const std::string& value, partsOfStringCompoundRecord)
   {
      uint32_t n;
      n = boost::lexical_cast<uint32_t>(value);
      rec._features.push_back(n);
   }
}

void TextCompoundIterator::init()
{
   std::string tmp;
	switch (_state)
	{
	case TextCompoundIteratorState::Begin:
		if (!_inputFileStream.is_open())
		{
			_inputFileStream.open(_path.c_str(), std::ios_base::in);
         std::getline(_inputFileStream, tmp);
         if (tmp == "")
         {
            _inputFileStream.close();
            _state = TextCompoundIteratorState::Finish;
         }
         else
         {
            fillCompoundRecord(_currentCompoundRecord, tmp);
         }
		}
		break;
	case TextCompoundIteratorState::Finish:
	case TextCompoundIteratorState::Proceed:
		break;
	case TextCompoundIteratorState::Unknown:
		throw std::exception();
		break;
	default:
		throw std::exception();
		break;
	}
}

bool TextCompoundIterator::equal(const TextCompoundIterator& other) const
{
	switch (other._state)
	{
	case TextCompoundIteratorState::Begin:
	case TextCompoundIteratorState::Finish:
		return _state == other._state;
		break;
	case TextCompoundIteratorState::Proceed:
		return false;
		break;
	case TextCompoundIteratorState::Unknown:
		throw std::exception();
		break;
	default:
		throw std::exception();
		break;
	}
}

CompoundRecord& TextCompoundIterator::dereference() const
{
	return _currentCompoundRecord;
}

void TextCompoundIterator::increment()
{
   std::string tmp;
   switch (_state)
	{
   case TextCompoundIteratorState::Begin:
      _state = TextCompoundIteratorState::Proceed;
   case TextCompoundIteratorState::Proceed:
      std::getline(_inputFileStream, tmp);
      if (tmp == "")
      {
         _inputFileStream.close();
         _state = TextCompoundIteratorState::Finish;
      }
      else
      {
         fillCompoundRecord(_currentCompoundRecord, tmp);
      }
      break;
   case TextCompoundIteratorState::Finish:
      throw std::exception();
		break;
   case TextCompoundIteratorState::Unknown:
      throw std::exception();
		break;
   default:
      throw std::exception();
		break;
   }
}