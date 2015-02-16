#include "precompile_header.h"

#include "CompoundReaderFactory.h"

using namespace std;

int main()
{
   CompoundReaderCreationConfig conf;
   conf.set_Type(CompoundReaderFactoryType::TextFile);
   conf.set_Path(boost::filesystem::path(L"D:\\Files\\code\\sandbox\\Decision tree\\stepan_csv\\stepan_example.csv"));
   CompoundRecordReaderPtr compoundRecordReader = CompoundReaderFactory::createCompoundReader(conf);
   BOOST_FOREACH(CompoundRecord& rec, compoundRecordReader.get()->get_CompoundRange())
   {
      cout << rec._compoundId._inchiCore << " " << rec._features.size() << endl;
   }
   cout << "HW!";
   return 0;
}