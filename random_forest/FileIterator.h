#pragma once

#include "precompile_header.h"

#include "Macros.h"

namespace FileIteratorState
{
   enum FileIteratorStateEnum
   {
      Begin,
      Proceed,
      Finish,
      Unknown
   };
};

class FileIterator
   :public boost::iterator_facade<FileIterator, const boost::filesystem::path, boost::forward_traversal_tag, const boost::filesystem::path&>
{
   friend class boost::iterator_core_access;

   typedef boost::filesystem::path path_type;

   typedef std::vector<path_type> file_list;

   typedef boost::shared_ptr<file_list > ptr_to_file_list;
   
protected:
   const path_type _directory;

   ptr_to_file_list _ptrToFileList;
   
   FileIteratorState::FileIteratorStateEnum _state;

   int _index;
   
public:
   FileIterator()
      :_state(FileIteratorState::Unknown), _index(0)
   {};
   
   FileIterator(const path_type& directory, const FileIteratorState::FileIteratorStateEnum state);

   FileIterator(const FileIterator& other)
      :_directory(other._directory),_state(other._state), _index(other._index), _ptrToFileList(other._ptrToFileList)
   {};
   
   void increment();
   
   bool equal(const FileIterator& other) const;
   
   const path_type& dereference() const
   {
      return (*_ptrToFileList)[_index];
   }
   
};