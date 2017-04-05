/*
      zmn.c     meataxe-64 make null-space
      =====     R. A. Parker    27.11.2016
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "field.h"
#include "io.h"
#include "bitstring.h"
 
int main(int argc,  char **argv)
{
    EFIL *e1,*e2,*e3;
    uint64_t hdr1[5],hdr2[5];
    uint64_t nor,noc,noc1,noc2,fdef;
    FIELD * f;
    DSPACE ds,ds1,ds2;    // output generated input
    Dfmt *v,*v1,*v2;      // output generated input
    uint64_t i,siz;
    uint64_t * bs;

    LogCmd(argc,argv);
/******  First check the number of input arguments  */
    if (argc != 4)
    {
        LogString(80,"usage zmn bs rm ns");
        exit(21);
    }
    e1=ERHdr(argv[1],hdr1);    // bitstring 2 1 bits setb 0
    e2=ERHdr(argv[2],hdr2);    // remnant 1 fdef nor noc 0
    nor=hdr2[2];      // rows in
    noc=hdr1[2];      // bits = output cols
    noc2=hdr2[3];     // input cols
    noc1=noc-noc2;    // generated cols
    if( (noc2!=hdr1[3]) || (nor!=noc1) )
    {
        LogString(80,"Inputs incompatible");
        exit(22);
    }
    fdef=hdr2[1];
    f = malloc(FIELDLEN);
    FieldSet(fdef,f);
    hdr2[3]=noc;
    e3 = EWHdr(argv[3],hdr2);

    DSSet(f,noc,&ds);     // output
    DSSet(f,noc1,&ds1);   // generated
    DSSet(f,noc2,&ds2);   // input

    v=malloc(ds.nob);     // output
    v1=malloc(ds1.nob);   // generated
    v2=malloc(ds2.nob);   // input

// read the bit string
    siz = 8*(2+(noc+63)/64);
    bs=malloc(siz);
    ERData(e1,siz,(uint8_t *)bs);

/******  Do them one row at a time  */
// later perhaps do a few rows at a time
    for(i=0;i<nor;i++)
    {
	ERData(e2,ds2.nob,v2);
        memset(v1,0,ds1.nob);
        DPak(&ds1,i,v1,1);
        BSColRiffle(f,bs,1,v2,v1,v);
        EWData(e3,ds.nob,v);
    }
    free(v);
    free(v1);
    free(v2);
    free(f);
    ERClose(e1);
    ERClose(e2);
    EWClose(e3);

    return 0;
}

/******  end of zmn.c    ******/
