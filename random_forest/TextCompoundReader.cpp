#include "precompile_header.h"

#include "TextCompoundReader.h"
#include "TextCompoundIterator.h"

CompoundRecordRange TextCompoundReader::get_CompoundRange()
{
   TextCompoundIterator first(_path, TextCompoundIteratorState::Begin), last(_path, TextCompoundIteratorState::Finish);
   return CompoundRecordRange(first, last);
}