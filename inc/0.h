#ifndef __K12_INC_0_H__
#define __K12_INC_0_H__

#include <stdint.h>
#include <stdlib.h>

#define Z(x) (sizeof(x))
#define IF(x,y) {if(x){y;}}
#define PUTC(x) {putc(x, stdout); fflush(stdout);}

using C = unsigned char;
using S = size_t;
using I = uint32_t;
using F = double;

#include <T.h>

#endif
