#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <fcntl.h>
#include <math.h>
#include <time.h>
#include <stdarg.h>
#include <errno.h>
#include <locale.h>

#if LINUX
#include <unistd.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#elif WINDOWS
#include <windows.h>
#endif

#define STB_SPRINTF_IMPLEMENTATION
#include "external_libs/stb_sprintf.h"
#include "external_libs/utf8.h"

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

#define U16_MAX 65535
#define S32_MAX 0x7fffffff
#define U32_MAX ((u32)-1)
#define U64_MAX ((u64)-1)
#define F32_MAX FLT_MAX
#define F32_MIN -FLT_MAX

#define array_count(array) (sizeof(array)/sizeof((array)[0]))

#if DEBUG
#define assert(expression, ...) if(!(expression)) { *(int*)0 = 0; }
#else
#define assert(expression, ...)
#endif

// MIN and MAX are already definend in Cocoa.h. Undef to avoid 'macro redefinition warning'.
#undef MIN
#undef MAX
#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define CLAMP(x_min, x, x_max)  ((x) < (x_min) ? (x_min) : (x) > (x_max) ? (x_max) : (x))
#define ABS(x) ((x) >= 0 ? (x) : -(x))

#define concat_(a,b) a##b
#define concat(a,b) concat_(a, b)

#define kilobytes(value) ((value)*1024LL)
#define megabytes(value) (kilobytes(value)*1024LL)
#define gigabytes(value) (megabytes(value)*1024LL)
#define terabytes(value) (gigabytes(value)*1024LL)

#define _for_each3(p, array, num_elements)           for ((p) = (array); (p) < (array) + (num_elements); ++(p))
#define _for_each4(p, index, array, num_elements)    for ((p) = (array), (index) = 0; (index) < (num_elements); ++(p), ++(index))
#define _OVERLOAD_for_each(_1, _2, _3, _4, NAME, ...) NAME
#define for_each(...) _OVERLOAD_for_each(__VA_ARGS__, _for_each4, _for_each3)(__VA_ARGS__)

// #define _for_range2(index, to)                       for ((index) = 0; (index) < (to); ++(index))
#define for_range(index, from, to)                 for ((index) = (from); (index) < (to); ++(index))
// #define _OVERLOAD_for_range(_1, _2, _3, NAME, ...) NAME
// #define for_range(...) _OVERLOAD_for_range(__VA_ARGS__, _for_range3, _for_range2)(__VA_ARGS__)

#define INVALID_CODE_PATH assert(!"INVALID_CODE_PATH")
#define INVALID_DEFAULT_CASE default: {INVALID_CODE_PATH;} break

#define global static
#define local_persist static
#define function static

#include "types.h"
#include "doubly_linked_list.h"
#include "queue.h"
#include "stack.h"
#include "bits.h"
#include "memory.cpp"
#include "math/math.h"
#include "string.cpp"
#include "file.cpp"

#if LINUX
#include "platforms/linux/time.cpp"
#elif WINDOWS
#include "platforms/windows/logging.cpp"
#endif
