// Random Forest.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include "..\random_forest\IteratorStaticLib.h"
#include "DecisionTree.h"

using namespace std;

int main()
{
   /*BOOST_FOREACH(const CompoundRecordOptional& opRec, IteratorStaticLib::getCompoundRecordReader(std::string("D:/Files/code/projects/MSVS2012/random_forest/random_forest/stepan_example.csv"))->get_RecordRange())
   {
      if (opRec)
         std::cout << opRec->_compoundId.to_string() << std::endl;
      else
         std::cout << "???\n";
   }*/
   vector<Item> data(16);
   int n = 0;
   for (int i = 0; i < 4; ++i)
   {
      for (int j = 0; j < 4; ++j)
      {
         data[n]._class = (i >= 1 && i <= 2 && j >= 1 && j <= 2);
         data[n]._features.push_back(Feature(0, i));
         data[n]._features.push_back(Feature(1, j));
         ++n;
      }
   }
   DecisionTree tree;
   trainDecisionTree(tree, data);
   n = 0;
   for (int i = 0; i < 4; ++i)
   {
      for (int j = 0; j < 4; ++j)
      {
         double x = tree.getClassTrueProbability(data[n]);
         cout << x << "\t";
         ++n;
      }
      cout << endl;
   }
	return 0;
}

