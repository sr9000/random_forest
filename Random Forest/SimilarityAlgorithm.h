#pragma once

#include "stdafx.h"

template <typename T>
double jaccardCoefficient(const std::vector<T>& f, const std::vector<T>& s)
{
   int c = 0;
   for (int i = 0; i < f.size(); ++i)//for
   {
      for (int j = 0; j < s.size(); ++j)//for
      {
         if (f[i] == s[j])
         {
            ++c;
            break;
         }
      }
   }
   return (double)c / (f.size() + s.size() - c);
}