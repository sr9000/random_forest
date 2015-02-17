#include "precompile_header.h"

#include "TextCompoundReader.h"
#include "TextCompoundIterator.h"

using namespace TextCompoundIteratorState;

TextCompoundReader::TextCompoundReader(const boost::filesystem::path& path)
{
   set_Path(path);
}

CompoundRecordRange TextCompoundReader::get_CompoundRecordRange()
{
    return CompoundRecordRange(TextCompoundIterator(get_Path(), Begin), TextCompoundIterator(get_Path(), Finish));
}

void TextCompoundReader::set_Path(const boost::filesystem::path& path)
{
   _path = path;
}

const boost::filesystem::path& TextCompoundReader::get_Path() const
{
   return _path;
}