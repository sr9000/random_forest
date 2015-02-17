#include "precompile_header.h"

#include "DirectedStreambuf.h"

DirectedStreambuf::DirectedStreambuf(char* begin, size_t count)
{
   setg(begin, begin, begin + count);
}

DirectedStreambuf::~DirectedStreambuf()
{
   setg(0, 0, 0);
}