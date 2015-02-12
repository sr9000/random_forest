#pragma once

#include "precompile_header.h"

#include "ICompoundReader.h"
#include "ICompoundIterator.h"

namespace CompoundReaderFactoryType
{
   enum CompoundReaderFactoryType
   {
      TextFile
   };
}

class CompoundReaderCreationConfig
{
private:
   boost::filesystem::path _path;
   
   CompoundReaderFactoryType::CompoundReaderFactoryType _type;
   
public:
   CompoundReaderCreationConfig(){};
   
   ~CompoundReaderCreationConfig(){};
   
   void set_Path(const boost::filesystem::path& path);
   
   void set_Type(const CompoundReaderFactoryType::CompoundReaderFactoryType& type);
   
   const boost::filesystem::path& get_Path() const;
   
   const CompoundReaderFactoryType::CompoundReaderFactoryType& get_Type() const;
   
};

class CompoundReaderFactory
{
private:
   //typedef boost::shared_ptr<ICompoundReader<ICompoundIterator> > ptr_type;
   
public:
   
/*   typedef ptr_type (*create_compound_reader_function) (CompoundReaderFactoryType::CompoundReaderFactoryType);
   
   void addFabricMethod(CompoundReaderFactoryType::CompoundReaderFactoryType type, create_compound_reader_function f);
   
   void removeFabricMethod(CompoundReaderFactoryType::CompoundReaderFactoryType type);*/
   
   CompoundRecordReaderPtr createCompoundReader(const CompoundReaderCreationConfig& config);
   
private:
   //std::map <CompoundReaderFactoryType::CompoundReaderFactoryType, create_compound_reader_function> _methodDictionary;
   
};