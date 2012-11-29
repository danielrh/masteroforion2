#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <set>
#include <string>
#include <vector>
std::set<std::string> homeworlds;
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
    Planet() {
        colony=0;
        memset(data,0,NUM_PLANET_DATA);
    }
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
    Star() {
        memset(this,0,sizeof(Star));
        unknownF[16]=255;//marks it as a dead system
        unknownF[17]=255;        
    }
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
                if (false&&planetTable) {
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
Star stars[NUM_STARS];
Planet planets[NUM_PLANETS];

bool isHomeworld(const Star&star) {
    if (homeworlds.find(star.name)!=homeworlds.end()) return true;
    if (star.x==0&&star.y==0)
        return false;
    if (star.owner!=255)
        return true;
    return false;
}

void wipeQuadrant(double minx, double miny, double maxx, double maxy) {
    Star empty;//last star is our empty one?
    empty.x=0;
    empty.y=0;
    memset(empty.name,0,sizeof(empty.name));
    for (int i=0;i<NUM_STARS;++i) {
        if (!isHomeworld(stars[i])) {
            if (stars[i].x>=minx&&stars[i].y>=miny&&
                stars[i].x<=maxx&&stars[i].y<=maxy) {
                stars[i]=empty;
                for (int i=0;i<NUM_PLANETS;++i){
                    if (planets[i].data[PARENT_STAR]==i) {
                        planets[i]=Planet();
                    }
                }
            }
        }
    }
}
std::vector<int>orphanHomeworlds;
int findHomeworld (double minx,double miny,double maxx,double maxy) {
    int retval=-1;
    for (int i=0;i<NUM_STARS;++i) {
        if (isHomeworld(stars[i])) {
            //printf("Potential homeworld located %s at %d %d Is it between (%f %f) - (%f %f)\n",stars[i].name,stars[i].x,stars[i].y,minx,miny,maxx,maxy);
            if (stars[i].x>=minx&&stars[i].y>=miny&&
                stars[i].x<=maxx&&stars[i].y<=maxy) {
                if (retval==-1) {
                    retval = i;
                }else {
                    orphanHomeworlds.push_back(i);
                }
            }
        }        
    }
    return retval;
}
void copyQuadrant(double minx,double miny,double maxx,double maxy,
                  double sourceminx,double sourceminy,double sourcemaxx,double sourcemaxy,bool flipX,bool flipY) {
    //FIXME;
}
int fixupHomeworlds(double minx,double miny,double maxx,double maxy,
                     double homeX, double homeY) {
    int count=0;
    for (int i=0;i<NUM_STARS;++i) {
        if (stars[i].x>=minx&&stars[i].y>=miny&&
            stars[i].x<=maxx&&stars[i].y<=maxy) {
            if (isHomeworld(stars[i])) {
                ++count;
                if (count==1) {
                    stars[i].x=minx+homeX;
                    stars[i].y=miny+homeY;
                }else {
                    orphanHomeworlds.push_back(i);
                }
            }
        }
    }
    if (count==0) {
        if (orphanHomeworlds.size()) {
            int i = orphanHomeworlds.back();
            orphanHomeworlds.pop_back();
            stars[i].x=minx+homeX;
            stars[i].y=miny+homeY;
            ++count;
        }
    }
    return count;
}

int main (int argc, char**argv) {
    homeworlds.insert("Sol");
    homeworlds.insert("Nazin");
    homeworlds.insert("Meklon");
    homeworlds.insert("Altair");
    homeworlds.insert("Ursa");
    homeworlds.insert("Gnol");
    homeworlds.insert("Draconis");
    homeworlds.insert("Kholdan");
    homeworlds.insert("Sssla");
    homeworlds.insert("Mentar");
    homeworlds.insert("Fieras");
    homeworlds.insert("Cryslon");
    homeworlds.insert("Trilar");

    FILE * fp = fopen(argv[1],"rb");
    FILE * output = fopen(argv[2],"r+b");
    
    fseek(fp,0,SEEK_END);
    size_t fileSize = ftell(fp);
    fseek(fp,0,SEEK_SET);    
    byt * data = (byt*)malloc(fileSize);
    fread(data,1,fileSize,fp);
    fclose(fp);

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
    int maxx = -(1<<30);
    int minx = (1<<30);
    int maxy = -(1<<30);
    int miny = (1<<30);
    for (int i=0;i<NUM_STARS;++i) {
        const byt * curData = data+(STAR_OFFSET+i*STAR_SIZE);
        Star starA;

        memcpy(&starA,curData,STAR_SIZE);
//        starA.printStar();
        Star starB;
        starB.readStar(curData);
        if (starB.x!=0||starB.y!=0) {
            if (starB.x<minx) {
                minx = starB.x;
            }
            if (starB.x>maxx) {
                maxx = starB.x;
            }
            if (starB.y<miny) {
                miny = starB.y;
            }
            if (starB.y>maxy) {
                maxy = starB.y;
            }
        }else {
            //invalid system
        }
        
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
    printf("Bounds: (%d,%d) - (%d,%d)\n",minx,miny,maxx,maxy);
    double percent_safe_zone=.03125;
    double wid = maxx-minx;
    double hei = maxy-miny;
    char mode = argv[3][0];
    int slice=argv[3][1]-'0';//q2 is the 2nd quadrant  x5 is the 5th hex zone h0 is the 0th horizontal slice v0 is the 0th vertical slice
    double sourceminx;
    double sourcemaxx;
    double sourceminy;
    double sourcemaxy;
    
    bool flipX=true;
    bool flipY=true;
    int numX=2,numY=2;
    if (mode=='q') {
        numX=2;
        numY=2;
        flipX=true;
        flipY=true;
    }
    if (mode=='h') {
        numX=2;
        numY=1;
        flipX=true;
        flipY=false;

    }
    if (mode=='v') {
        numX=1;
        numY=2;
        flipX=false;
        flipY=true;
    }
    if (mode=='x') {
        numX=3;
        numY=2;
        flipX=false;
        flipY=true;
    }
    {
        std::set<int>homeworldlessQuadrant;
        double homeX, homeY;
        for (int doPlace=0;doPlace<3;++doPlace) {
            int count=0;
            for (int x=0;x<numX;++x) {
                for (int y=0;y<numY;++y) {
                    double lenx = (maxx-minx)/(double)numX;
                    double leny = (maxy-miny)/(double)numY;

                    double localminx=minx+lenx*x;
                    double localminy=miny+leny*y;
                    double localmaxx=numX==1?lenx:lenx-percent_safe_zone;
                    double localmaxy=numY==1?leny:leny-percent_safe_zone;
                    localmaxx+=localminx;
                    localmaxy+=localminy;
                    if (numX>1) {//we shove things over so that we are flush with maxx by the end
                        double del = x*percent_safe_zone/(numX-1);
                        localminx+=del;
                        localmaxx+=del;
                        if (x+1==numX) {
                            localmaxx=maxx;//we don't want a float error here
                        }
                    }
                    if (numY>1) {//we shove things over so we are flush with maxx by the end
                        double del = y*percent_safe_zone/(numY-1);
                        localminy+=del;
                        localmaxy+=del;
                        if (y+1==numY) {
                            localmaxy=maxy;//we don't want a float error here cus we need every last star
                        }
                    }
                    if (!doPlace) {
                        printf("Searching range (%f %f, %f %f)\n",localminx,localminy,localmaxx,localmaxy);
                        if (slice==count) {
                            sourceminx=localminx;
                            sourceminy=localminy;
                            sourcemaxx=localmaxx;
                            sourcemaxy=localmaxy;
                            int homeIndex = findHomeworld (localminx,localminy,localmaxx,localmaxy);
                            if (homeIndex==-1) {
                                printf("Cannot find homeworld in section %d...exiting\n",slice);
                                return -1;
                            }else {
                                Star homeSystem = stars[homeIndex];
                                printf("Homeworld located at %s\n",homeSystem.name);
                                homeX = ((flipX&&x)?localmaxx-homeSystem.x:homeSystem.x-localminx);
                                homeY = ((flipY&&y)?localmaxy-homeSystem.y:homeSystem.y-localminx);
                            }
                        }else {
                            wipeQuadrant(localminx,localminy,localmaxx,localmaxy);
                        }
                    }else {
                        if (slice!=count) {//copy only if the slice isn't the count
                            if(doPlace==1) {
                                copyQuadrant(localminx,localminy,localmaxx,localmaxy,
                                             sourceminx,sourceminy,sourcemaxx,sourcemaxy,flipX,flipY);
                                if (0==fixupHomeworlds(localminx,localminy,localmaxx,localmaxy,
                                                       (flipX&&x)?maxx-homeX:homeY+localminy,(flipY&&y)?maxy-homeY:homeY+localminy)) {
                                    homeworldlessQuadrant.insert(count);
                                }
                            }else if (doPlace==2) {
                                if (homeworldlessQuadrant.find(count)!=homeworldlessQuadrant.end()){
                                    if (0==fixupHomeworlds(localminx,localminy,localmaxx,localmaxy,
                                                           (flipX&&x)?maxx-homeX:homeY+localminy,(flipY&&y)?maxy-homeY:homeY+localminy)) {
                                        printf("Failed on second try to fixup homeworld in quadrant %d\n",count);
                                    }
                                }
                            }
                        }
                    }
                    ++count;
                }
            }
        }
        
    }
    for (int i=0;i<NUM_STARS;++i) {
        stars[i].printStar(planets,stars);
    }
    free(data);
    
}
