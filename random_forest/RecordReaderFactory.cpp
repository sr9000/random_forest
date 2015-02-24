#include "precompile_header.h"

#include "RecordReaderFactory.h"
#include "TextRecordReader.h"
#include "Macros.h"

using namespace RecordReaderFactoryType;
using namespace std;

void RecordReaderCreationConfig::set_Path(const boost::filesystem::path& path)
{
   _path = path;
}

void RecordReaderCreationConfig::set_Type(const RecordReaderFactoryTypeEnum& type)
{
   _type = type;
}

const boost::filesystem::path&  RecordReaderCreationConfig::get_Path() const
{
   return _path;
}

const RecordReaderFactoryTypeEnum& RecordReaderCreationConfig::get_Type() const
{
   return _type;
}

void RecordReaderCreationConfig::set_FileFormat(const FileFormat::FileFormatEnum& formatFile)
{
   _formatFile = formatFile;
}

const FileFormat::FileFormatEnum& RecordReaderCreationConfig::get_FileFormat() const
{
   return _formatFile;
}