#pragma once

#include "precompile_header.h"

#include "DeclareReaderFactory.h"
#include "TextRecordReader.h"

namespace RecordReaderFactoryType
{
   enum RecordReaderFactoryTypeEnum
   {
      TextFile
   };
}

class RecordReaderCreationConfig
{
private:
   boost::filesystem::path _path;
   
   RecordReaderFactoryType::RecordReaderFactoryTypeEnum _type;

   FileFormat::FileFormatEnum _formatHint;
   
public:
   RecordReaderCreationConfig(){}
   
   void set_Path(const boost::filesystem::path& path);
   
   void set_Type(const RecordReaderFactoryType::RecordReaderFactoryTypeEnum& type);
   
   const boost::filesystem::path& get_Path() const;
   
   const RecordReaderFactoryType::RecordReaderFactoryTypeEnum& get_Type() const;
   
   void set_FileFormat(const FileFormat::FileFormatEnum& fileFormat);
   
   const FileFormat::FileFormatEnum& get_FileFormat() const;
};

template<typename TRecord>
class RecordReaderFactory
{
public:
   static IRecordReader<TRecord> createRecordReader(const RecordReaderCreationConfig& config);
   
};