#pragma once

#include "precompile_header.h"

#include "ICompoundReader.h"
#include "ICompoundIterator.h"
#include "CompoundRecord.h"
#include "CompoundReaderFactory.h"

class TextCompoundReader: public ICompoundReader<CompoundRecord>
{
   friend class CompoundReaderFactory;
   
private:
   boost::filesystem::path _path;
   
protected:
   TextCompoundReader(){};
   
   TextCompoundReader(const boost::filesystem::path& path):_path(path){};
   
   typedef ICompoundReader<CompoundRecord> interface_type;
   
public:
   ~TextCompoundReader(){};
   
   //implementation ICompoundReader
   //virtual ICompoundReader::iterator_type ICompoundReader::begin();
   //virtual ICompoundReader::iterator_type ICompoundReader::end();
   
   virtual CompoundRecordRange get_CompoundRange();
   
   //boost::shared_ptr<TextCompoundReader::interface_type> textCompoundReaderFabricMethod (CompoundReaderFactoryType::CompoundReaderFactoryType type);
   
};

//boost::shared_ptr<TextCompoundReader::interface_type> textCompoundReaderFabricMethod (CompoundReaderFactoryType::CompoundReaderFactoryType type); 