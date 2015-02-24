#pragma once

#include "precompile_header.h"

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

   FileFormat::FileFormatEnum _formatFile;
   
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
   static typename IRecordReader<TRecord>::RecordReaderPtr createRecordReader(const RecordReaderCreationConfig& config)
   {
      switch (config.get_Type())
      {
      case RecordReaderFactoryType::TextFile:
         switch (config.get_FileFormat())
         {
         case FileFormat::EndOfLineSeparator:
            return typename IRecordReader<TRecord>::RecordReaderPtr(new TextRecordReader<FileFormat::EndOfLineSeparator, TRecord>(config.get_Path()));
         case FileFormat::Unknown:
            THROWEXCEPTION("Wrong argument", "RecordReaderCreationConfig has \'FileFormat::Unknown\', but \'RecordReaderFactoryType::TextFile\'");
         default:
            THROWEXCEPTION("No implementation", "No case option");
         }
      default:
         THROWEXCEPTION("No implementation", "No case option");
      }
   }
   
};