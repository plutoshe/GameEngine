#pragma once
#include <memory>


#define PS_DATCOPY(dst, src, n) \
	{ for (int i = 0; i < (n); i++) (dst)[i] = (src)[i]; }

#define PS_DATCONVERT(TYPE, dst, src, n) \
	{ for (int i = 0; i < (n); i++) (dst)[i] = type((src)[i]); }

#define PS_INITIALIZE(dst, n, value) \
	{ for (int i = 0; i < (n); i++) (dst)[i] = value; }

#define PS_DATCLEAR(TYPE, dst, n) memset(dst, 0, (n)*sizeof(TYPE))

