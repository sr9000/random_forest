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
   TextCompoundIterator first(get_Path(), Begin), last(get_Path(), Finish);
   return CompoundRecordRange(first, last);
}

void TextCompoundReader::set_Path(const boost::filesystem::path& path)
{
   _path = path;
}

const boost::filesystem::path& TextCompoundReader::get_Path() const
{
   return _path;
}