#pragma once

#include "precompile_header.h"

#include "ICompoundReader.h"
#include "CompoundRecord.h"
#include "CompoundReaderFactory.h"

class TextCompoundReader: public ICompoundReader<CompoundRecordOptional>
{
   friend class CompoundReaderFactory;
   
protected:
   typedef ICompoundReader<CompoundRecord> interface_type;
   
private:
   const boost::filesystem::path _path;
   
protected:
   TextCompoundReader(){};
   
   TextCompoundReader(const boost::filesystem::path& path):_path(path){};
   
public:
   ~TextCompoundReader(){};
   
   //implementation ICompoundReader<CompoundRecord>
   virtual CompoundRecordRange get_CompoundRecordRange();
   
};