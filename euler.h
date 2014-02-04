#include <stdint.h>
#include <error.h>
#include <inttypes.h>

#define checkanswer(a,b,c) if(a==b) { error(0,0,"[ok]; %s",c); } else { error(1,0,"[not ok] ( %"PRId64" != %"PRId64" ) in %s at line %d; %s",(int64_t)a,(int64_t)b,__FILE__, __LINE__,c ); }
#define quietly_checkanswer(a,b,c) if(a!=b) { error(1,0,"[not ok] ( %"PRId64" != %"PRId64" ) in %s at line %d; %s",(int64_t)a,(int64_t)b,__FILE__, __LINE__,c ); }
