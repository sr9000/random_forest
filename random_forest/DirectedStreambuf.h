#pragma once

#include "precompile_header.h"

class DirectedStreambuf : public std::streambuf
{
public:
   DirectedStreambuf(char* begin, size_t count);

   ~DirectedStreambuf();

};

typedef boost::shared_ptr<DirectedStreambuf> DirectedStreambufPtr;