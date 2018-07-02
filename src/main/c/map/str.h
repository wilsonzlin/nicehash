#ifndef _HDR_NICEHASH_MAP_STR
#define _HDR_NICEHASH_MAP_STR

#include "../common/map.h"

#define NICEHASH_MAP_STR(value_name, value_t) \
  NICEHASH_CREATE_MAP_INFRA(STR, nh_map_str_##value_name, char *, value_t)

#endif // _HDR_NICEHASH_MAP_STR
