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

/*template <typename T>
inline void outAsByte(FILE* f, const T& val)
{
   //sizeof(T);
   fwrite((void*)(&val), sizeof(T), 1, f);
}

template <typename T>
inline void inAsByte(FILE* f, T& val)
{
   fread((void*)(&val), sizeof(T), 1, f);
}
*/
template <typename TStream, typename T>
inline void outAsByte(TStream& stream, const T& val)
{
   //sizeof(T);
//   fwrite((void*)(&val), sizeof(T), 1, f);
   stream.write((char*)(&val), sizeof(T));
}

template <typename TStream, typename T>
inline void inAsByte(TStream& stream, T& val)
{
   stream.read((char*)(&val), sizeof(T));
}

/*template <typename T>
inline void outAsByte(fstream& stream, const T& val)
{
   //sizeof(T);
   fwrite((void*)(&val), sizeof(T), 1, f);
}

template <typename T>
inline void inAsByte(FILE* f, T& val)
{
   fread((void*)(&val), sizeof(T), 1, f);
}*/

void exec_train()
{
   vector<pair<boost::filesystem::path, boost::filesystem::path> > learningData; //first - train, second - test
   //boost::filesystem::path featuresData("D:/Files/code/sandbox/Decision tree/stepan_csv/stepan_csv.csv");
   //boost::filesystem::path featuresData("D:/Files/code/sandbox/Decision tree/stepan_csv/stepan_example.csv");
   boost::filesystem::path featuresData("D:/Files/code/sandbox/Decision tree/stepan_csv/stepan_csv.bin");
   boost::filesystem::path predData("D:/Files/code/sandbox/Decision tree/targetgen_full_hmr_pred");
   boost::filesystem::path tempDirectory("D:/Files/code/sandbox/Decision tree/other_temp_trees");

   learningData.push_back(
      pair<boost::filesystem::path, boost::filesystem::path>(
         boost::filesystem::path("D:/Files/code/sandbox/Decision tree/My_train1"),
         boost::filesystem::path("D:/Files/code/sandbox/Decision tree/My_test1")));
         

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
      /*BOOST_FOREACH(const CompoundRecordOptional& opRec, IteratorStaticLib::getCompoundRecordReader(featuresData.generic_string())->get_RecordRange())
      {
         if (opRec)
         {
            mapFeaturesData.insert(pair<string, CompoundRecord>(opRec->_compoundId.to_string(), *opRec));
         }
         else
         {
            ++skip;
         }
      }*/
      //FILE* f = fopen(featuresData.generic_string().c_str(), "rb");
      fstream fin(featuresData.generic_string(), std::ios::binary | std::ios::in);
      size_t count;
      inAsByte(fin, count);
      for (int i = 0; i < count; ++i)
      {
         CompoundRecord rec;
         size_t strLen;
         inAsByte(fin, strLen);
         string id;
         id.resize(strLen);
         for (int j = 0; j < strLen; ++j)
         {
            char s;
            inAsByte(fin, s);
            id[j] = s;
         }
         rec._compoundId = id;
         size_t countFt;
         inAsByte(fin, countFt);
         rec._features.resize(countFt);
         for (int j = 0; j < countFt; ++j)
         {
            uint32_t ft;
            inAsByte(fin, ft);
            rec._features[j] = ft;
         }
         mapFeaturesData.insert(pair<string, CompoundRecord>(rec._compoundId.to_string(), rec));
      }
      //fclose(f);
      fin.close();
      LOG << "Done." << endl << "skip: " << skip << endl << "total: " << skip + mapFeaturesData.size();
   }
   else
   {
      THROWEXCEPTION("Error", "No such file \'" + featuresData.generic_string() + "\'");
   }
   //
   //translate mapFeaturesData to binaryformat
  /* {
      fstream fout((featuresData.parent_path() / "stepan_csv.bin").generic_string(), std::ios::binary | std::ios::out);
      outAsByte(fout, mapFeaturesData.size());
      map<string, CompoundRecord>::iterator itr = mapFeaturesData.begin();
      while (itr != mapFeaturesData.end())
      {
         outAsByte(fout, itr->first.length());
         for (int i = 0; i < itr->first.length(); ++i)
            outAsByte(fout, itr->first[i]);
         outAsByte(fout, itr->second._features.size());
         for (int i = 0; i < itr->second._features.size(); ++i)
            outAsByte(fout, itr->second._features[i]);
         ++itr;
      }
      fout.close();
   }
   return;*/
   //
   //TODO: you are stopping here. debug your trainRandomForest!!!
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
                  LOG << "Done." << endl << "Erased: " << skip << endl << "Left: " << testedTargets.second.size();
               }
               //calc features
               pair<vector<Item>, vector<Item> > items(vector<Item>(testedTargets.first.size()), vector<Item>(testedTargets.second.size()));
               for (int i = 0; i < testedTargets.first.size(); ++i)
               {
                  items.first[i]._featuresSize = testedTargets.first.size();
                  items.first[i]._features = new Feature[items.first[i]._featuresSize];//.resize(testedTargets.first.size());
               }
               for (int i = 0; i < testedTargets.second.size(); ++i)
               {
                  items.second[i]._featuresSize = testedTargets.first.size();
                  items.second[i]._features = new Feature[items.second[i]._featuresSize];//.resize(testedTargets.first.size());
               }

               LOG << "Calc features for train data";
               for (int i = 0; i < testedTargets.first.size(); ++i)//BOOST_FOREACH(const TargetRecord& rec, testedTargets.first)
               {
                  map<string, CompoundRecord>::const_iterator itr1 = mapFeaturesData.find(testedTargets.first[i]._compoundId.to_string());
                  //Item item;
                  Item& itemI = items.first[i];
                  itemI._class = testedTargets.first[i]._target;
                  //int n = 0;//reserve, diag
                  for (int j = i; j < testedTargets.first.size(); ++j)//BOOST_FOREACH(const TargetRecord& ft, testedTargets.first)
                  {
                     Feature& itemJFeatureI = items.first[j]._features[i];
                     Feature& itemIFeatureJ = itemI._features[j];

                     map<string, CompoundRecord>::const_iterator itr2 = mapFeaturesData.find(testedTargets.first[j]._compoundId.to_string());//to_string -> int
                     if (i == j)
                     {
                        //itemI._features[i] = Feature(i, 1.0);
                        itemIFeatureJ._number = i;// = Feature(j, l);
                        itemIFeatureJ._value = 1.0;
                        //itemJ._features[i] = Feature(i, l);
                     }
                     else
                     {
                        

                        double l = jaccardCoefficient(itr1->second._features, itr2->second._features);
                        itemIFeatureJ._number = j;// = Feature(j, l);
                        itemIFeatureJ._value = l;
                        itemJFeatureI._number = i;// = Feature(j, l);
                        itemJFeatureI._value = l;
                        //itemJ._features[i] = Feature(i, l);
                     }
                     //++n;
                  }
                  //items.first.push_back(item);
               }
               LOG << "Done.";

               LOG << "Calc features for test data";
               for (int i = 0; i < testedTargets.second.size(); ++i)//BOOST_FOREACH(const TargetRecord& rec, testedTargets.second)
               {
                  map<string, CompoundRecord>::const_iterator itr1 = mapFeaturesData.find(testedTargets.second[i]._compoundId.to_string());
                  //Item item;
                  Item& itemI = items.second[i];
                  itemI._class = testedTargets.second[i]._target;
                  //int n = 0;//reserve
                  for (int j = 0; j < testedTargets.first.size(); ++j)//BOOST_FOREACH(const TargetRecord& ft, testedTargets.first)
                  {
                     Feature& itemIFeatureJ = itemI._features[j];
                     map<string, CompoundRecord>::const_iterator itr2 = mapFeaturesData.find(testedTargets.first[j]._compoundId.to_string());
                     itemIFeatureJ._number = j;
                     itemIFeatureJ._value = jaccardCoefficient(itr1->second._features, itr2->second._features);
                     //++n;
                  }
                  //items.second.push_back(item);
               }
               LOG << "Done.";
               //train forest
               LOG << "Train Forest";
               RandomForest forest;
               trainRandomForest(forest, items.first, items.second, 42, 1, 100);
               LOG << "Done.";
               LOG << "Write forest binary data \'" + (itr->first) + "\'";
               vector<uint8_t> bin;
               forest.serialize(bin);
               boost::filesystem::path forestPath = setPath / itr->first;
               fstream fout(forestPath.generic_string(), std::ios::binary | std::ios::out);
               for (int i = 0; i < bin.size(); ++i)
                  fout.write((char*)(&bin[i]), sizeof(uint8_t));
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

void exec_maketrashold()
{
   //first - path to forests, 
   //second - path to train set,
   //third - path to test set,
   vector<boost::tuples::tuple<boost::filesystem::path, boost::filesystem::path, boost::filesystem::path> > learningData; 
   boost::filesystem::path featuresData("D:/Files/code/sandbox/Decision tree/stepan_csv/stepan_csv.bin");
   boost::filesystem::path tempDirectory("D:/Files/code/sandbox/Decision tree/temp_trees_directory/Set_1");
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
   }
   vector <uint8_t> ser;
   forest.serialize(ser);*/
   /*FileListReaderPtr ls = IteratorStaticLib::getFileListReader("D:/Files/code/sandbox/Decision tree/targetgen_full_hmr_test_1-0");
   BOOST_FOREACH(const boost::filesystem::path& pth, ls->get_Range())
   {
      cout << pth.generic_string() << endl;
   }*/
   try
   {
      init_log();
      exec_train();
   }
   catch(const ThrowedException& ex)
   {
      LOG << ex.what();
      cout << ex.what();
   }
	return 0;
}
