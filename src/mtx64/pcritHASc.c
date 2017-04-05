/*    Meataxe-64    pcritHASc.c     */
/*    ==========    =========     */

/*    R. A. Parker      12 July 2015 */

#include <stdio.h>
#include <stdint.h>
#include "field.h"

/* these routines here because they depend on technology */

/* set the "generation" of the hardware  */
/* 0 generic     1 SSE        2 AVX-2    */
void pchal(FIELD * f)
{
    f->pcgen=2;
}

/* choose suitable nor from nob  */
uint64_t pcstride(uint64_t s)
{
    uint64_t i,j,k,d;
    if(s<600) return 200;    // fits in L2 in its entirety
    for(i=1;i<25;i++)        // how many L1 banks can we use
    {
        d=s*i;
        if( ((d+7)&4095)<15) break;
    }
    for(j=1;j<50;j++)        // how many L2 banks can we use
    {
        d=s*j;
        if( ((d+15)&65535)<31) break;
    }
    k=8*i;
    if(k<(4*j)) k=4*j;
    return k;
}

/* end of pcritHASc.c  */
