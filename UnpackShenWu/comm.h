
#ifndef __INCLUDE_COMMON_H__
#define __INCLUDE_COMMON_H__

#define SAFE_RELEASE(p)  do{ if (p) { delete p; p = NULL;}} while (0)

#endif