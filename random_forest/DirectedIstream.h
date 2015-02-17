#pragma once

#include "precompile_header.h"
#include "DirectedStreambuf.h"

class DirectedIstream
{
private:
   typedef boost::shared_ptr<std::istream> istream_ptr;

   DirectedStreambuf _streamBuffer;

   istream_ptr _istreamPtr;

public:
   DirectedIstream(char*, size_t);

private:
   DirectedIstream():_streamBuffer(DirectedStreambuf(0, 0)){};

   DirectedIstream(const DirectedIstream&):_streamBuffer(DirectedStreambuf(0, 0)){};

public:
   operator const std::istream&() const;
   
};

typedef boost::shared_ptr<DirectedIstream> DirectedIstreamPtr;