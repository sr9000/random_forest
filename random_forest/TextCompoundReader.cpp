#include "precompile_header.h"

#include "TextCompoundReader.h"
#include "TextCompoundIterator.h"

using namespace TextCompoundIteratorState;

CompoundRecordRange TextCompoundReader::get_CompoundRecordRange()
{
    return CompoundRecordRange(TextCompoundIterator(_path, Begin), TextCompoundIterator(_path, Finish));
}