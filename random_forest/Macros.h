#include <stdexcept>
#include <string>

typedef std::runtime_error ThrowedException;

#define THROWEXCEPTION(name, details)\
   {\
      std::string msg = "\nException:   ";\
      msg += name; msg += "\nIn File:     \'"; msg += __FILE__; msg += "\':"; msg += std::to_string(__LINE__);\
      msg += "\nDetails:     "; msg += details; msg += "\n";\
      throw  ThrowedException(msg);\
   }
