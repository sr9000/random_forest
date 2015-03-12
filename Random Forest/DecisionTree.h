#pragma once

#include "stdafx.h"

struct Feature
{
public:
   int _number;
   
   double _value;

   Feature(){};

   Feature(int number, double value)
      :_number(number), _value(value){};
   
   inline bool predicate(const double value) const
   {
      return _value < value;
   }
   
};

struct Item
{
   Feature* _features;

   int _featuresSize;
   
   bool _class; //true - item is belong to class, false - else.

   Item(){};

   Item(const bool& clazz):_class(clazz){};
   
   inline bool predicate(const Feature& feature) const
   {
      return _features[feature._number].predicate(feature._value);
   }

   ~Item()
   {
      delete[] _features;
   }
   
};

struct DecisionTree
{
   struct Node
   {
      struct ControlFooting
      {
         Item const** _set;
         
         double _cashSetEntropy;

         double _cashDeltaEntropy;
         
         //bool* _cashSetPredict[2];

         double _cashTrueSetPredictEntropy;

         double _cashFalseSetPredictEntropy;
         
         //int _bestPredict; //(-1) - no best predict, 0 - _cashSetPredict[0], 1 - _cashSetPredict[1]

         int _cashTX;

         int _cashSize;

         ControlFooting()
            : _set(0) {}

         ~ControlFooting()
         {
            //delete[] _cashSetPredict[0];
            //delete[] _cashSetPredict[1];
            delete[] _set;
         }
         
      };
      
      ControlFooting* _controlFooting;
      
      bool _predictNode; //true - check predicate, false - take answer
      
      double _classTrueProbability; //probability of item is belong to class.
      
      Feature _predicateFeature;
      
      Node* _trueChild;
      
      Node* _falseChild;

      Node():_trueChild(0), _falseChild(0), _controlFooting(0){};

      ~Node()
      {
         clear();
      }
      
      double getClassTrueProbability(const Item&) const;

      void clear();

      void serialize(std::vector<uint8_t>& v) const;

      void deserialize(std::vector<uint8_t>::iterator& itr);
      
   };
   
   struct ControlFooting
   {
      std::vector<int> _numberOfUsedFeatures;
      
      std::priority_queue<Node*> _leafs;
      
      Node* _trueNode;
      
      Node* _falseNode;

      ControlFooting():_trueNode(0), _falseNode(0){};
      
   };

   ControlFooting* _controlFooting;
   
   Node _root;

   DecisionTree():_controlFooting(0){};

   ~DecisionTree()
   {
      clear();
   }
   
   inline double getClassTrueProbability(const Item& item) const
   {
      return _root.getClassTrueProbability(item);
   }

   void clear();

   void serialize(std::vector<uint8_t>&) const;

   void deserialize(std::vector<uint8_t>::iterator&);
   
};

void trainDecisionTree(DecisionTree& decisionTree, const std::vector<Item>& trainData, const std::vector<int>& numberOfUsedFeatures = std::vector<int>());

void trainDecisionTree(DecisionTree& decisionTree, const std::vector<const Item*>& trainData, const std::vector<int>& numberOfUsedFeatures = std::vector<int>());