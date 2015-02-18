#include "precompile_header.h"

#include "CompoundReaderFactory.h"
#include "TextCompoundReader.h"

using namespace std;

#include <ctime>

#include "Macros.h"

//iterator for read traindata

//randomforest

void execute()
{
   CompoundReaderCreationConfig conf;
   conf.set_Type(CompoundReaderFactoryType::TextFile);
   conf.set_Path(boost::filesystem::path("stepan_example.csv"));
   CompoundRecordReaderPtr compoundRecordReader = CompoundReaderFactory::createCompoundReader(conf);
   clock_t b = clock();
   int i = 0;
   //THROWEXCEPTION("test", "test test");
   BOOST_FOREACH(const CompoundRecordOptional& rec, compoundRecordReader->get_CompoundRecordRange())
   {
      ++i;
      if (!(i%1000)) cout << "!";
      if (rec)
      {
         CompoundRecord rec2;
         rec2 = *rec;
         cout << rec2._compoundId._inchiCore << "-" 
            << rec2._compoundId._inchiStereo << "-" 
            << rec2._compoundId._inchiChecksum << " " << rec2._features.size() << endl;
      }
      else
      {
         cout << "no data\n";
      }
   }
   cout << i << endl;
   cout << clock() - b << endl;
   cout << "HW!";
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