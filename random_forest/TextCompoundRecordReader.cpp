#include "precompile_header.h"

#include "TextCompoundRecordReader.h"
#include "TextRecordIterator.h"

using namespace TextRecordIteratorState;

CompoundRecordRange TextCompoundRecordReader::get_CompoundRecordRange()
{
    return CompoundRecordRange(TextRecordIterator<>(_path, Begin), TextRecordIterator<>(_path, Finish));
}