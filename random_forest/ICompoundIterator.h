#pragma once

#include "precompile_header.h"

#include "CompoundRecord.h"
/*
class ICompoundIterator: boost::iterator_facade <ICompoundIterator, CompoundRecord, boost::forward_traversal_tag>
{
public:
   ICompoundIterator(){}
   
   virtual ~ICompoundIterator(){}
   
protected:
   //implementation boost::iterator_facade < ... >
   friend class boost::iterator_core_access;
   
   virtual void increment() = 0;
   
   virtual bool equal(const ICompoundIterator& other) const = 0;
   
   virtual CompoundRecord& dereference() const = 0;
   
};*/