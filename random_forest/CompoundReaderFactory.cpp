#include "precompile_header.h"

#include "CompoundReaderFactory.h"
#include "TextCompoundReader.h"

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