#include "stdafx.h"

#include "RandomForest.h"

using namespace std;

typedef boost::mt19937 RNGType;

typedef boost::variate_generator<RNGType, boost::uniform_int<> > RNG;

void trainRandomForest(RandomForest& randomForest, const vector<Item>& trainData, const vector<Item>& testData, int mink, int maxk, uint32_t seed) //because 42 is answer to life the universe and everything!
{
   vector<const Item*> ptrTrainData;
   vector<const Item*> ptrTestData;
   for (int i = 0; i < trainData.size(); ++i)
   {
      ptrTrainData.push_back(&trainData[i]);
   }
   for (int i = 0; i < trainData.size(); ++i)
   {
      ptrTestData.push_back(&testData[i]);
   }
   trainRandomForest(randomForest, ptrTrainData, ptrTestData, mink, maxk, seed);
}

void trainRandomForest(RandomForest& randomForest, const vector<const Item*>& trainData, const vector<const Item*>& testData, int mink, int maxk, uint32_t seed) //because 42 is answer to life the universe and everything!
{
   //validate train data
   if (trainData.empty())
      return;
   //initialize params
   randomForest.clear();
   if (mink == 0)
   {
      mink = 1;
      maxk = trainData.size();
   }
   int M = trainData[0]->_features.size();
   int m = (int)floor(sqrt((double)M));
   //generate subsets
   vector<const Item*>* subset = new vector<const Item*>[maxk];
   vector<int>* subfeature = new vector<int>[maxk];
   RNG rngN(RNGType(seed), boost::uniform_int<>(0, trainData.size() - 1));
   RNG rngB(RNGType(seed), boost::uniform_int<>(0, INT32_MAX));
   for (int k = 0; k <= maxk; ++k)
   {
      for (int j = 0; j < trainData.size(); ++j)
         subset[k].push_back(trainData[rngN()]);
      for (int j = 0, t = m; j < M; ++j)
      {
         if ((rngB() % (M - j)) < t)
         {
            subfeature[k].push_back(j);
            --t;
         }
      }
   }
   //create trees
   randomForest._forest.resize(maxk);
   for (int k = 0; k <= maxk; ++k)
   {
      trainDecisionTree(randomForest._forest[k], subset[k], subfeature[k]);
   }
   //write here...
}