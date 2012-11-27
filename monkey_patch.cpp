#include <stdio.h>

int main (int argc, char**argv) {
    FILE * f0 = fopen(argv[1],"rb");
    FILE * f1 = fopen(argv[2],"rb");
    FILE * f2 = fopen(argv[3],"w+b");
    long offset0=0,offset1=0;
    long offset0end=0,offset1end=0;
    sscanf(argv[4],"%lx",&offset0);
    sscanf(argv[5],"%lx",&offset0end);
    offset1=offset0;
    offset1end=offset0end;
    if (argc>7) {
        sscanf(argv[6],"%lx",&offset1);
        sscanf(argv[7],"%lx",&offset1end);
    }
    if (offset0end-offset0!=offset1end-offset1) {
        printf ("Failure %lx != %lx\n",offset0end-offset0,offset1end-offset1);
        return 1;
    }
    if (f1&&f2) {
        fseek(f1,0,SEEK_END);
        size_t dataLen = ftell(f1);
        fseek(f1,0,SEEK_SET);
        unsigned char * fullData = new unsigned char [dataLen];
        fread(fullData,1,dataLen,f1);
        fwrite(fullData,1,dataLen,f2);
        fclose(f1);
    }
    if (f0&&f2) {
        fseek(f0,offset0,SEEK_SET);
        fseek(f2,offset1,SEEK_SET);
        unsigned char * data = new unsigned char [offset0end-offset0];
        fread(data,1,offset0end-offset0,f0);
        fwrite(data,1,offset1end-offset1,f2);
        fclose(f2);
        fclose(f0);
        delete [] data;
        printf ("Copied [%06lx, %06lx) :: [%06lx, %06lx)\n",offset0,offset0end,offset1,offset1end);
    }else {
        printf("404d");
    }
    return 0;
}
