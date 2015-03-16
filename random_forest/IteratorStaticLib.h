#pragma once

#include "precompile_header.h"

#include "CompoundRecord.h"
#include "TargetRecord.h"
#include "RecordReaderFactory.h"
#include "TextRecordReader.h"
#include "FileListReader.h"
#include "FileListReaderFactory.h"

namespace IteratorStaticLib
{
   IRecordReader<TargetRecordOptional>::RecordReaderPtr getTargetRecordReader(const std::string& path);

   IRecordReader<CompoundRecordOptional>::RecordReaderPtr getCompoundRecordReader(const std::string& path);

   IRecordReader<PredRecordOptional>::RecordReaderPtr getPredRecordReader(const std::string& path);

   FileListReaderPtr getFileListReader(const std::string& path);

}