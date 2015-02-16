#include "precompile_header.h"

#include "CompoundReaderFactory.h"
#include "TextCompoundReader.h"

void CompoundReaderCreationConfig::set_Path(const boost::filesystem::path& path)
{
   _path = path;
}

void CompoundReaderCreationConfig::set_Type(const CompoundReaderFactoryType::CompoundReaderFactoryType& type)
{
   _type = type;
}

const boost::filesystem::path&  CompoundReaderCreationConfig::get_Path() const
{
   return _path;
}

const CompoundReaderFactoryType::CompoundReaderFactoryType& CompoundReaderCreationConfig::get_Type() const
{
   return _type;
}

CompoundRecordReaderPtr CompoundReaderFactory::createCompoundReader(const CompoundReaderCreationConfig& config)
{
   switch (config.get_Type())
   {
      case CompoundReaderFactoryType::TextFile:
         return CompoundRecordReaderPtr(new TextCompoundReader(config.get_Path()));
      default:
         throw std::exception();
   }
}