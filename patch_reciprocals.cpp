
#include "RangeMatch.hpp"
RangeMatchSet hs;
RangeMatchSortedSet reciprocals;
int main(int argc, char ** argv) {
    
    FILE * log = fopen(argv[1],"r");
    char data[1024]={0};
    if (log) {
        while (fgets(data,1023,log)!=NULL) {
            RangeMatch rm;
            if (rm.setRangeMatch(data)) {
                hs.insert(rm);
            }
        }
        for (RangeMatchSet::const_iterator i = hs.begin(),ie=hs.end();i!=ie;++i) {
            if (hs.find(i->reciprocal())!=ie) {
                reciprocals.insert(*i);
            }
        }
        for (RangeMatchSortedSet::const_iterator i=reciprocals.begin(),ie=reciprocals.end();i!=ie;++i) {
            if (i->min1>=i->min0)
                printf ("Valid range [%lx, %lx) :: [%lx, %lx) non zero: %ld size: %ld\n",i->min0,i->max0,i->min1,i->max1,i->nonzero,i->max1-i->min1);
        }
        return 0;
    }else {
        printf ("Files not found %s\n",argv[1]);
    }
    return 1;
}
