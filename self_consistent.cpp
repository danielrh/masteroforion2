#include <stdio.h>
#include <math.h>
#include <tr1/unordered_set>
int main (int argc, char**argv) {
    FILE * f0 = fopen(argv[1],"rb");
    FILE * f1 = fopen(argv[2],"rb");
    long offset0=0,offset1=0;
    //sscanf(argv[3],"%lx",&offset0);
    //sscanf(argv[4],"%lx",&offset1);
    
    if (f0&&f1) {
        fseek(f0,0,SEEK_END);
        fseek(f1,0,SEEK_END);
        size_t e0 = ftell(f0);
        size_t e1 = ftell(f1);
        fseek(f0,0,SEEK_SET);
        fseek(f1,0,SEEK_SET);
        unsigned char * data0 = new unsigned char[e0];
        unsigned char * data1 = new unsigned char[e1];
        long read0 = fread(data0,1,e0,f0);
        long read1 = fread(data1,1,e1,f1);
        if (read0!=e0||read1!=e1) {
            printf("Read error\n");
            return 1;
        }
        fclose(f0);        
        fclose(f1);        
        size_t minSize = 64;
        size_t minNonZero=10;
        double lastPct=0;
        std::tr1::unordered_set<unsigned long long> hs;
        for (offset0=0;offset0<e0-minSize;++offset0) {
            double pct = 1000*(offset0/(double)e0);
            if (floor(pct)!=lastPct) {
                lastPct = floor(pct);
                printf("%f percent complete\n",lastPct/10);
                fflush(stdout);
            }
            for (offset1=minSize;offset1<e1-minSize;++offset1) {            
                if (offset1==offset0)continue;
                size_t minValid0=offset0;
                size_t minValid1=offset1;
                size_t maxValid0=offset0;
                size_t maxValid1=offset1;//non inclusive
                int nonZero=0;
                for (size_t i=offset0,j=offset1;;--i,--j) {
                    unsigned char c = data0[i];
                    if (c==data1[j]) {
                        minValid0=i;
                        minValid1=j;
                        if (c&&c!=255) nonZero++;
                    }else break;
                    if (i==0) break;
                }
                for (size_t i=offset0,j=offset1;i<e0&&j<e1;++j,++i) {
                    unsigned char c = data0[i];
                    if (c==data1[j]) {
                        if (c&&c!=255) nonZero++;
                        maxValid0=i+1;
                        maxValid1=j+1;
                    }else break;
                }
                if (nonZero>minNonZero&&maxValid0-minValid0>minSize) { 
                    unsigned long long key = minValid0;
                    key*=65536;
                    key*=65536;
                    key+=minValid1;
                    if (hs.find(key)==hs.end()) {
                        hs.insert(key);
                        printf ("Valid range [%06lx, %06lx) :: [%06lx, %06lx) non zero: %d size: %ld\n",minValid0,maxValid0,minValid1,maxValid1,nonZero,maxValid0-minValid0);
                    }
                }
            }
        }
        delete[]data0;
        delete[]data1;
    }else {
        printf("404d");
    }
    return 0;
}
