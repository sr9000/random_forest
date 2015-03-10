#pragma once

#include "stdafx.h"

#include "DecisionTree.h"

class RandomForest;

void trainRandomForest(RandomForest& randomForest, const std::vector<Item>& trainData, const std::vector<Item>& testData, uint32_t seed = 42, int mink = 0, int maxk = 0); //because 42 is answer to life the universe and everything!

void trainRandomForest(RandomForest& randomForest, const std::vector<const Item*>& trainData, const std::vector<const Item*>& testData, uint32_t seed = 42, int mink = 0, int maxk = 0); //because 42 is answer to life the universe and everything!

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

   const void serialize(std::vector<uint8_t>&) const;

   friend void trainRandomForest(RandomForest& randomForest, const std::vector<Item>& trainData, const std::vector<Item>& testData, uint32_t seed, int mink, int maxk);

   friend void trainRandomForest(RandomForest& randomForest, const std::vector<const Item*>& trainData, const std::vector<const Item*>& testData, uint32_t seed, int mink, int maxk);

};