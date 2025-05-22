#ifndef __K12_INC_0_H__
#define __K12_INC_0_H__

#include <stdint.h>
#include <stdlib.h>

#define Z(x)      (sizeof(x))
#define IF(x,y)   {if(x){y;}}
#define PUTC(x)   {putc(x, stdout); fflush(stdout);}
#define CASE(c,x) case c:{x;break;}

/** chars */
using C = uint8_t;
/** sizes */
using S = size_t;
/** ints */
using I = uint32_t;
/** floats */
using F = double;

#include <T.h>

#endif
