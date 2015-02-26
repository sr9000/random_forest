#include "precompile_header.h"

#include "IteratorStaticLib.h"

namespace IteratorStaticLib
{
   IRecordReader<TargetRecordOptional>::RecordReaderPtr getTargetRecordReader(const std::string& path)
   {
      RecordReaderCreationConfig conf;
      conf.set_Type(RecordReaderFactoryType::TextFile);
      conf.set_Path(boost::filesystem::path(path));
      conf.set_FileFormat(FileFormat::EndOfLineSeparator);
      return RecordReaderFactory<TargetRecordOptional>::createRecordReader(conf);
   }

   IRecordReader<CompoundRecordOptional>::RecordReaderPtr getCompoundRecordReader(const std::string& path)
   {
      RecordReaderCreationConfig conf;
      conf.set_Type(RecordReaderFactoryType::TextFile);
      conf.set_Path(boost::filesystem::path(path));
      conf.set_FileFormat(FileFormat::EndOfLineSeparator);
      return RecordReaderFactory<CompoundRecordOptional>::createRecordReader(conf);
   }

}

//#include "precompile_header.h"
//
//#include "CompoundRecord.h"
//#include "TargetRecord.h"
//#include "RecordReaderFactory.h"
//#include "TextRecordReader.h"
//
//using namespace std;
//
//#include "Macros.h"

//iterator for read traindata

//randomforest

//void execute()
//{
//   RecordReaderCreationConfig conf;
//   conf.set_Type(RecordReaderFactoryType::TextFile);
//   //TargetRecord: "D:/Files/code/sandbox/Decision tree/targetgen_full_hmr_test_1-0/O00141_level6.train"
//   //CompoundRecord: "stepan_example.csv"
//   conf.set_Path(boost::filesystem::path("D:/Files/code/sandbox/Decision tree/targetgen_full_hmr_test_1-0/O00141_level6.train"));
//   conf.set_FileFormat(FileFormat::EndOfLineSeparator);
//   IRecordReader<TargetRecordOptional>::RecordReaderPtr compoundRecordReader = RecordReaderFactory<TargetRecordOptional>::createRecordReader(conf);
//   int i = 0;
//   //THROWEXCEPTION("test", "test test");
//   BOOST_FOREACH(const TargetRecordOptional& rec, compoundRecordReader->get_RecordRange())
//   {
//      ++i;
//      if (rec)
//      {
//         TargetRecord rec2;
//         rec2 = *rec;
//         cout << rec2._compoundId.to_string() << " " << rec2._target << endl;
//      }
//      else
//      {
//         cout << "<<no data>>\n";
//      }
//   }
//   cout << "total: " << i << endl;
//}
//
//int main()
//{
//   try
//   {
//      execute();
//   }
//   catch(const ThrowedException& ex)
//   {
//      cout << ex.what();
//   }
//   return 0;
//}