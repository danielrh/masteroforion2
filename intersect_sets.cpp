
#include "RangeMatch.hpp"
RangeMatchSet *hs;
bool *invert;
RangeMatchSortedSet final;
int main(int argc, char ** argv) {
    hs = new RangeMatchSet[argc-1];    
    invert = new bool[argc-1];
    for (int j=1;j<argc;++j) {
        FILE * log;
        if (argv[j][0]=='-') {
            invert[j-1]=true;
            log = fopen(argv[j]+1,"r");
        }else {
            log = fopen(argv[j],"r");
            invert[j-1]=false;            
        }

        char data[1024]={0};
        if (log) {
            while (fgets(data,1023,log)!=NULL) {
                RangeMatch rm;
                if (rm.setRangeMatch(data)) {
                    hs[j-1].insert(rm);
                }
            }
        }else {
            printf ("404'd: %s\n",argv[j]);
        }
    }
    for (RangeMatchSet::const_iterator i = hs[0].begin(),ie=hs[0].end();i!=ie;++i) {
        bool valid=true;
        for (int j=0;j+1<argc;++j) {
            if (hs[j].find(*i)==hs[j].end()) {
                if (!invert[j]) {
                    valid=false;
                    break;
                }
            }else {
                if (invert[j]) {
                    valid=false;
                    break;
                }                
            }
        }
        if (valid) {
            final.insert(*i);
        }
    }
    for (RangeMatchSortedSet::const_iterator i=final.begin(),ie=final.end();i!=ie;++i) {
        if (!i->selfOverlap())
            printf ("Valid range [%lx, %lx) :: [%lx, %lx) non zero: %ld size: %ld\n",i->min0,i->max0,i->min1,i->max1,i->nonzero,i->max1-i->min1);
    }
    return 0;
}
