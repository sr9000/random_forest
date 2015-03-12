#pragma once

#include "stdafx.h"

#include "RandomForest.h"

struct TrainData
{
public:
   DecisionTree* _tree;
   std::vector<const Item*> const * const _trainData;
   std::vector<int> const * const _numberOfUsedFeatures;

   TrainData(DecisionTree& tree, const std::vector<const Item*>& trainData, const std::vector<int>& numberOfUsedFeatures)
      : _tree(&tree), _trainData(&trainData), _numberOfUsedFeatures(&numberOfUsedFeatures) {}

};

class TrainDecisionTree
{
public:
   void operator()(TrainData* ptr) const;

};

class VectorTreesIterator
{
private:
   mutable std::vector<DecisionTree>::iterator _itr;
   std::vector<DecisionTree>::iterator _end;
   mutable std::vector<std::vector<const Item*> >::const_iterator _itrSubsets;
   mutable std::vector<std::vector<int> >::const_iterator _itrSubfeatures;

public:
   VectorTreesIterator(std::vector<DecisionTree>& v, const std::vector<std::vector<const Item*> >& subSets, const std::vector<std::vector<int> >& subFeatures)
      : _itr(v.begin()), _end(v.end()), _itrSubsets(subSets.begin()), _itrSubfeatures(subFeatures.begin()) {}

   TrainData* operator()(tbb::flow_control& fc) const;

};
