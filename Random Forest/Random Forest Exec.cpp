// Random Forest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../random_forest/IteratorStaticLib.h"
#include "RandomForest.h"
#include "SimilarityAlgorithm.h"
#include "../random_forest/Macros.h"
#include "Macros.h"

using namespace std;

void init_log()
{
   namespace pt = boost::posix_time;
   namespace lg = boost::log;
   string filename = "../logs/log_" + pt::to_iso_string(pt::second_clock::local_time()) + ".log";

   lg::add_file_log(filename);
   lg::core::get()->set_filter
   (
      lg::trivial::severity >= lg::trivial::info
   );
}

void exec()
{
   LOG << "a";
   LOG << "b";
   THROWEXCEPTION("A", "B");
   LOG << "c";
   return;
   /*IRecordReader<CompoundRecordOptional>::RecordReaderPtr compoundRR;
   compoundRR = IteratorStaticLib::getCompoundRecordReader("D:/Files/code/sandbox/Decision tree/stepan_csv/stepan_csv.csv");
   int k = 0;
   map<string, CompoundRecord> mapData;
   {
      int failed = 0;
      BOOST_FOREACH(const CompoundRecordOptional& rec, compoundRR->get_RecordRange())
      {
         if (rec)
            mapData.insert(pair<string, CompoundRecord>(rec->_compoundId.to_string(), *rec));
         else
            ++failed;
      }
      //cout << mapData.s
   }*/
}

int main()
{
   /*BOOST_FOREACH(const CompoundRecordOptional& opRec, IteratorStaticLib::getCompoundRecordReader(std::string("D:/Files/code/projects/MSVS2012/random_forest/random_forest/stepan_example.csv"))->get_RecordRange())
   {
      if (opRec)
         std::cout << opRec->_compoundId.to_string() << std::endl;
      else
         std::cout << "???\n";
   }*/
   /*vector<Item> data(16);
   int n = 0;
   for (int i = 0; i < 4; ++i)
   {
      for (int j = 0; j < 4; ++j)
      {
         data[n]._class = (i >= 1 && i <= 2 && j >= 1 && j <= 2) || (i == 3 && j == 2);
         data[n]._features.push_back(Feature(0, i));
         data[n]._features.push_back(Feature(1, j));
         ++n;
      }
   }
   RandomForest forest;
   trainRandomForest(forest, data, data, 42);
   n = 0;
   for (int i = 0; i < 4; ++i)
   {
      for (int j = 0; j < 4; ++j)
      {
         double x = forest.getClassTrueProbability(data[n]);
         cout.width(10);
         cout << x << "\t";
         ++n;
      }
      cout << endl;
   }*/
   /*FileListReaderPtr ls = IteratorStaticLib::getFileListReader("D:/Files/code/sandbox/Decision tree/targetgen_full_hmr_test_1-0");
   BOOST_FOREACH(const boost::filesystem::path& pth, ls->get_Range())
   {
      cout << pth.generic_string() << endl;
   }*/
   try
   {
      init_log();
      exec();
   }
   catch(const ThrowedException& ex)
   {
      LOG << ex.what();
      cout << ex.what();
   }
	return 0;
}
