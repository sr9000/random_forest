#pragma once

#include "stdafx.h"

#include "DecisionTree.h"

class RandomForest;

void trainRandomForest(RandomForest& randomForest, const vector<Item>& trainData, const vector<Item>& testData, int mink = 0, int maxk = 0, uint32_t seed = 42); //because 42 is answer to life the universe and everything!

void trainRandomForest(RandomForest& randomForest, const vector<const Item*>& trainData, const vector<const Item*>& testData, int mink = 0, int maxk = 0, uint32_t seed = 42); //because 42 is answer to life the universe and everything!

struct RandomForest
{
   std::vector<DecisionTree> _forest;

   inline double getClassTrueProbability(const Item& item) const
   {
      double s = 0;
      for (int i = 0; i < _forest.size(); ++i)
         s += _forest[i].getClassTrueProbability(item);
      return s / _forest.size();
   }

   void clear()
   {
      _forest.clear();
   }

   friend void trainRandomForest(RandomForest& randomForest, const vector<Item>& trainData, const vector<Item>& testData, int mink, int maxk, uint32_t seed);

   friend void trainRandomForest(RandomForest& randomForest, const vector<const Item*>& trainData, const vector<const Item*>& testData, int mink, int maxk, uint32_t seed);

};