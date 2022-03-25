#pragma once

#ifndef __COMMON_H__
#define __COMMON_H__

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <stdarg.h>

#include <time.h>
#include <math.h>

#define PI 3.141592  //3.14159265359f
#define PI2 6.283185 //6.28318530718f

#define PI_M ((4) * atan(1));
#define DEG2RAD(x) ((x)*((PI)/(180)))

#define DTYPE double
#define MACRO_TO_STRING(x) #x

typedef char* string_dir;
typedef char* type_t;

typedef DTYPE dtype; // for general programming

typedef int pIdx; // pointer index


#ifdef _GCC_COMPILER
// no use msvc compiler
typedef unsigned int size_t;
#endif

#endif