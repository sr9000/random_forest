#pragma once

#include "stdafx.h"

template <typename T>
double jaccardCoefficient(const std::vector<T>& f, const std::vector<T>& s)
{
   int c = 0;
   BOOST_FOREACH(const T& ff, f)
   {
      BOOST_FOREACH(const T& ss, s)
      {
         if (ss == ff)
         {
            ++c;
            break;
         }
      }
   }
   return (double)c / (f.size() + s.size() - c);
}