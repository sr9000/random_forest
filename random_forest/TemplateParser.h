#pragma once

#include "precompile_header.h"

#include "Macros.h"

namespace FileFormat
{
   enum FileFormatEnum
   {
      Unknown, //uninitialized file format
      EndOfLineSeparator //use "\t" as inline separator, new line as line separator
   };
};

template<typename TRecord>
struct RawRecordParser
{
public:
   static void parse(TRecord&, const std::string&)
   {
      THROWEXCEPTION("No implementation", "\'struct RawRecordParser<TRecord>\' need specialization for TRecord=\'" + std::string(typeid(TRecord).name()) + "\'.");
   }
};

template<FileFormat::FileFormatEnum formatHint, typename TRecord>
struct FormatHintRawRecordParser
{
public:
   static void parse(TRecord&, const std::string&)
   {
      THROWEXCEPTION("No implementation", "\'struct FormatHintRawRecordParser<formatHint, TRecord>\' need specialization for each formatHint=" + std::to_string(formatHint) + " and TRecord=\'" + std::string(typeid(TRecord).name()) + "\'.");
   }
};
