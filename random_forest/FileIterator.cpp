#include "precompile_header.h"

#include "FileIterator.h"
#include "Macros.h"

using namespace std;
using namespace FileIteratorState;
namespace bfs = boost::filesystem;

FileIterator::FileIterator(const bfs::path& directory, const FileIteratorStateEnum state)
   :_directory(directory),_state(state), _index(0)
{
   if (!bfs::is_directory(_directory))
      THROWEXCEPTION("Error", "Constructor \'FileIterator(const path_type& directory, const FileIteratorState::FileIteratorStateEnum state)\', path \'" + _directory.generic_string() + "\' is not directory!");
   if (!bfs::exists(_directory))
      THROWEXCEPTION("Error", "Constructor \'FileIterator(const path_type& directory, const FileIteratorState::FileIteratorStateEnum state)\', directory \'" + _directory.generic_string() + "\' not found!");
   _ptrToFileList = ptr_to_file_list(new file_list());
   bfs::directory_iterator endItr;
   for (bfs::directory_iterator itr(_directory); itr != endItr; ++itr)
   {
      if (bfs::is_regular_file(*itr))
         _ptrToFileList->push_back(*itr);
   }

   if (_ptrToFileList->empty())
      _state = Finish;
};

void FileIterator::increment()
{
   switch (_state)
   {
   case Finish:
      break;
   case Begin:
      _state = Proceed;
   case Proceed:
      ++_index;
      if (_index >= _ptrToFileList->size())
         _state = Finish;
      break;
   case Unknown:
      THROWEXCEPTION("Wrong operation", "Copy constructor of \'TextRecordIterator<FileFormat::EndOfLineSeparator, TRecord, TDevice>\'. Source iterator was in \'Unknown\' state.");
   default:
      THROWEXCEPTION("No implementation", "No case option");
   }
}

bool compareFileLists(const vector<bfs::path>& first, const vector<bfs::path>& second)
{
   if (first.size() != second.size())
      return false;
   for (int i = 0; i < first.size(); ++i)
   {
      if (first[i] != second[i])
         return false;
   }
   return true;
}

bool FileIterator::equal(const FileIterator& other) const
{
   switch (_state)
   {
      case Finish:
         return other._state == Finish;
      case Begin:
      case Proceed:
         if (other._state == Unknown)
            THROWEXCEPTION("Wrong operation", "Method \'bool equal(const FileIterator& other) const\'. You can not compare iterator with other iterator in \'Unknown\' state.");
         if (_state != other._state)
            return false;
         return compareFileLists(*_ptrToFileList, *other._ptrToFileList) && _index == other._index;
      case Unknown:
         THROWEXCEPTION("Wrong operation", "Method \'bool equal(const FileIterator& other) const\'. You can not compare iterator in \'Unknown\' state with other iterators.");
      default:
         THROWEXCEPTION("No implementation", "No case option");
   }
}