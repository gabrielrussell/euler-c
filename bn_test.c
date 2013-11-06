#include <error.h>
#include <inttypes.h>

#include "bn.h"
#include "dar.h"
#include "euler.h"

int main( int argc, char ** argv ) {

    uint32_t x;
    uint32_t y;
    uint64_t z;

    bn_t * n = bn_new();
    bn_destroy(n);

    n = bn_from_uint32(8);
    checkanswer(n->dar->element_count,1);
    dar_fetch(n->dar,&x,0);
    checkanswer(x,8);
    y = bn_to_uint32(n);
    checkanswer(y,8);
    z = bn_to_uint64(n);
    checkanswer(z,8);
    bn_destroy(n);

    n = bn_from_uint64(281474976710657) ;
    checkanswer(n->dar->element_count,2);
    checkanswer(bn_to_uint64(n),281474976710657);
    bn_destroy(n);

    n = bn_from_uint32(8);
    bn_t * m = bn_copy(n);
    checkanswer(bn_to_uint64(m),8);
    bn_destroy(n);
    bn_destroy(m);

    checkanswer( ( 0xFFFFFFFF >> 24 ) << 24, 0xFF000000 ); 

    n = bn_from_uint32(4294967295);
    checkanswer( bn_to_uint64(n),4294967295);
    bn_offset_iadd(n,1,0);
    checkanswer( bn_to_uint64(n),4294967296);

    return(0);
}
