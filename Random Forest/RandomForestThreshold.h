#pragma once

#include "stdafx.h"

#include "RandomForest.h"

struct ContingencyTable
{
public:
   int _tp; //true positive
   int _fp; //false positive
   int _tn; //true negative
   int _fn; //false negative

   ContingencyTable()
      : _tp(0), _fp(0), _tn(0), _fn(0){};

   ContingencyTable(int tp, int fp, int tn, int fn)
      : _tp(tp), _fp(fp), _tn(tn), _fn(fn){};

   bool operator==(const ContingencyTable& other) const;

};

struct FMetricParams
{
public:
   ContingencyTable _table;
   double _alfa; //1 - max precision, 0 - max recall, 0.5 - balance(bad for disbalance sample)

   FMetricParams()
      : _alfa(0.5), _table(ContingencyTable()){};

   FMetricParams(double alfa, ContingencyTable& table)
      : _alfa(alfa), _table(table){};

};

struct ThresholdLevel
{
public:
   FMetricParams _metricParams; //fmetric params
   double _fmetric; //cash value
   double _threshold; //finish threshold value

   ThresholdLevel()
      : _fmetric(1.0), _threshold(0){};
};

struct RandomForestThreshold
{
public:
   RandomForest _forest;
   std::vector<ThresholdLevel> _threshold; 

   std::vector<uint32_t> getClassTrueProbability(const Item&) const;

};

inline double fmetric(const FMetricParams& params);

void FindThreshold(RandomForestThreshold& thrld, const std::vector<Item>& itm, std::vector<double>* ptrAlfaParam = 0);