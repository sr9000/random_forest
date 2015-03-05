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

   lg::add_file_log(filename, lg::keywords::auto_flush = true);
   lg::core::get()->set_filter
   (
      lg::trivial::severity >= lg::trivial::info
   );
}

void exec()
{
   vector<pair<boost::filesystem::path, boost::filesystem::path> > learningData; //first - train, second - test
   boost::filesystem::path featuresData("D:/Files/code/sandbox/Decision tree/stepan_csv/stepan_csv.csv");
   //boost::filesystem::path featuresData("D:/Files/code/sandbox/Decision tree/stepan_csv/stepan_example.csv");
   boost::filesystem::path predData("D:/Files/code/sandbox/Decision tree/targetgen_full_hmr_pred");
   boost::filesystem::path tempDirectory("D:/Files/code/sandbox/Decision tree/temp_trees_directory");

   learningData.push_back(
      pair<boost::filesystem::path, boost::filesystem::path>(
         boost::filesystem::path("D:/Files/code/sandbox/Decision tree/targetgen_full_hmr_train_1-0"),
         boost::filesystem::path("D:/Files/code/sandbox/Decision tree/targetgen_full_hmr_test_1-0")));

   learningData.push_back(
      pair<boost::filesystem::path, boost::filesystem::path>(
         boost::filesystem::path("D:/Files/code/sandbox/Decision tree/targetgen_full_hmr_train_2-2"),
         boost::filesystem::path("D:/Files/code/sandbox/Decision tree/targetgen_full_hmr_test_2-2")));

   map<string, CompoundRecord> mapFeaturesData;
   LOG << "**Read all compound records**";
   if (boost::filesystem::exists(featuresData))
   {
      LOG << "Begin read \'CompoundRecord\' from file \'" + featuresData.generic_string() + "\'";
      int skip = 0;
      BOOST_FOREACH(const CompoundRecordOptional& opRec, IteratorStaticLib::getCompoundRecordReader(featuresData.generic_string())->get_RecordRange())
      {
         if (opRec)
         {
            mapFeaturesData.insert(pair<string, CompoundRecord>(opRec->_compoundId.to_string(), *opRec));
         }
         else
         {
            ++skip;
         }
      }
      LOG << "Done." << endl << "skip: " << skip << endl << "total: " << skip + mapFeaturesData.size();
   }
   else
   {
      THROWEXCEPTION("Error", "No such file \'" + featuresData.generic_string() + "\'");
   }

   LOG << "**Clear temp directory or create it**";
   if (boost::filesystem::exists(tempDirectory))
   {
      LOG << "Begin clean directory \'" + tempDirectory.generic_string() + "\'";
      int total = 0;
      boost::filesystem::directory_iterator end;
      boost::filesystem::directory_iterator itr(tempDirectory);
      while (itr != end)
      {
         boost::filesystem::remove_all(*itr);
         ++itr;
      }
      /*BOOST_FOREACH(const boost::filesystem::path& p, IteratorStaticLib::getFileListReader(tempDirectory.generic_string())->get_Range())
      {
         total += boost::filesystem::remove(p);
      }*/
      LOG << "Done." << endl << "total clean: " << total;
   }
   else
   {
      LOG << "Begin create directory \'" + tempDirectory.generic_string() + "\'";
      if (boost::filesystem::create_directories(tempDirectory))
      {
         LOG << "Done.";
      }
      else
      {
         THROWEXCEPTION("Error", "failure, when execute \'boost::filesystem::create_directories(tempDirectory)\'");
      }
   }
   
   LOG << "**Train forests**";
   for (int i = 0; i < learningData.size(); ++i)
   {
      LOG << "Set #" << i + 1;
      try
      {
         //prepeare
         pair<boost::filesystem::path, boost::filesystem::path> dirs = learningData[i];
         if (!(boost::filesystem::exists(dirs.first) && boost::filesystem::exists(dirs.second)))
            THROWEXCEPTION("Error", "One of {\'" + dirs.first.generic_string() + "\', \'" + dirs.second.generic_string() + "\'} was not found.");

         
         boost::filesystem::path setPath = tempDirectory / ("Set_" + to_string(i + 1));
         LOG << "Create \'" + setPath.generic_string() + "\'";
         if (boost::filesystem::create_directories(setPath))
         {
            LOG << "Done.";
         }
         else
         {
            THROWEXCEPTION("Error", "failure, when execute \'boost::filesystem::create_directories(setPath)\'");
         }
         

         //get files
         pair<map<string, boost::filesystem::path>, map<string, boost::filesystem::path> > traiTestSets; //first - train, second - test
         LOG << "Begin read train set";
         BOOST_FOREACH(const boost::filesystem::path& p, IteratorStaticLib::getFileListReader(dirs.first.generic_string())->get_Range())
         {
            traiTestSets.first.insert(pair<string, boost::filesystem::path>(p.filename().generic_string(), p));
         }
         LOG << "Done.";
         LOG << "Begin read test set";
         BOOST_FOREACH(const boost::filesystem::path& p, IteratorStaticLib::getFileListReader(dirs.second.generic_string())->get_Range())
         {
            traiTestSets.second.insert(pair<string, boost::filesystem::path>(p.filename().generic_string(), p));
         }
         LOG << "Done.";
         LOG << "Train file(s): " << traiTestSets.first.size();
         LOG << "Test file(s): " << traiTestSets.second.size();

         //iterate
         map<string, boost::filesystem::path>::iterator itr;
         map<string, boost::filesystem::path>::const_iterator cnstItr;
         
         for (itr = traiTestSets.first.begin(); itr != traiTestSets.first.end(); ++itr)
         {
            try
            {
               //prepeare data
               LOG << "Train file \'" + itr->first + "\'";
               cnstItr = traiTestSets.second.find(itr->first);
               if (cnstItr == traiTestSets.second.cend())
                  THROWEXCEPTION("No data", "\'" + itr->first + "\' contains in a train set, but not contains in a test set");

               //read data
               pair<vector<TargetRecord>, vector<TargetRecord> > targets;
               {
                  LOG << "Begin read train records";
                  int skip = 0;
                  BOOST_FOREACH(const TargetRecordOptional& opTrg, IteratorStaticLib::getTargetRecordReader(itr->second.generic_string())->get_RecordRange())
                  {
                     if (opTrg)
                     {
                        targets.first.push_back(*opTrg);
                     }
                     else
                     {
                        ++skip;
                     }
                  }
                  LOG << "Done." << endl << "Skip: " << skip << endl << "Total: " << skip + targets.first.size();
               }
               {
                  LOG << "Begin read test records";
                  int skip = 0;
                  BOOST_FOREACH(const TargetRecordOptional& opTrg, IteratorStaticLib::getTargetRecordReader(cnstItr->second.generic_string())->get_RecordRange())
                  {
                     if (opTrg)
                     {
                        targets.second.push_back(*opTrg);
                     }
                     else
                     {
                        ++skip;
                     }
                  }
                  LOG << "Done." << endl << "Skip: " << skip << endl << "Total: " << skip + targets.second.size();
               }
               //test data
               pair<vector<TargetRecord>, vector<TargetRecord> > testedTargets;
               {
                  LOG << "Find features for train set targets.";
                  int skip = 0;
                  BOOST_FOREACH(const TargetRecord& rec, targets.first)
                  {
                     map<string, CompoundRecord>::const_iterator featureItr = mapFeaturesData.find(rec._compoundId.to_string());
                     if (featureItr == mapFeaturesData.cend())
                     {
                        ++skip;
                        LOG << "Target \'" + rec._compoundId.to_string() + "\' ereased";
                     }
                     else
                     {
                        testedTargets.first.push_back(rec);
                     }
                  }
                  LOG << "Done." << endl << "Erased: " << skip << endl << "Left: " << testedTargets.first.size();
               }
               {
                  LOG << "Find features for test set targets.";
                  int skip = 0;
                  BOOST_FOREACH(const TargetRecord& rec, targets.second)
                  {
                     map<string, CompoundRecord>::const_iterator featureItr = mapFeaturesData.find(rec._compoundId.to_string());
                     if (featureItr == mapFeaturesData.cend())
                     {
                        ++skip;
                        LOG << "Target \'" + rec._compoundId.to_string() + "\' ereased";
                     }
                     else
                     {
                        testedTargets.second.push_back(rec);
                     }
                  }
                  LOG << "Done." << endl << "Erased: " << skip << endl << "Left: " << testedTargets.first.size();
               }
               //calc features
               pair<vector<Item>, vector<Item> > items;

               LOG << "Calc features for train data";
               BOOST_FOREACH(const TargetRecord& rec, testedTargets.first)
               {
                  map<string, CompoundRecord>::const_iterator itr1 = mapFeaturesData.find(rec._compoundId.to_string());
                  Item item;
                  item._class = rec._target;
                  int n = 0;
                  BOOST_FOREACH(const TargetRecord& ft, testedTargets.first)
                  {
                     map<string, CompoundRecord>::const_iterator itr2 = mapFeaturesData.find(ft._compoundId.to_string());
                     item._features.push_back(Feature(n, jaccardCoefficient(itr1->second._features, itr2->second._features)));
                     ++n;
                  }
                  items.first.push_back(item);
               }
               LOG << "Done.";

               LOG << "Calc features for test data";
               BOOST_FOREACH(const TargetRecord& rec, testedTargets.second)
               {
                  map<string, CompoundRecord>::const_iterator itr1 = mapFeaturesData.find(rec._compoundId.to_string());
                  Item item;
                  item._class = rec._target;
                  int n = 0;
                  BOOST_FOREACH(const TargetRecord& ft, testedTargets.first)
                  {
                     map<string, CompoundRecord>::const_iterator itr2 = mapFeaturesData.find(ft._compoundId.to_string());
                     item._features.push_back(Feature(n, jaccardCoefficient(itr1->second._features, itr2->second._features)));
                     ++n;
                  }
                  items.second.push_back(item);
               }
               LOG << "Done.";
               //train forest
               LOG << "Train Forest";
               RandomForest forest;
               trainRandomForest(forest, items.first, items.second);
               LOG << "Done.";
               LOG << "Write forest binary data \'" + (itr->first) + "\'";
               vector<uint8_t> bin = forest.serialize();
               boost::filesystem::path forestPath = setPath / itr->first;
               fstream fout(forestPath.generic_string(), std::ios::binary | std::ios::out);
               for (int i = 0; i < bin.size(); ++i)
                  fout << bin[i];
               fout.close();
               LOG << "Done.";
            }
            catch(const ThrowedException& ex)
            {
               LOG << ex.what();
            }
         }
      }
      catch(const ThrowedException& ex)
      {
         LOG << ex.what();
      }
   }

   return;
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
