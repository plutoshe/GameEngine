#pragma once
#include <memory>


# define PS_DATCOPY(dst, src, TYPE, n) \
	{ for (int i = 0; i < (n); i++) (dest)[i] = (source)[i]; }

#define PS_DATCONVERT(type,dest,source,n) \
	{ for ( int i = 0; i < (n); i++ ) (dest)[i] = type((source)[i]); }

