#include "precompile_header.h"

#include "CompoundReaderFactory.h"

using namespace std;

#include <ctime>

//use memory mapped file boost

//iterator must skipped invalide records boost_optional

//iterator for read traindata

//randomforest

int main()
{
   CompoundReaderCreationConfig conf;
   conf.set_Type(CompoundReaderFactoryType::TextFile);
   conf.set_Path(boost::filesystem::path(L"D:\\Files\\code\\sandbox\\Decision tree\\stepan_csv\\stepan_example.csv"));
   CompoundRecordReaderPtr compoundRecordReader = CompoundReaderFactory::createCompoundReader(conf);
   clock_t b = clock();
   BOOST_FOREACH(CompoundRecord& rec, compoundRecordReader.get()->get_CompoundRange())
   {
      rec._features.clear();
   }
   cout << clock() - b << endl;
   cout << "HW!";
   return 0;
}