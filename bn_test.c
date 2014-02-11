#include <error.h>
#include <inttypes.h>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#include "bn.h"
#include "dar.h"
#include "euler.h"

int main( int argc, char ** argv ) {

    uint32_t x;
    uint32_t y;
    uint64_t z;
    bn_t * m, * n, *p;
    uint32_t r;

    n = bn_new();
    bn_destroy(n);

    n = bn_from_uint32(8);
    checkanswer(n->dar->element_count,1,"32 bit int has an element count of 1");
    dar_fetch(n->dar,&x,0);
    checkanswer(x,8,"correct int value from fetch");
    y = bn_to_uint32(n);
    checkanswer(y,8,"correct int value from uint32 conversion");
    z = bn_to_uint64(n);
    checkanswer(z,8,"correct int value from uint64 conversion");
    bn_destroy(n);

    n = bn_from_uint64(UINT64_MAX) ;
    checkanswer(n->dar->element_count,2,"64 bit int as element count of 2");
    checkanswer(bn_to_uint64(n),UINT64_MAX,"correct 64 bit value from conversion");
    bn_destroy(n);

    n = bn_from_uint32(8);
    m = bn_copy(n);
    checkanswer(bn_to_uint64(m),8,"correct value after copy");
    bn_destroy(n);
    bn_destroy(m);

//    checkanswer( ( 0xFFFFFFFF >> 24 ) << 24, 0xFF000000, "what is the point of this?"); 

    n = bn_from_uint32( 0xffffffffLL );
    checkanswer( bn_to_uint64(n), 0xffffffffLL, "round trip conversion of MAX_UINT");
    bn_iadd(n,1,0);
    checkanswer( bn_to_uint64(n), 0xffffffffLL + 1, "round trip conversion of MAX_UINT + 1");
    bn_destroy(n);

    n = bn_new();
    bn_iadd(n,0x000000FF,0);
    checkanswer(bn_to_uint32(n),0x000000FF,"iadd 0xFF to nothing");
    bn_destroy(n);

    n = bn_from_uint32(0x000000FF);
    bn_clear(n);
    checkanswer( bn_to_uint64(n),0,"bn_clear");
    bn_destroy(n);

    n = bn_from_uint32(0x000000FF);
    m = bn_new();
    bn_add(n,m,0);
    checkanswer(bn_to_uint32(n),0x000000FF,"bn_add 0xFF to nothing");
    bn_destroy(n);
    bn_destroy(m);

    n = bn_from_uint32(0x000000FF);
    m = bn_from_uint32(0x0000FF00);
    bn_add(n,m,0);
    checkanswer(bn_to_uint32(n),0x0000FFFF,"bn_add 0x000000FF + 0x0000FF00");
    bn_destroy(n);
    bn_destroy(m);

    n = bn_from_uint32(0x000000FF);
    m = bn_from_uint32(0x000000FF);
    bn_add(n,m,8);
    checkanswer(bn_to_uint32(n),0x0000FFFF,"bn_add 0x000000FF + 0x000000FF shifted 8 bits");
    bn_destroy(n);
    bn_destroy(m);

    n = bn_from_uint32(0x00000001);
    m = bn_from_uint32(0xFFFFFFFF);
    bn_add(n,m,0);
    checkanswer(bn_to_uint64(n),0x100000000,"bn_add 32 bit overflow");
    bn_destroy(n);
    bn_destroy(m);

    n = bn_scan("123",3);
    checkanswer(bn_to_uint32(n),123,"bn_scan 123");
    bn_destroy(n);

    n = bn_from_uint32(123);
    r = bn_isub(n,123,0);
    checkanswer(r,0,"bn_isub 123 - 123 doesn't underflow");
    checkanswer(bn_to_uint32(n),0,"bn_isub 123 - 123=0");
    bn_destroy(n);

    n = bn_from_uint32(123);
    r = bn_isub(n,124,0);
    checkanswer(r,1,"123-124 underflows");
    bn_destroy(n);

    n = bn_from_uint64(0x100000001);
    r = bn_isub(n,1,32);
    checkanswer(bn_to_uint32(n),1,"0x100000001 - 1 << 32 = 1");
    checkanswer(r,0,"0x100000001 - 1 << 32 doesn't underflow");
    bn_destroy(n);

    n = bn_from_uint32(123);
    m = bn_from_uint32(123);
    r = bn_sub(n,m,0);
    checkanswer(r,0,"bn_sub 123-123 doesn't underflow");
    checkanswer(bn_to_uint32(n),0,"bn_sub 123-123 = 0");
    bn_destroy(n);
    bn_destroy(m);

    n = bn_from_uint64(18446744073709551615ULL);
    m = bn_from_uint64(18446744073709551000ULL);
    r = bn_sub(n,m,0);
    checkanswer(r,0,"bn_sub 64 bit ints don't underflow");
    checkanswer(bn_to_uint32(n),615,"bn_sub small int answer from sub of large ints");
    bn_destroy(n);

    n = bn_from_uint64(0xFFFFFFFF0000);
    m = bn_from_uint64(0xFFFFFFFF);
    r = bn_sub(n,m,16);
    checkanswer(r,0,"bn_sub shifted 64 bit ints don't underflow");
    checkanswer(bn_to_uint32(n),0,"bn_sub shifted 64 bit subtraction = 0");
    bn_destroy(n);
    bn_destroy(m);
    
    n = bn_from_uint32(0xFFFFFFFF);
    m = bn_new();
    bn_imulti(m,n,0xFFFFFFFF);
    p = bn_scan("18446744065119617025",20);
    checkanswer(bn_equal(p,m),1,"0xFFFFFFFF * 0xFFFFFFFF = \"18446744065119617025\"");
    bn_destroy(m);
    bn_destroy(n);
    bn_destroy(p);

    n = bn_from_uint64(0x180000000);
    checkanswer(bn_icmp(n,1,31), 1,"1<<31 <  0x180000000");
    checkanswer(bn_icmp(n,1,32), 1,"1<<32 <  0x180000000");
    checkanswer(bn_icmp(n,1,33),-1,"1<<33 >  0x180000000");
    checkanswer(bn_icmp(n,3,30), 1,"3<<30 <  0x180000000");
    checkanswer(bn_icmp(n,3,31), 0,"3<<31 == 0x180000000");
    checkanswer(bn_icmp(n,3,32),-1,"3<<31 >  0x180000000");
    bn_destroy(n);


    //uint32_t r;

    n = bn_from_uint32(100);
    m = bn_idiv(n,10,&r);
    checkanswer(bn_to_uint32(m),10, "idiv 100 / 10 == 10");
    checkanswer(r,0, "idiv 100 / 10 remainder == 0");
    bn_destroy(m);
    bn_destroy(n);

    n = bn_from_uint32(123456789);
    m = bn_idiv(n,10,&r);
    checkanswer(bn_to_uint32(m),12345678, "idiv 123456789 / 10 == 12345678");
    checkanswer(r,9, "idiv 123456789 / 10 remainder = 9");
    bn_destroy(m);
    bn_destroy(n);

    n = bn_from_uint64(11926328644230);
    m = bn_idiv(n,34534534,&r);
    checkanswer(bn_to_uint32(m),345345, "idiv 11926328644230 / 34534534 = 345345");
    checkanswer(r,0, "idiv 11926328644230 / 34534534 remainder = 0");
    bn_destroy(m);
    bn_destroy(n);

    dar_t * nf;
    dar_t * d ;

    n = bn_scan("9876",4);
    checkanswer(bn_to_uint64(n),9876ULL,"scan of 9876 = 9876");
    nf = bn_format(n);
    d = dar_new_from_bytes(1,"9876",4);
    checkanswer(dar_eq(d,nf),1,"format of 9876 eq 9876");
    bn_destroy(n);
    dar_destroy(nf);
    dar_destroy(d);

    n = bn_scan("987654321",9);
    checkanswer(bn_to_uint64(n),987654321ULL,"scan of 987654321 = 987654321");
    nf = bn_format(n);
    d = dar_new_from_bytes(1,"987654321",9);
    checkanswer(dar_eq(d,nf),1,"format of 987654321 eq 987654321");
    bn_destroy(n);
    dar_destroy(nf);
    dar_destroy(d);

    n = bn_scan("9876543210",10);
    checkanswer(bn_to_uint64(n),9876543210ULL,"scan of max_uint64 = max_uint64");
    nf = bn_format(n);
    d = dar_new_from_bytes(1,"9876543210",10);
    checkanswer(dar_eq(d,nf),1,"format of 9876543210 eq 9876543210");
    bn_destroy(n);
    dar_destroy(nf);
    dar_destroy(d);

    n = bn_scan("18446744073709551615",20);
    checkanswer(bn_to_uint64(n),18446744073709551615ULL,"scan of max_uint64 = max_uint64");
    nf = bn_format(n);
    d = dar_new_from_bytes(1,"18446744073709551615",20);
    checkanswer(dar_eq(d,nf),1,"format of 18446744073709551615 eq 18446744073709551615");
    bn_destroy(n);
    dar_destroy(nf);
    dar_destroy(d);

    n = bn_scan("18446744073709551615",20);
    checkanswer(bn_to_uint64(n),18446744073709551615ULL,"scan of max_uint64 = max_uint64");
    nf = bn_format(n);
    d = dar_new_from_bytes(1,"18446744073709551615",20);
    checkanswer(dar_eq(d,nf),1,"format of 18446744073709551615 eq 18446744073709551615");
    bn_destroy(n);
    dar_destroy(nf);
    dar_destroy(d);

    n = bn_scan("123",3);
    d = dar_new_from_bytes(1,"123",3);
    nf = bn_format(n);
    checkanswer(dar_eq(d,nf),1,"format(scan(\"123\")) == \"123\"");
    bn_destroy(n);
    dar_destroy(d);
    dar_destroy(nf);

    n = bn_scan("37107287533902102798797998220837590246510135740250",50);
    nf = bn_format(n);
    m = bn_scan(nf->data,nf->element_count);
    //dar_t * mf = bn_format(m);
    checkanswer(bn_equal(n,m),1,"scan format scan round trip");

    char * ohf = "93326215443944152681699238856266700490715968264381621468592963895217599993229915608941463976156518286253697920827223758251185210916864000000000000000000000000";
    n = bn_scan(ohf,158);
    nf = bn_format(n);
    //printf("%s\n",(char *)nf->data);
    checkanswer(memcmp(ohf,nf->data,158),0,"scan format of onehundred factorial equals imput string");
    
    return(0);
}
