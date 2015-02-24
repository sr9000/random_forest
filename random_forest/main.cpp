#include "precompile_header.h"

#include "CompoundRecord.h"
#include "RecordReaderFactory.h"
#include "TextRecordReader.h"

using namespace std;

#include "Macros.h"

//iterator for read traindata

//randomforest

void execute()
{
   RecordReaderCreationConfig conf;
   conf.set_Type(RecordReaderFactoryType::TextFile);
   conf.set_Path(boost::filesystem::path("stepan_example.csv"));
   conf.set_FileFormat(FileFormat::EndOfLineSeparator);
   IRecordReader<CompoundRecordOptional>::RecordReaderPtr compoundRecordReader = RecordReaderFactory<CompoundRecordOptional>::createRecordReader(conf);
   int i = 0;
   //THROWEXCEPTION("test", "test test");
   BOOST_FOREACH(const CompoundRecordOptional& rec, compoundRecordReader->get_RecordRange())
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
   catch(const ThrowedException& ex)
   {
      cout << ex.what();
   }
   return 0;
}