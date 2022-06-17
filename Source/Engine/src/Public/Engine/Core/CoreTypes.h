#pragma once

#include <string>

typedef char i8;
typedef short i16;
typedef int i32;
typedef long long i64;

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef unsigned long long u64;

typedef float f32;
typedef double f64;

static_assert(sizeof(i8) == 1, "i8 is not 1 byte");
static_assert(sizeof(i16) == 2, "i16 is not 2 bytes");
static_assert(sizeof(i32) == 4, "i32 is not 4 bytes");
static_assert(sizeof(i64) == 8, "i64 is not 8 bytes");

static_assert(sizeof(u8) == 1, "u8 is not 1 byte");
static_assert(sizeof(u16) == 2, "u16 is not 2 bytes");
static_assert(sizeof(u32) == 4, "u32 is not 4 bytes");
static_assert(sizeof(u64) == 8, "u64 is not 8 bytes");

static_assert(sizeof(f32) == 4, "f32 is not 4 bytes");
static_assert(sizeof(f64) == 8, "f64 is not 8 bytes");

#define I8_MIN (-128)
#define I8_MAX 127
#define I16_MIN (-32768)
#define I16_MAX 32767
#define I32_MIN (-2147483648)
#define I32_MAX 2147483647
#define I64_MIN (-9223372036854775808)
#define I64_MAX 9223372036854775807

#define U8_MIN 0
#define U8_MAX 255
#define U16_MIN 0
#define U16_MAX 65535
#define U32_MIN 0
#define U32_MAX 4294967295
#define U64_MIN 0
#define U64_MAX 18446744073709551615

#define F32_MIN (-3.402823466e+38F)
#define F32_MAX 3.402823466e+38F
#define F64_MIN (-1.7976931348623158e+308)
#define F64_MAX 1.7976931348623158e+308

#define VERSION(major, minor, patch) \
    ((((u32)(major)) << 22) | (((u32)(minor)) << 12) | ((u32)(patch)))

#define VERSION_MAJOR(version) ((u32)((version) >> 22))
#define VERSION_MINOR(version) ((u32)((version) >> 12) & 0x3ff)
#define VERSION_PATCH(version) ((u32)(version) & 0xfff)

#define VERSION_STRING(version, suffix) \
    ("v" \
    + std::to_string(VERSION_MAJOR(version)) \
    + "." + std::to_string(VERSION_MINOR(version)) \
    + "." + std::to_string(VERSION_PATCH(version)) \
    + (!(suffix).empty() ? "-" + (suffix) : ""))