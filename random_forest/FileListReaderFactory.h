#pragma once

#include "precompile_header.h"

#include "FileListReader.h"

class FileListReaderCreationConfig
{
private:
   boost::filesystem::path _path;

public:
   void set_Path(const boost::filesystem::path& path)
   {
      _path = path;
   }

   const boost::filesystem::path& get_Path() const
   {
      return _path;
   }

};

class FileListReaderFactory
{
public:
   static FileListReaderPtr createFileListReader(const FileListReaderCreationConfig& config)
   {
      return FileListReaderPtr(new FileListReader(config.get_Path()));
   }
};