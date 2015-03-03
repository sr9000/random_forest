// Random Forest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "../random_forest/IteratorStaticLib.h"
#include "RandomForest.h"
#include "SimilarityAlgorithm.h"

using namespace std;

void exec()
{
   IRecordReader<CompoundRecordOptional>::RecordReaderPtr compoundRR;
   compoundRR = IteratorStaticLib::getCompoundRecordReader("D:/Files/code/sandbox/Decision tree/stepan_csv/stepan_csv.csv");
   int k = 0;
   map<string, CompoundRecord> mapData;
   BOOST_FOREACH(const CompoundRecordOptional& rec, compoundRR->get_RecordRange())
   {
      if (rec)
         //you write here...
   }
   cout << jaccardCoefficient(data[0]->_features, data[1]->_features);
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
      exec();
   }
   catch(const ThrowedException& ex)
   {
      cout << ex.what();
   }
	return 0;
}

