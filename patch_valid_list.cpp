
#include "RangeMatch.hpp"
RangeMatchSet hs;
RangeMatchSortedSet reciprocals;
int main(int argc, char ** argv) {
    FILE * f0 = fopen(argv[1],"rb");
    FILE * f1 = fopen(argv[2],"rb");    
    FILE * log = fopen(argv[3],"r");
    FILE * f2 = fopen(argv[4],"w+b");    
    
    char data[1024]={0};
    
    if (log&&f0&&f1) {
        while (fgets(data,1023,log)!=NULL) {
            RangeMatch rm;
            if (rm.setRangeMatch(data)) {
                hs.insert(rm);
            }
        }
        fseek(f1,0,SEEK_END);
        long maxSize = ftell(f1);
        char * tmp = new char [maxSize];
        fseek(f1,0,SEEK_SET);
        fread(tmp,1,maxSize,f1);
        fwrite(tmp,1,maxSize,f2);
        for (RangeMatchSet::const_iterator i = hs.begin(),ie=hs.end();i!=ie;++i) {
            fseek(f0,i->min0,SEEK_SET);
            fseek(f2,i->min0,SEEK_SET);
            fread(tmp,i->max0-i->min0,1,f0);
            fwrite(tmp,i->max0-i->min0,1,f2);
            fseek(f0,i->min1,SEEK_SET);
            fseek(f2,i->min1,SEEK_SET);
            fread(tmp,i->max1-i->min1,1,f0);
            fwrite(tmp,i->max1-i->min1,1,f2);
        }
        fclose(f0);
        fclose(f1);
        fclose(log);
        delete [] tmp;
        return 0;
    }else {
        printf ("Files not found %s %s %s\n",argv[1],argv[2], argv[3]);
    }
    return 1;
}
