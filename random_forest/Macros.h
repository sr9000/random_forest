#include "precompile_header.h"

typedef std::runtime_error ThrowedException;

#define THROWEXCEPTION(name, details)\
   {\
      std::stringstream str(std::ios_base::out);\
      str << "\nException:   " << name << "\nIn File:     \'" << __FILE__\
         << "\':" << std::to_string(__LINE__) << "\nDetails:     " << details << std::endl;\
      throw  ThrowedException(str.str());\
   }
