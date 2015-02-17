#pragma once

#include "precompile_header.h"

#include "ICompoundReader.h"
#include "CompoundRecord.h"
#include "CompoundReaderFactory.h"

class TextCompoundReader: public ICompoundReader<CompoundRecord>
{
   friend class CompoundReaderFactory;
   
protected:
   typedef ICompoundReader<CompoundRecord> interface_type;
   
private:
   boost::filesystem::path _path;
   
protected:
   TextCompoundReader(){};
   
   TextCompoundReader(const boost::filesystem::path& path);
   
public:
   ~TextCompoundReader(){};
   
   //implementation ICompoundReader<CompoundRecord>
   virtual CompoundRecordRange get_CompoundRecordRange();
   
   void set_Path(const boost::filesystem::path&);
   
   const boost::filesystem::path& get_Path() const;
   
};