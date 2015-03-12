#include "stdafx.h"

#include "DecisionTree.h"

using namespace std;

bool less<vector<DecisionTree::Node*>::value_type>::operator()(const vector<DecisionTree::Node*>::value_type& left, const vector<DecisionTree::Node*>::value_type& right) const
{
   return left->_controlFooting->_cashDeltaEntropy < right->_controlFooting->_cashDeltaEntropy;
}

double DecisionTree::Node::getClassTrueProbability(const Item& item) const
{
   if (_predictNode)
   {
      if (item.predicate(_predicateFeature))
         return _trueChild->getClassTrueProbability(item);
      else
         return _falseChild->getClassTrueProbability(item);
   }
   else
   {
      return _classTrueProbability;
   }
}

void DecisionTree::clear()
{
   _root.clear();
}

void DecisionTree::Node::clear()
{
   if (_trueChild)
      delete _trueChild;
   if (_falseChild)
      delete _falseChild;
   _trueChild = 0;
   _falseChild = 0;
}

void DecisionTree::Node::serialize(vector<uint8_t>& v) const
{
   const uint8_t finishRoot = 0;
   const uint8_t predicateRoot = 1;
   if (_predictNode)
   {
      v.push_back(predicateRoot);
      for (int i = 0; i < sizeof(Feature); ++i)
         v.push_back(((uint8_t*)&_predicateFeature)[i]);
      _trueChild->serialize(v);
      _falseChild->serialize(v);
   }
   else
   {
      v.push_back(finishRoot);
      for (int i = 0; i < sizeof(double); ++i)
         v.push_back(((uint8_t*)&_classTrueProbability)[i]);
   }
}

void DecisionTree::Node::deserialize(std::vector<uint8_t>::iterator& itr)
{
   const uint8_t finishRoot = 0;
   const uint8_t predicateRoot = 1;
   if (*itr == predicateRoot)
   {
      _predictNode = true;
      for (int i = 0; i < sizeof(Feature); ++i, ++itr)
         ((uint8_t*)&_predicateFeature)[i] = *itr;
      _trueChild = new DecisionTree::Node();
      _trueChild->deserialize(itr);
      _falseChild = new DecisionTree::Node();
      _falseChild->deserialize(itr);
   }
   else
   {
      _predictNode = false;
      for (int i = 0; i < sizeof(double); ++i, ++itr)
         ((uint8_t*)&_classTrueProbability)[i] = *itr;
   }
}

void DecisionTree::serialize(vector<uint8_t>& v) const
{
   _root.serialize(v);
}

void DecisionTree::deserialize(vector<uint8_t>::iterator& itr)
{
   _root.deserialize(itr);
}

inline double entropy(int t, int n)
{
   if (t == 0 || t == n)
      if (n == 0)
         return 1.0;
      else
         return 0.0;

   double x = (double)t / (double)n;
   return -(x * log(x) + (1 - x) * log(1 - x));
}

void splitNode(DecisionTree::Node& node, const vector<int>& numberOfUsedFeatures)
{
   //int nPredict = 0;
   node._controlFooting->_cashDeltaEntropy = -2; //-2 is lower, than any other delta entropy value
   //node._controlFooting->_bestPredict = -1;
   //node._controlFooting->_cashSetPredict[0] = new bool[node._controlFooting->_cashSize];//.resize(node._controlFooting->_set.size());
   //node._controlFooting->_cashSetPredict[1] = new bool[node._controlFooting->_cashSize];//.resize(node._controlFooting->_set.size());

   for (int i = 0; i < numberOfUsedFeatures.size(); ++i)
   {
      for (int j = 0; j < node._controlFooting->_cashSize; ++j)
      {
         const Feature& feature = node._controlFooting->_set[j]->_features[numberOfUsedFeatures[i]];
         int TX = 0;
         int TT = 0;
         int FT = 0;
         for (int k = 0; k < node._controlFooting->_cashSize; ++k)
         {
            //node._controlFooting->_cashSetPredict[nPredict][k] = node._controlFooting->_set[k]->predicate(feature);
            //node._controlFooting->_cashSetPredict[nPredict][k] = node._controlFooting->_set[k]->_features[feature._number]._value < feature._value;
            const vector<Feature>& vFt = node._controlFooting->_set[k]->_features;
            const Feature& ft = vFt[feature._number];
            if ( ft._value < feature._value)//(node._controlFooting->_cashSetPredict[nPredict][k])
            {
               ++TX;
               if (node._controlFooting->_set[k]->_class)
                  ++TT;
            }
            else if (!node._controlFooting->_set[k]->_class)
            {
               ++FT;
            }
         }
         double newTrueSetPredictEntropy = entropy(TT, TX);
         double newFalseSetPredictEntropy = entropy(FT, node._controlFooting->_cashSize - TX);
         double newDeltaEntropy = node._controlFooting->_cashSetEntropy - 0.5 * (newTrueSetPredictEntropy + newFalseSetPredictEntropy);
         if (newDeltaEntropy > node._controlFooting->_cashDeltaEntropy)
         {
            //node._controlFooting->_bestPredict = nPredict;
            //nPredict = (nPredict + 1) % 2;
            node._controlFooting->_cashDeltaEntropy = newDeltaEntropy;
            node._controlFooting->_cashTrueSetPredictEntropy = newTrueSetPredictEntropy;
            node._controlFooting->_cashFalseSetPredictEntropy = newFalseSetPredictEntropy;
            node._predicateFeature = feature;
            node._controlFooting->_cashTX = TX;
         }
      }
   }
}

void trainDecisionTree(DecisionTree& decisionTree, const vector<Item>& trainData, const vector<int>& numberOfUsedFeatures)
{
   vector<const Item*> ptrTrainData;
   for (int i = 0; i < trainData.size(); ++i)
   {
      ptrTrainData.push_back(&trainData[i]);
   }

   trainDecisionTree(decisionTree, ptrTrainData, numberOfUsedFeatures);
}

void trainDecisionTree(DecisionTree& decisionTree, const vector<const Item*>& trainData, const vector<int>& numberOfUsedFeatures)
{
   //exit if no data
   if (trainData.empty())
      return;
   //initialization decisiontree
   decisionTree.clear();
   decisionTree._controlFooting = new DecisionTree::ControlFooting();
   if (numberOfUsedFeatures.empty())
   {
      for (int i = 0; i < trainData.front()->_features.size(); ++i)
         decisionTree._controlFooting->_numberOfUsedFeatures.push_back(i);
   }
   else
   {
      decisionTree._controlFooting->_numberOfUsedFeatures = numberOfUsedFeatures;
   }
   //initialization decisiontree root
   decisionTree._root._controlFooting = new DecisionTree::Node::ControlFooting();
   int t = 0;
   decisionTree._root._controlFooting->_cashSize = trainData.size();
   decisionTree._root._controlFooting->_set = new Item const*[decisionTree._root._controlFooting->_cashSize];//.reserve(decisionTree._root._controlFooting->_cashSize);
   for (int i = 0; i < decisionTree._root._controlFooting->_cashSize; ++i)
   {
      if (trainData[i]->_class) ++t;
      decisionTree._root._controlFooting->_set[i] = trainData[i];
   }
   decisionTree._root._controlFooting->_cashSetEntropy = entropy(t, decisionTree._root._controlFooting->_cashSize);
   //split root
   splitNode(decisionTree._root, decisionTree._controlFooting->_numberOfUsedFeatures);
   decisionTree._controlFooting->_leafs.push(&decisionTree._root);
   //train decision tree
   while(!decisionTree._controlFooting->_leafs.empty())
   {
      //execute split
      DecisionTree::Node& bestNode = *decisionTree._controlFooting->_leafs.top();
      decisionTree._controlFooting->_leafs.pop();
      if (bestNode._controlFooting->_cashDeltaEntropy > 0) //have effect
      {
         bestNode._predictNode = true;
         //fill true child
         bestNode._trueChild = new DecisionTree::Node();
         decisionTree._controlFooting->_trueNode = bestNode._trueChild;
         DecisionTree::Node& tchild = *(decisionTree._controlFooting->_trueNode);
         tchild._controlFooting = new DecisionTree::Node::ControlFooting();
         tchild._controlFooting->_cashSetEntropy = bestNode._controlFooting->_cashTrueSetPredictEntropy;
         //fill false child
         bestNode._falseChild = new DecisionTree::Node();
         decisionTree._controlFooting->_falseNode = bestNode._falseChild;
         DecisionTree::Node& fchild = *(decisionTree._controlFooting->_falseNode);
         fchild._controlFooting = new DecisionTree::Node::ControlFooting();
         fchild._controlFooting->_cashSetEntropy = bestNode._controlFooting->_cashFalseSetPredictEntropy;
         //fill sets
         tchild._controlFooting->_cashSize = bestNode._controlFooting->_cashTX;
         fchild._controlFooting->_cashSize = bestNode._controlFooting->_cashSize - bestNode._controlFooting->_cashTX;
         tchild._controlFooting->_set = new Item const*[tchild._controlFooting->_cashSize];//.reserve(tchild._controlFooting->_cashSize);
         fchild._controlFooting->_set = new Item const*[fchild._controlFooting->_cashSize];//.reserve(fchild._controlFooting->_cashSize);
         int ti = 0;
         int fi = 0;
         for (int i = 0; i < bestNode._controlFooting->_cashSize; ++i)
         {
            if (bestNode._controlFooting->_set[i]->_features[bestNode._predicateFeature._number]._value < bestNode._predicateFeature._value)//(bestNode._controlFooting->_cashSetPredict[bestNode._controlFooting->_bestPredict][i])
            {
               tchild._controlFooting->_set[ti] = bestNode._controlFooting->_set[i];
               ++ti;
            }
            else
            {
               fchild._controlFooting->_set[fi] = bestNode._controlFooting->_set[i];
               ++fi;
            }
         }
      }
      else
      {
         bestNode._predictNode = false;
         int t = 0;
         for (int i = 0; i < bestNode._controlFooting->_cashSize; ++i)
            if (bestNode._controlFooting->_set[i]->_class)
               ++t;
         bestNode._classTrueProbability = (double)t / (double)(bestNode._controlFooting->_cashSize);
      }
      //clear controlFooting
      delete bestNode._controlFooting;
      //split childs
      if (decisionTree._controlFooting->_trueNode)
      {
         splitNode(*decisionTree._controlFooting->_trueNode, decisionTree._controlFooting->_numberOfUsedFeatures);
         decisionTree._controlFooting->_leafs.push(decisionTree._controlFooting->_trueNode);
         decisionTree._controlFooting->_trueNode = 0;
      }
      if (decisionTree._controlFooting->_falseNode)
      {
         splitNode(*decisionTree._controlFooting->_falseNode, decisionTree._controlFooting->_numberOfUsedFeatures);
         decisionTree._controlFooting->_leafs.push(decisionTree._controlFooting->_falseNode);
         decisionTree._controlFooting->_falseNode = 0;
      }
   }
   delete decisionTree._controlFooting;
}