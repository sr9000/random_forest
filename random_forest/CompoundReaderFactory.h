#pragma once

#include "precompile_header.h"
#include "TextCompoundReader.h"

namespace CompoundReaderFactoryType
{
   enum CompoundReaderFactoryTypeEnum
   {
      TextFile
   };
}

class CompoundReaderCreationConfig
{
private:
   boost::filesystem::path _path;
   
   CompoundReaderFactoryType::CompoundReaderFactoryTypeEnum _type;
   
public:
   void set_Path(const boost::filesystem::path& path);
   
   void set_Type(const CompoundReaderFactoryType::CompoundReaderFactoryTypeEnum& type);
   
   const boost::filesystem::path& get_Path() const;
   
   const CompoundReaderFactoryType::CompoundReaderFactoryTypeEnum& get_Type() const;
   
};

class CompoundReaderFactory
{
public:
   static CompoundRecordReaderPtr createCompoundReader(const CompoundReaderCreationConfig& config);
   
};