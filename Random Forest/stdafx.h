// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#define BOOST_LIB_DIAGNOSTIC

#include <boost/date_time/posix_time/posix_time.hpp> //no i/o just types
#include <boost/date_time/date_clock_device.hpp>
#include <boost/tuple/tuple.hpp>
#include <tbb/pipeline.h>

#include <algorithm>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/filesystem/path.hpp>
#include <boost/foreach.hpp>
#include <boost/function.hpp>
#include <boost/generator_iterator.hpp>
#include <boost/iostreams/device/file_descriptor.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/iterator/iterator_facade.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/optional.hpp>
#include <boost/random.hpp>
#include <boost/range/any_range.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/system/config.hpp>
#include <fstream>
#include <iostream>
#include <istream>
#include <map>
#include <queue>
#include <stdexcept>
#include <stdint.h>
#include <cstdio>
#include <streambuf>
#include <string>
#include <typeinfo>
#include <vector>