#include "precompile_header.h"

#include "CompoundReaderFactory.h"
#include "TextCompoundReader.h"

using namespace std;

#include "Macros.h"

//iterator for read traindata

//randomforest

void execute()
{
   CompoundReaderCreationConfig conf;
   conf.set_Type(CompoundReaderFactoryType::TextFile);
   conf.set_Path(boost::filesystem::path("stepan_example.csv"));
   CompoundRecordReaderPtr compoundRecordReader = CompoundReaderFactory::createCompoundReader(conf);
   int i = 0;
   //THROWEXCEPTION("test", "test test");
   BOOST_FOREACH(const CompoundRecordOptional& rec, compoundRecordReader->get_CompoundRecordRange())
   {
      ++i;
      if (rec)
      {
         CompoundRecord rec2;
         rec2 = *rec;
         cout << rec2._compoundId.to_string() << " " << rec2._features.size() << endl;
      }
      else
      {
         cout << "<<no data>>\n";
      }
   }
   cout << "total: " << i << endl;
}

int main()
{
   try
   {
      execute();
   }
   catch(ThrowedException ex)
   {
      cout << ex.what();
   }
   return 0;
}