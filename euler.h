#include <stdint.h>
#include <error.h>

#define checkanswer(a,b) if(a==b) { error(0,0,"[ok]"); } else { error(1,0,"[not ok]"); }
