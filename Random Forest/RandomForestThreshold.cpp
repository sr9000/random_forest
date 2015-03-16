#include "stdafx.h"

#include "RandomForestThreshold.h"

using namespace std;

vector<uint32_t> RandomForestThreshold::getClassTrueProbability(const Item& item) const
{
   vector<uint32_t> res(_threshold.size());
   double val = _forest.getClassTrueProbability(item);
   for (int i = 0; i < res.size(); ++i)
   {
      if (val < _threshold[i]._threshold)
         res[i] = 0;
      else
         res[i] = 1;
   }
   return res;
}

bool ContingencyTable::operator==(const ContingencyTable& other) const
{
   return _tp == other._tp && _fp == other._fp && _tn == other._tn && _fn == other._fn;
}

bool myLess (const pair<double, const Item*>& f, const pair<double, const Item*>& s)
{
   return f.first < s.first;
}

inline double fmetric(const FMetricParams& params)
{
   if (params._table == ContingencyTable())
      return 1.0;
   double _1_p = (params._table._tp + params._table._fp) / (double)params._table._tp; //1 / precision
   double _1_r = (params._table._tp + params._table._fn) / (double)params._table._tp; //1 / recall
   return 1.0 / (params._alfa * _1_p + (1 - params._alfa) * _1_r);
}

inline double mcc(const ContingencyTable& t)
{
   return (t._tp * t._tn - t._fp * t._fn) / sqrt((double)(t._tp + t._fp) * (double)(t._tp + t._fn) * (double)(t._tn + t._fp) * (double)(t._tn + t._fn));
}

void FindThreshold(RandomForestThreshold& thrld, const std::vector<Item>& itm, std::vector<double>* ptrAlfaParam)
{
   //fill predict
   vector<pair<double, const Item*> > arr(itm.size());
   for (int i = 0; i < itm.size(); ++i)
      arr[i] = pair<double, const Item*>(thrld._forest.getClassTrueProbability(itm[i]), &itm[i]);
   //sort by predict
   sort(arr.begin(), arr.end(), myLess);
   //calc true class for n first items
   int *mas = new int[itm.size() + 1];
   mas[0] = 0;
   for (int i = 1; i <= itm.size(); ++i)
   {
      mas[i] = (arr[i - 1].second->_class ? 1 : 0) + mas[i - 1];
   }
   //select alfa params
   if (ptrAlfaParam == 0)
   {
      double temp[] = {1/10.0, 1/4.0, 1/3.0, 1/2.0, 2/3.0, 3/4.0, 9/10.0};
      int sz = 7;
      thrld._threshold.resize(sz + 1);
      for (int i = 1; i <= sz; ++i)
         thrld._threshold[i]._metricParams._alfa = temp[i - 1];
   }
   else
   {
      thrld._threshold.resize(ptrAlfaParam->size() + 1);
      for (int i = 1; i <= ptrAlfaParam->size(); ++i)
         thrld._threshold[i]._metricParams._alfa = (*ptrAlfaParam)[i - 1];
   }
   //calc best thresholds
   ContingencyTable tb;
   double th = 0.0;
   vector<pair<double, const Item*> >::const_iterator citr = arr.cbegin();
   //zero threshold
   //fill table
   tb._fn = mas[citr - arr.cbegin()];
   tb._tn = (citr - arr.cbegin()) - tb._fn;
   tb._tp = mas[arr.size()] - tb._fn;
   tb._fp = arr.size() - tb._fn - tb._tn - tb._tp;
   thrld._threshold[0]._metricParams._alfa = tb._tp / (double)arr.size();
   //calc fmetric foreach alfa param
   for (vector<ThresholdLevel>::iterator itr = thrld._threshold.begin(); itr != thrld._threshold.end(); ++itr)
   {
      itr->_threshold = th;
      itr->_metricParams._table = tb;
      itr->_fmetric = fmetric(itr->_metricParams);
   }
   //others
   //find next threshold
   citr = upper_bound(arr.cbegin(), arr.cend(), pair<double, const Item*>(th, 0), myLess);
   while (citr != arr.cend())
   {
      th = citr->first;
      //fill table
      tb._fn = mas[citr - arr.cbegin()];
      tb._tn = (citr - arr.cbegin()) - tb._fn;
      tb._tp = mas[arr.size()] - tb._fn;
      tb._fp = arr.size() - tb._fn - tb._tn - tb._tp;
      //calc fmetric foreach alfa param
      for (vector<ThresholdLevel>::iterator itr = thrld._threshold.begin(); itr != thrld._threshold.end(); ++itr)
      {
         double newFMetric = fmetric(FMetricParams(itr->_metricParams._alfa, tb));
         if (newFMetric > itr->_fmetric)
         {
            itr->_threshold = th;
            itr->_metricParams._table = tb;
            itr->_fmetric = newFMetric;
         }
      }
      //find next threshold
      citr = upper_bound(arr.cbegin(), arr.cend(), pair<double, Item*>(th, 0), myLess);
   }
}