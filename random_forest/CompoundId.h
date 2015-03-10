#pragma once

#include "precompile_header.h"

class CompoundIdException : public std::exception
{
public:
   CompoundIdException(){}
   
};

struct CompoundId
{
private:
   std::string _inchiCore;
   std::string _inchiStereo;
   std::string _inchiChecksum;
   std::string _fullString;
public:
   CompoundId(){};
   
   CompoundId(const CompoundId& other)
      :_inchiCore(other._inchiCore),_inchiStereo(other._inchiStereo),_inchiChecksum(other._inchiChecksum),_fullString(other._fullString)
   {};
   
   CompoundId(const std::string& full_compound);

   const std::string& to_string() const;

   CompoundId& operator=(const CompoundId&);
   
};