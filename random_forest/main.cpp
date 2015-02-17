#include "precompile_header.h"

#include "CompoundReaderFactory.h"
#include "TextCompoundReader.h"

using namespace std;

#include <ctime>

//use memory mapped file boost..

//iterator must skipped invalide records boost_optional

//iterator for read traindata

//randomforest

int main()
{
   CompoundReaderCreationConfig conf;
   conf.set_Type(CompoundReaderFactoryType::TextFile);
   conf.set_Path(boost::filesystem::path("D:/Files/code/sandbox/Decision tree/stepan_csv/stepan_csv.csv"));
   CompoundRecordReaderPtr compoundRecordReader = CompoundReaderFactory::createCompoundReader(conf);
   clock_t b = clock();
   int i = 0;
   BOOST_FOREACH(const CompoundRecord& rec, compoundRecordReader->get_CompoundRecordRange())
   {
      CompoundRecord rec2(rec);
      ++i;
      if (!(i%1000)) cout << "!";
      //rec._features.clear();
      //cout << rec2._compoundId._inchiCore << " " << rec2._features.size() << endl;
   }
   cout << i << endl;
   cout << clock() - b << endl;
   cout << "HW!";
   return 0;
}