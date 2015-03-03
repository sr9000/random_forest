#pragma once

#include "precompile_header.h"

#include "FileIterator.h"

class FileListReader
{
   typedef boost::filesystem::path path_type;

   typedef boost::any_range <path_type, boost::forward_traversal_tag, const path_type&, std::ptrdiff_t> range;

private:
   const path_type _directory;

public:
   FileListReader(const path_type& directory)
      :_directory(directory)
   {};

   range get_Range()
   {
      return range(FileIterator(_directory, FileIteratorState::Begin), FileIterator(_directory, FileIteratorState::Finish));
   }

};

typedef boost::shared_ptr<FileListReader> FileListReaderPtr;