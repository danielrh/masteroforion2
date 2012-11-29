#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef unsigned char byt;

const char *environments[]={"toxic","radiated","barren","desert","tundra","ocean","swamp","arid","terran","gaia"};
const char* planetdata[]={
    "STAR",
    "ORBIT",
    "TYPE",
    "SIZE",//0 = tiny 4=huge
    "G",//1 = normal
    "UNKNOWNA",
    "ENVIRONMENT",//index into environments
    "BACKGROUND",//0-5 image
    "MINERALS",//0 = ultra poor 4 = ultra rich
    "FOODBASE",
    "TERRAFORMINGS",
    "MODSIZE",//2 = tiny 4 = small 5 = med 7 = large 0xa = huge
    "UNKNOWNB",
    "SPECIAL",//0 = none
    "FLAGS"//2 = soil
        };
enum PLANET_DATA{
    PARENT_STAR,
    ORBIT,
    TYPE,
    SIZE,//0 = tiny 4=huge
    G,//1 = normal
    UNKNOWNA,
    ENVIRONMENT,//index into environments
    BACKGROUND,//0-5 image
    MINERALS,//0 = ultra poor 4 = ultra rich
    FOODBASE,
    TERRAFORMINGS,
    MODSIZE,//2 = tiny 4 = small 5 = med 7 = large 0xa = huge
    UNKNOWNB,
    SPECIAL,//0 = none
    FLAGS,//2 = soil
    NUM_PLANET_DATA
};
#define PLANET_SIZE (NUM_PLANET_DATA+2)
class Star;
class Planet {
public:
#pragma pack(1)
    short colony;//-1 = uncolonized
    byt data[NUM_PLANET_DATA];
    void printPlanet(Star* starTable);
    void readPlanet(const byt *dat) {
        if (dat[1]==0xff&&dat[0]==0xff) {
            colony=-1;
        }else {
            colony=dat[1];
            colony*=0x100;
            colony|=dat[0];
        }
        dat+=0x2;            
        memcpy(data,dat,NUM_PLANET_DATA);
    }
    void writePlanet(byt * dat) {
        if (colony==-1) {
            dat[0]=0xff;
            dat[1]=0xff;
        }else{
            dat[0]=(byt)(colony&0xff);
            dat[1]=(byt)((colony/0x100)&0xff);
        }
        dat+=0x2;
        memcpy(dat,data,NUM_PLANET_DATA);
    }
    
};
class Star {
public:
#pragma pack(1)
    char name[0xf];
    short x;
    short y;
    byt size;
    byt owner;//0xff = unowned
    byt unknownA;
    byt starType;
    byt unknownB[0x11];
    byt special;
    byt wormhole;//0xff no wormhole
    byt unknownC[0xf];
    byt interdictor;
    byt unknownD[0x5];
    byt artemis;//0x0 no artemis otherwise player+1
    byt unknownE[0xa];
    short planets[5];///-1 = none;
    byt unknownF[0x1d];
    bool operator==(const Star&oth) const{
        if (x!=oth.x) {
            return false;
        }
        if (y!=oth.y) {
            return false;
        }
        if (size!=oth.size) {
            return false;
        }
        if (owner!=oth.owner) {
            return false;
        }
        if (unknownA!=oth.unknownA) {
            return false;
        }
        if (starType!=oth.starType) {
            return false;
        }
        if (memcmp(unknownB,oth.unknownB,0x11)) {
            return false;
        }
        if (special!=oth.special) {
            return false;
        }
        if (artemis!=oth.artemis) {
            return false;
        }
        if (memcmp(unknownC,oth.unknownC,0xf)) {
            return false;
        }
        if (interdictor!=oth.interdictor) {
            return false;
        }
        
        if (memcmp(unknownD,oth.unknownD,0x5)) {
            return false;
        }
        if (memcmp(unknownE,oth.unknownE,0xa)) {
            return false;
        }
        if (memcmp(unknownF,oth.unknownF,0x1d)) {
            return false;
        }
        for (int i=0;i<5;++i) {
            if (planets[i]!=oth.planets[i]) {
                return false;
            }
        }
        return true;
    }
    void readStar(const byt *data) {
        memcpy(name,data,0xf);
        data+=0xf;
        x=data[1];
        x*=0x100;
        x|=data[0];
        data+=0x2;
        y=data[1];
        y*=0x100;
        y|=data[0];
        data+=0x2;
        size=data[0];
        data++;
        owner=data[0];
        data++;
        unknownA=data[0];
        data++;
        starType = data[0];
        data++;
        memcpy(unknownB,data,0x11);
        data+=0x11;
        special=data[0];
        data++;
        wormhole=data[0];
        data++;
        memcpy(unknownC,data,0xf);
        data+=0xf;
        interdictor=data[0];
        data++;
        memcpy(unknownD,data,0x5);
        data+=0x5;
        artemis=data[0];
        data++;
        memcpy(unknownE,data,0xa);
        data+=0xa;        
        for (int i=0;i<5;++i) {
            if (data[1]==0xff&&data[0]==0xff) {
                planets[i]=-1;
            }else {
                planets[i]=data[1];
                planets[i]*=0x100;
                planets[i]|=data[0];
            }
            data+=0x2;            
        }
        memcpy(unknownF,data,0x1d);
        data+=0x1d;        

    }
    //needs to have 71 bytes free to write out the star
    void writeStar(byt *data){
        memcpy(data,name,0xf);
        data+=0xf;
        data[0]=(byt)(x&0xff);
        data[1]=(byt)((x/0x100)&0xff);
        data+=0x2;
        data[0]=(byt)(y&0xff);
        data[1]=(byt)((y/0x100)&0xff);
        data+=0x2;        
        data[0]=size;
        data++;
        data[0]=owner;
        data++;
        data[0]=unknownA;
        data++;
        data[0]=starType;
        data++;
        memcpy(data,unknownB,0x11);
        data+=0x11;
        data[0]=special;
        data++;
        data[0]=wormhole;
        data++;
        memcpy(data,unknownC,0xf);
        data+=0xf;
        data[0]=interdictor;
        data++;
        memcpy(data,unknownD,0x5);
        data+=0x5;
        data[0]=artemis;
        data++;
        memcpy(data,unknownE,0xa);
        data+=0xa;  
        for (int i=0;i<5;++i) {
            if (planets[i]==-1) {
                data[0]=0xff;
                data[1]=0xff;
            }else{
                data[0]=(byt)(planets[i]&0xff);
                data[1]=(byt)((planets[i]/0x100)&0xff);
            }
            data+=0x2;            
        }
        
        memcpy(data,unknownF,0x1d);
        data+=0x1d;        
    }    
    void printStar(Planet*planetTable, Star*starTable) {
        printf("%s (%d, %d) owner:%d\n",name,x,y,owner);
        printf("[[[\n");
        for (int i=0;i<5;++i) {
            if (planets[i]!=-1) {
                printf("planet[%d]: %d\n",i,planets[i]);
                if (planetTable) {
                    planetTable[planets[i]].printPlanet(starTable);
                }else {
                    
                }
            }
        }
        printf("]]]\n");
    }
};//size = 0x71
void Planet::printPlanet(Star* starTable) {
    printf("Owned by %d\n",colony);
    for (int i=0;i<NUM_PLANET_DATA;++i) {
        if (i==PARENT_STAR&&starTable) {
            printf ("Parent System: %s\n",starTable[data[i]].name);
        }else{
            printf ("%s: %d\n",planetdata[i],data[i]);
        }
    }
}

#define STAR_OFFSET 0x17ad3//offset to star table
#define STAR_SIZE 0x71
#define PLANET_OFFSET 0x162E9
#define NUM_STARS 72
#define NUM_PLANETS 108
int main (int argc, char**argv) {

    FILE * fp = fopen(argv[1],"rb");
    fseek(fp,0,SEEK_END);
    size_t fileSize = ftell(fp);
    fseek(fp,0,SEEK_SET);    
    byt * data = (byt*)malloc(fileSize);
    fread(data,1,fileSize,fp);
    fclose(fp);
    Planet planets[NUM_PLANETS];
    for (int i=0;i<NUM_PLANETS;++i) {
        const byt * curData = data+(PLANET_OFFSET+i*PLANET_SIZE);
        Planet planetA;
        memcpy(&planetA,curData,PLANET_SIZE);
        Planet planetB;
        planetB.readPlanet(curData);
        //planetB.printPlanet(NULL);
        if (memcmp(&planetA,&planetB,PLANET_SIZE)) {
            printf("Endianness Mismatch: luckily we coded for that\n");
        }
        byt testIdempotency[PLANET_SIZE];
        planetB.writePlanet(testIdempotency);
        planetA.readPlanet(testIdempotency);
        if (memcmp(&planetA,&planetB,PLANET_SIZE)) {
            printf("Idempotency Mismatch: FAIL\n");
        }
        if (memcmp(testIdempotency,curData,PLANET_SIZE)) {
            printf("Idempotency Mismatch: FAIL Internal\n");
        }
        planets[i]=planetB;
    }
    Star stars[NUM_STARS];
    for (int i=0;i<NUM_STARS;++i) {
        const byt * curData = data+(STAR_OFFSET+i*STAR_SIZE);
        Star starA;

        memcpy(&starA,curData,STAR_SIZE);
//        starA.printStar();
        Star starB;
        starB.readStar(curData);
        stars[i]=starB;
        if (memcmp(&starA,&starB,STAR_SIZE)) {
            printf("Endianness Mismatch: luckily we coded for that\n");
        }
        byt testIdempotency[STAR_SIZE];
        starB.writeStar(testIdempotency);
        starA.readStar(testIdempotency);
        if (memcmp(&starA,&starB,STAR_SIZE)) {
            printf("Idempotency Mismatch: FAIL\n");
            if (!(starA==starB)) {
                printf("Idempotency Mismatch: FAIL B\n");
            }
        }
        if (memcmp(testIdempotency,curData,STAR_SIZE)) {
            printf("Idempotency Mismatch: FAIL Internal\n");
        }
    }
    for (int i=0;i<NUM_STARS;++i) {
        stars[i].printStar(planets,stars);
    }
    free(data);
    
}
