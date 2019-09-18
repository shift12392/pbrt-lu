#pragma once



#include <cassert>


#define DCHECK( c ) assert( (c) )



#ifdef PBRT_FLOAT_AS_DOUBLE
typedef double Float;
#else
typedef float Float;
#endif  // PBRT_FLOAT_AS_DOUBLE
