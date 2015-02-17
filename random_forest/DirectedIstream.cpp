#include "precompile_header.h"

#include "DirectedIstream.h"

using namespace std;

DirectedIstream::DirectedIstream(char* begin, size_t count):_streamBuffer(begin, count),_istreamPtr(new istream(&_streamBuffer))
{

}

DirectedIstream::operator const std::istream&() const
{
   return *(_istreamPtr.get());
}