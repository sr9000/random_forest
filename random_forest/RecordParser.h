#pragma once

#include "precompile_header.h"

#include "TemplateParser.h"
#include "CompoundRecord.h"

template<>
struct RawRecordParser<CompoundRecordOptional>
{
   static void parse(CompoundRecordOptional&, const std::string&);
};

template<>
struct FormatHintRawRecordParser<FileFormat::EndOfLineSeparator, CompoundRecordOptional>
{
   static void parse(CompoundRecordOptional&, const std::string&);
};