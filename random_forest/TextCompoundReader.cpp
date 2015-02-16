#include "precompile_header.h"

#include "TextCompoundReader.h"
#include "TextCompoundIterator.h"

CompoundRecordRange TextCompoundReader::get_CompoundRange()
{
   TextCompoundIterator first, last;
   first._path = _path;
   last._path = _path;
   
   first._state = TextCompoundIteratorState::Begin;
   last._state = TextCompoundIteratorState::Finish;

   first.init();

   return CompoundRecordRange(first, last);
}