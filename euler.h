#include <stdint.h>
#include <error.h>
#include <inttypes.h>

#define checkanswer(a,b) if(a==b) { error(0,0,"[ok]"); } else { error(1,0,"[not ok] ( %"PRId64" != %"PRId64" ) in %s at line %d",(int64_t)a,(int64_t)b,__FILE__, __LINE__ ); }
