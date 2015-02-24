#include "precompile_header.h"

#include "CompoundReaderFactory.h"
#include "TextCompoundRecordReader.h"
#include "Macros.h"

using namespace CompoundReaderFactoryType;
using namespace std;

void CompoundReaderCreationConfig::set_Path(const boost::filesystem::path& path)
{
   _path = path;
}

void CompoundReaderCreationConfig::set_Type(const CompoundReaderFactoryTypeEnum& type)
{
   _type = type;
}

const boost::filesystem::path&  CompoundReaderCreationConfig::get_Path() const
{
   return _path;
}

const CompoundReaderFactoryTypeEnum& CompoundReaderCreationConfig::get_Type() const
{
   return _type;
}

CompoundRecordReaderPtr CompoundReaderFactory::createCompoundReader(const CompoundReaderCreationConfig& config)
{
   switch (config.get_Type())
   {
      case TextFile:
         return CompoundRecordReaderPtr(new TextCompoundRecordReader(config.get_Path()));
      default:
         THROWEXCEPTION("No implementation", "No case option");
   }
}