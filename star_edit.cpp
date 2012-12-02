/*********************************************
 * CopyrigCopyright (c) 2012, The Tree House
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
 *
 * - Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
 * - Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 ************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <set>
#include <string>
#include <vector>
#include <map>
#include <math.h>
const char * possibleNames[]={"Rhodos","Delphi","Horta","Cassandra","Sethlans","Ismareos","Diomedes","Thrace","Pontus","Thesseus","Nortia","Stymphalus","Thebes","Hecaton","Arachne","Pactolus","Eretria","Hera","Leon","Euphrosyne","Augeas","Zephir","Eurus","Mummu","Ajax","Scyros","Icarus","Hehet","Dionysus","Ammon","Lerna","Neith","Postverta","Nekhbet","Thelxepia","Coeus","Astarte","Alcmene","Sphinx","Nepthys","Kingu","Iphicles","Sparta","Iapetus","Clytaemnestra","Kalkal","Alcestis","Iris","Tartarus","Bel","LotosAni","Calypso","Aglaia","Vladimir","Geb","Argos","Samos","Aegeus","Aplu","Apollo","Ninhursaga","Sobek","Antu","Imhotep","Khepry","Khnum","Vertumus","Paros","Perseus","Aeolus","Nabu","Clio","Marduk","Apsu","Inanna","Laius","Turan","Mammetum","Epimetheus","ZaltuAmaunet","Aton","Aia","Telamon","Ea","Bes","Polyhymnia","Charun","Shara","Union","Metope","Nin ildu","Hesione","Delos","Peisinoe","Thracia","Hades","Callen","Tenedos","Tyndareus","Peleus","Hecuba","Nemesis","Belet ili","Nammu","Nintu","Hestia","Laocoon","Atropos","Nemea","Clotho","Chalcis","Gibil","Aglaophonos","Sekhmet","Keket","Crete","Mut","Thalia","Tethys","Enki","Patroclus","Hecate","Enurta","Osiris","Tinia","Erebus","Amun","Enlil","Nin agal ","Ptah","Papsukkal ","Karl","Ishtar","Cetus","Sin","Minotaur","Seth","Cepheus","Maat","Molpe","Pandora","Isis","Olympia","Athena","Jocasta","Neoptolemos","Ninurta","Nanna","Lachesis","Hydra","Hathor","Hanish","Aruru","Selvans","Laomedon","Naxos","Anu","Soviet","Eris","Artemis","Megara","Thasos","Penthesilea","Calchas","Morpheus","Ennead","Iphigenia","Utu","ThothAether","Aphrodite","Choephori","Moscow","Euripides","Maia","Laran","Deidameia","Engels","Mount Ida","Hephaestus","Lykia","Heracleidae","Februus","Anuket","Apis","Oceanus","Nusku","Archimedes","Cautha","Nereid","Cronus","Leto","Serapis","Tiamat","Culsu","Plataea","Charontes","Andromeda","Erymanthia","Nethuns","Rhesus","Persephone","Phobe","Nike","Hippolyta","Theseus","Qingu","Nut","Hebe","Deadulus","Ellil","Atum","Calliope","Andromache","Agamemnon","Athens","Mami","Lycus","Berkeley","Hellespont","Siduri","Nemaea","Hypnos","Silenus","Ra","Kek","Asclepius","Enceladus","Trotsky","Khonsu","Midas","Meresger","Gerra","Lenin","Urania","Bastet","Feronia","Heh","Euterpe","Theba","Anshar","Nash","Erato","Melpomene","Argolida","Phrygia","Chios","Poseidon","Hyperion","Ninsun","Eros","Eos","Hercules","Terpischore","Apep","Myrmidon","Ishum","Thesan","Pyrrhus","Helene","Alexandros","Hesiod","Erinyes","Rhea","Ares","Mullitu","Lahmu","Anubis","Atlas","Menelaus","Thetis","Horus","Voltumna","Janus","Chryseis","Ashur","Cerynea","Cyclope","Friedrich","Pasiphae","Hespera ","Athos","Nimnah","Boreas","Red","Shamash","Aeschylus","Summanus","Hygeia","Anat","Ninlil","Naunet","Kakka","Oedipus","Fama","Notus","Kishar","Olympus","Leningrad","Dumkina","Zeus","Shu","Klytamnestra","Mors","Hermes","Gaea","Philoctetes","Antaios","Priam","Shullat","Sophocles","Min","Gushkin banda","Marx","Lahamu","Adad","Demeter"};
std::vector<std::string> starNames;
std::set<std::string> validNames;
std::set<std::string> homeworlds;
std::set<int> orphanStars;
#define MAX_NUM_PLANETS 192
int NUM_PLANETS=MAX_NUM_PLANETS;
typedef unsigned char byt;

std::map<std::string,int> hist[0x1f];
void histogram (const unsigned char *data, size_t size) {
    std::string dat ((const char*)data,size);
    if (hist[size].find(dat)!=hist[size].end()) {
        hist[size][dat]++;
    }else {
        hist[size][dat]=1;
    }
}
char nibbleToHex(unsigned char b) {
    if (b>=10) return (b-10)+'a';
    return b+'0';
}
void printHist() {
    for (int i=0;i<sizeof(hist)/sizeof(hist[0]);++i) {
        if (!hist[i].empty()) {
            printf("Histogram for %d\n",i);
            for (std::map<std::string,int>::iterator j=hist[i].begin(),je=hist[i].end();j!=je;++j) {
                std::string s = j->first;
                std::string hexS;
                for (std::string::iterator si=s.begin(),sie=s.end();si!=sie;++si) {
                    char byt = *si;
                    unsigned char b = byt;
                    
                    hexS+=nibbleToHex(b/16);
                    hexS+=nibbleToHex(b&15);
                    
                }
                printf ("%s : %d\n",hexS.c_str(),j->second);
            }
        }
    }
}
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
    PLANETSIZECLASS,//0 = tiny 4=huge
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
    bool isEmpty() const{
        Planet p;
        return memcmp(this,&p,sizeof(Planet))==0;
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
    bool isEmpty() const{
        Star empty;
        return memcmp(this,&empty,sizeof(Star))==0;
    }
    bool within (double minx,double miny,double maxx,double maxy)const {
        return (x>=minx&&y>=miny&&x<=maxx&&y<=maxy);
    }
    void recordHist() const{
        histogram(&unknownA,1);
        histogram(unknownB,sizeof(unknownB));
        histogram(unknownC,sizeof(unknownC));
        histogram(unknownD,sizeof(unknownD));
        histogram(unknownE,sizeof(unknownE));
        histogram(unknownF,sizeof(unknownF));

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
        if (validNames.find(name)==validNames.end()) {
            if (strlen(name)>2)
                validNames.insert(name);
        }
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
        data[1]=(byt)((((unsigned short)x)/0x100)&0xff);
        data+=0x2;
        data[0]=(byt)(y&0xff);
        data[1]=(byt)((((unsigned short)y)/0x100)&0xff);
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
        if (this->isEmpty()) {
            printf("Empty system\n");
            return;
        }
        printf("%s (%d, %d) owner:%d\n",name,x,y,owner);
        printf("[[[\n");
        for (int i=0;i<5;++i) {
            if (planets[i]!=-1&&planets[i]<NUM_PLANETS) {
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
#define MAX_NUM_STARS 71
int NUM_STARS=MAX_NUM_STARS;
int NUM_PLAYERS=8;

bool isHomeworld(const Star&star, Planet planets[]) {
    if (star.x==0&&star.y==0)
        return false;
    bool retval=false;
    for (int i=0;i<5;++i) {
        if (star.planets[i]==-1) {
            if (planets[star.planets[i]].colony!=-1) {
                //printf("Primary method for identifying %s as homeworld %d\n",star.name,planets[star.planets[i]].colony);
                //return true;
                //everything seems to be zero on turn 0
            }
        }
    }
    
    if (star.owner!=255) {
        retval = true;
    }
    if (homeworlds.find(star.name)!=homeworlds.end()) {
        retval = true;
    }
    if (retval) {//clear us from a valid name
        if (validNames.find(star.name)!=validNames.end()) {
            validNames.erase(star.name);
        }
    }
    return retval;
}
void wipeStars(Star stars[], Planet planets[]) {

    for (int i=0;i<NUM_STARS;++i) {
        if (!isHomeworld(stars[i],planets)) {
            stars[i]=Star();
        }
    }
}
void wipePlanets(Star stars[], Planet planets[]) {
    for (int i=0;i<NUM_PLANETS;++i) {
        int parent = planets[i].data[PARENT_STAR];
        if (parent!=-1) {
            if (!isHomeworld(stars[parent],planets)) {
                planets[i] = Planet();
            }
        }
    }
    int count=0;
    for (int i=0;i<NUM_PLANETS;++i) {
        if (planets[i].isEmpty()) count++;
    }
    printf("Empty Planet Slots %d/%d\n",count,NUM_PLANETS);
}
void wipeQuadrant(Star stars[],Planet planets[],double minx, double miny, double maxx, double maxy) {
    Star empty;//last star is our empty one?
    empty.x=0;
    empty.y=0;
    memset(empty.name,0,sizeof(empty.name));
    for (int i=0;i<NUM_STARS;++i) {
        if (!isHomeworld(stars[i],planets)) {
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
int findHomeworld (Star stars[], Planet planets[], double minx,double miny,double maxx,double maxy) {
    int retval=-1;
    for (int i=0;i<NUM_STARS;++i) {
        if (isHomeworld(stars[i],planets)) {
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
int nextFreeStar(Star destStars[], Planet destPlanets[], int curFree) {
    while (isHomeworld(destStars[curFree],destPlanets)) {
        curFree++;
    }
    if (curFree<NUM_STARS)
        return curFree;
    else return -1;
}
Star& crossMapStarCopy(Star&dst, const Star&src) {
    size_t starNameIndex = rand()%starNames.size();
    std::string curName = starNames[starNameIndex];
    starNames[starNameIndex]=starNames.back();
    starNames.pop_back();
    if (starNames.empty()) {
        printf("Falling back to builtin names\n");
        for (int i=0;i<sizeof(possibleNames)/sizeof(char*);++i) {
            starNames.push_back(possibleNames[i]);//fall back to builtin names
        }
    }
    strncpy(dst.name,curName.c_str(),0xf);
    dst.name[0xe]='\0';//zero terminate
    dst.special=src.special;
    return dst;
}
void copyQuadrantStars(
    Star destStars[], Planet destPlanets[],double minx,double miny,double maxx,double maxy,
    Star stars[], Planet planets[], double sourceminx,double sourceminy,double sourcemaxx,double sourcemaxy,bool flipX,bool flipY, int whichSlice, std::map<int,int> &starMap, std::vector<int> &freePlanets, int &freeStar) {
    freeStar = nextFreeStar(destStars,destPlanets,freeStar);//in case we're at a homeworld
    int sectorCount=1;//for the homeworld.
    for (int i=0;i<NUM_STARS;++i) {
        if (stars[i].x>=sourceminx&&
            stars[i].x<=sourcemaxx&&
            stars[i].y>=sourceminy&&
            stars[i].y<=sourcemaxy&&
            !isHomeworld(stars[i],planets)) {

            //fixup x and y coordinates
            int delx = stars[i].x-sourceminx;

            int dely = stars[i].y-sourceminy;

            if (!((sectorCount*NUM_PLAYERS)+whichSlice<NUM_STARS)) {
                printf("Extra star %d (total of %d) detected beyond remainder\n",sectorCount,freeStar);
                continue;//forget about stars that are too much
            }
            if (freeStar==-1) {
                printf ("Failure to find available star index after for count %d: quadrant too dense\n",sectorCount);
                return;
            }
            bool orphan=false;
            if (((sectorCount+1)*NUM_PLAYERS)>NUM_STARS) {//we're the orphans in the middle
                orphan=true;
                delx = sourcemaxx-sourceminx;
                dely = sourcemaxy-sourceminy;
                int varX = (sourcemaxx-sourceminx)/16;
                int varY = (sourcemaxy-sourceminy)/16;
                int randomX = rand()%varX-varX/2;//7% variability
                int randomY = rand()%varY-varY/2;
                delx += randomX;
                dely += randomY;
                printf("Making random star in the middle\n");
            }
            ++sectorCount;
            starMap[freeStar]=i;
            crossMapStarCopy(destStars[freeStar],stars[i]);
            if (orphan) {
                printf("Orphan %s\n",destStars[freeStar].name);
            }
            destStars[freeStar].x=delx+minx;
            destStars[freeStar].y=dely+miny;
            if (flipX&&sourceminx!=minx) {//only flip if we're on the opposite side
                destStars[freeStar].x=maxx-delx;
            }
            if (flipY&&sourceminy!=miny) {//only flip if we're on the opposite side
                int dely = stars[i].y-sourceminy;
                destStars[freeStar].y=maxy-dely;
            }
            //fixup planets
            int numPlanetsNeeded = 0;
            for (int j=0;j<5;++j) {
                if (stars[i].planets[j]!=-1&&stars[i].planets[j]<NUM_PLANETS) {//otherwise we have it covered because the gets operator should do it fine
                    ++numPlanetsNeeded;
                }
            }
            if (orphan)
                orphanStars.insert(freeStar);
            
            for (int j=0;j<5;++j) {
                if (destStars[freeStar].planets[j]!=-1&&stars[i].planets[j]<NUM_PLANETS) {//otherwise we have it covered because the gets operator should do it fine
                    --numPlanetsNeeded;
                    if (numPlanetsNeeded<0) {
                        if (destPlanets[destStars[freeStar].planets[j]].data[PARENT_STAR]==freeStar) {
                            freePlanets.push_back(destStars[freeStar].planets[j]);
                            destStars[freeStar].planets[j]=-1;
                        }else {
                            if (destStars[freeStar].planets[j]!=0) {
                                printf("Strange planet that doesn't reference parent in source save\n");
                            }
                        }

                    }
                }
            }
            freeStar++;
            int oldFreeStar = freeStar;
            freeStar = nextFreeStar(destStars,destPlanets,freeStar);//in case we'r4e at a homeworld
        }
    }
}
bool fixupHomeworlds(Star stars[], Planet planets[], double minx,double miny,double maxx,double maxy,
                    double homeX, double homeY, int whichHomeworld) {
    int count=0;
    for (int i=0;i<NUM_STARS;++i) {
        if (isHomeworld(stars[i],planets)) {
            if (count++==whichHomeworld) {
                stars[i].x=homeX;
                stars[i].y=homeY;                
                bool foundHuge=false;
                for (int j=0;j<5;++j) {
                    int planetIdx = stars[i].planets[j];
                    if (planetIdx!=-1&&planetIdx<NUM_PLANETS) {
                        if (planets[planetIdx].data[PLANETSIZECLASS]==4&&foundHuge==false) {//we know players cannot select huge planets in the race pix
                            foundHuge=true;
                            planets[planetIdx].data[MINERALS]=2;//set huge planets to abundant for sure since they aren't home planets
                            planets[planetIdx].data[ENVIRONMENT]=2;//set huge planets to barren
                            
                            
                        }else if (planets[planetIdx].data[TYPE]==3&&
                                  (planets[planetIdx].data[ENVIRONMENT]!=5&&
                                   planets[planetIdx].data[ENVIRONMENT]!=8)) {
                            planets[planetIdx].data[TYPE]=2;
                        }
                    }
                }
                return true;
            }
        }
    }
    return false;
}
void nerf(Star stars[], Planet planets[]) {
    for (int i=0;i<NUM_STARS;++i) {
        Star&star=stars[i];
        if (!isHomeworld(star,planets)) {
            if (star.special==0xb||star.special==0xa||star.special==0x8||star.special==0x7||star.special==0x6) {
                star.special=(rand()%2+2);//turn natives,splinter,hero,artifacts into space debris, pirate cache
            }
            for (int j=0;j<5;++j) {
                int whichPlanet = star.planets[j];
                if (whichPlanet!=-1&&whichPlanet<NUM_PLANETS) {
                    Planet&planet = planets[whichPlanet];
                    if (planet.data[SPECIAL]>=6) {
                        planet.data[SPECIAL]=(rand()%2+6);//gold or gem deposits
                    }
                }
            }
        }
    }
}
void crossMapPlanetCopy(Planet&dst, const Planet&src) {
    dst=src;
}
int main (int argc, char**argv) {
    bool doHelp=false;
    if (argc<=1) {
        doHelp=true;
    }
    for (int i=1;i<argc;++i) {
        if (strcmp(argv[i],"-h")==0||
            strcmp(argv[i],"-help")==0||
            strcmp(argv[i],"--help")==0||
            strcmp(argv[i],"/help")==0||
            strcmp(argv[i],"/h")==0) {
            doHelp=true;
        }
    }
    if (doHelp) {
        printf("Usage Example:\n\n%s SAVE1.GAM SAVE2.GAM q0 SAVE3.GAM\nThe above example takes the planets from SAVE1.GAM applies it to the monsters and 4 player races and planet picks of SAVE2.GAM takes the 0th quadrant (numbered from 0 to 3) and saves the result into SAVE3.GAM\n\n",argv[0]);
        printf("Generic usage %s <planetInput> <raceInput> <quadrantSelection> <output>\n\n",argv[0]);
        printf("The general usage is that <planetInput> should be set to a Master of Orion II save game file, often the same file, that contains the planets and <raceInput> should be set to the save game that has the desired races. Then the quadrantSelection selects a portion of the map and rotates and mirrors it so that every player gets an even shake. <output> should be set to the final save file that may be reloaded for the fair game\n\n");
        printf("quadrant selection is limited to the following options:\n");
        printf("2 player options:\n");
        printf("h0 assume a 2 player game and take the left half and reflect it\n");
        printf("h1 assume a 2 player game and take the right half and reflect it\n");
        printf("v0 assume a 2 player game and take the top half and reflect it\n");
        printf("v1 assume a 2 player game and take the bottom half and reflect it\n");
        printf("4 player options:\n");
        printf("q0 assume a 4 player game and take the top left quarter and mirror it\n");
        printf("q1 assume a 4 player game and take the bottom left quarter and mirror it\n");
        printf("q2 assume a 4 player game and take the bottom right quarter and mirror it\n");
        printf("q3 assume a 4 player game and take the top right quarter and mirror it\n");
        printf("x0 assume a 6 player game and take the first slice and mirror it\n");
        printf("6 player options:\n");
        printf("x0 or x1 or x2 or x3 or x4 or x5 mirror the appropriate slice\n");

        return 0;
    }
    srand(0x31337);
    Star stars[MAX_NUM_STARS];
    Planet planets[MAX_NUM_PLANETS];
    Star newStars[MAX_NUM_STARS];
    Planet newPlanets[MAX_NUM_PLANETS];
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
    
    fseek(fp,0,SEEK_END);
    size_t fileSize = ftell(fp);
    fseek(fp,0,SEEK_SET);    
    byt * data = (byt*)malloc(fileSize);
    fread(data,1,fileSize,fp);
    fclose(fp);
    FILE * output;
    size_t writeFileSize=0;
    byt * writeData;
    if (argc>2) {
        output = fopen(argv[2],"rb");
        fseek(output,0,SEEK_END);
        writeFileSize = ftell(output);
        fseek(output,0,SEEK_SET);    
        writeData = (byt*)malloc(fileSize);
        fread(writeData,1,writeFileSize,output);
        fclose(output);
    }
    for (int doInput=(argc>2?0:1);doInput<2;++doInput) {
        for (int i=0;i<NUM_PLANETS;++i) {
            const byt * curData = (doInput?data:writeData)+(PLANET_OFFSET+i*PLANET_SIZE);
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
            if (doInput) {
                planets[i]=planetB;
            }else {
                newPlanets[i]=planetB;
            }
        }
    }
    
    int maxx = -(1<<30);
    int minx = (1<<30);
    int maxy = -(1<<30);
    int miny = (1<<30);
    nerf(stars,planets);
    for (int doInput=(argc>2?0:1);doInput<2;++doInput) {
        for (int i=0;i<NUM_STARS;++i) {
            const byt * curData = (doInput?data:writeData)+(STAR_OFFSET+i*STAR_SIZE);
            Star starA;
            
            memcpy(&starA,curData,STAR_SIZE);
//        starA.printStar();
            Star starB;
            starB.readStar(curData);
            if (doInput) {
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
            }else {
                newStars[i]=starB;
            }
            if (memcmp(&starA,&starB,STAR_SIZE)) {
                printf("Endianness Mismatch: luckily we coded for that\n");
            }
            byt testIdempotency[STAR_SIZE];
            starB.writeStar(testIdempotency);
            starA.readStar(testIdempotency);
            if (memcmp(&starA,&starB,STAR_SIZE)) {
                starB.writeStar(testIdempotency);
                starA.readStar(testIdempotency);

                printf("Idempotency Mismatch: FAIL\n");
                if (!(starA==starB)) {
                    printf("Idempotency Mismatch: FAIL B\n");
                }
            }
            if (memcmp(testIdempotency,curData,STAR_SIZE)) {
                printf("Idempotency Mismatch: FAIL Internal\n");
            }
        }
    }
    for (int i=0;i<NUM_STARS;++i) {
        if (newStars[i].isEmpty()) {
            NUM_STARS=i;
            if (i==0) NUM_STARS=71;
            printf("Setting num stars to %d\n",NUM_STARS);
            break;
        }
    }
    if (argc==2) {
        for (int i=0;i<NUM_STARS;++i) {
            stars[i].recordHist();

            stars[i].printStar(planets,stars);
        }
        printf("Bounds: (%d,%d) - (%d,%d)\n",minx,miny,maxx,maxy);
        printHist();
        return 0;
    }
    printf("Bounds: (%d,%d) - (%d,%d)\n",minx,miny,maxx,maxy);
    if (false) {
        for (int i=0;i<NUM_STARS;++i) {
            isHomeworld(stars[i],planets);
        }
        for (int i=0;i<NUM_STARS;++i) {
            isHomeworld(newStars[i],newPlanets);
        }
        for (std::set<std::string>::iterator i=validNames.begin(),ie=validNames.end();i!=ie;++i) {
            starNames.push_back(*i);
        }
    }else {
        for (int i=0;i<sizeof(possibleNames)/sizeof(char*);++i) {
            starNames.push_back(possibleNames[i]);
        }
    }
    //wipePlanets(newStars,newPlanets);
    //wipeStars(newStars,newPlanets); no longer: we now work with what we have
    double percent_safe_zone=0;//.03125;
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
        NUM_PLAYERS=4;
        numX=2;
        numY=2;
        flipX=true;
        flipY=true;
    }
    if (mode=='h') {
        NUM_PLAYERS=2;
        numX=2;
        numY=1;
        flipX=true;
        flipY=false;

    }
    if (mode=='v') {
        NUM_PLAYERS=2;
        numX=1;
        numY=2;
        flipX=false;
        flipY=true;
    }
    if (mode=='x') {
        NUM_PLAYERS=6;
        numX=3;
        numY=2;
        flipX=false;
        flipY=true;
    }

    {
        std::set<int>homeworldlessQuadrant;
        std::vector<int> freePlanets;
        std::map<int,int> starMap;//destination star to source star (multiple desitnations may reference a single source)
        int freeStar=0;
        double homeX, homeY;
        for (int doPlace=0;doPlace<2;++doPlace) {
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
                        //printf("Searching range (%f %f, %f %f)\n",localminx,localminy,localmaxx,localmaxy);
                        if (slice==count) {
                            sourceminx=localminx;
                            sourceminy=localminy;
                            sourcemaxx=localmaxx;
                            sourcemaxy=localmaxy;
                            int homeIndex = findHomeworld (stars,planets,localminx,localminy,localmaxx,localmaxy);
                            if (homeIndex==-1) {
                                printf("Cannot find homeworld in section %d...exiting\n",slice);
                                return -1;
                            }else {
                                Star homeSystem = stars[homeIndex];
                                homeX = ((flipX&&x)?localmaxx-homeSystem.x:homeSystem.x-localminx);
                                homeY = ((flipY&&y)?localmaxy-homeSystem.y:homeSystem.y-localminy);

                                printf("Homeworld located at %s %f %f (%d %d)\n",homeSystem.name,homeX,homeY,homeSystem.x,homeSystem.y);
                            }
                        }
                        //wipeQuadrant(newStars,newPlanets,localminx,localminy,localmaxx,localmaxy);
                    }else if (doPlace==1){
                        copyQuadrantStars(newStars,newPlanets, localminx,localminy,localmaxx,localmaxy,
                                          stars,planets,sourceminx,sourceminy,sourcemaxx,sourcemaxy,flipX,flipY,count,starMap,freePlanets, freeStar);//saves up some free planets for us
                        int newHomeX = (flipX&&x)?localmaxx-homeX:homeX+localminx;
                        int newHomeY = (flipY&&y)?localmaxy-homeY:homeY+localminy;
                        printf("Placing homeworld at %d %d (From %f %f)\n",newHomeX, newHomeY, homeX, homeY);
                        if (!fixupHomeworlds(newStars,newPlanets, localminx,localminy,localmaxx,localmaxy,
                                             newHomeX,newHomeY,count)) {
                            printf("Could not find %d th homeworld\n",count);
                        }

                    }
                    ++count;
                }
            }
        }
        {//go through and copy planets
            while ((freeStar=nextFreeStar(newStars,newPlanets,freeStar))!=-1) {
                //if (!isHomeworld(newStars[freeStar],newPlanets)) {freeStar should look for homeworlds
                //uSELESS STAR
                //strcpy(newStars[freeStar].name,"DANGER");
                printf("Found a free star\n");
                for (int p=0;p<5;++p) {
                    if (newStars[freeStar].planets[p]!=-1&&newStars[freeStar].planets[p]<NUM_PLANETS) {
                        if (newPlanets[newStars[freeStar].planets[p]].data[PARENT_STAR]==freeStar) {
                            freePlanets.push_back(newStars[freeStar].planets[p]);
                        }else {
                            if (newStars[freeStar].planets[p]!=0&&newStars[freeStar].planets[p]<NUM_PLANETS) {
                                printf("Odd syste in save file that's cross referenced\n");
                            }
                        }
                    }
                    newStars[freeStar].planets[p]=-1;
                }
                //}
                ++freeStar;
            } 
            printf("Orphan star size %d\n",(int)orphanStars.size());
            int orphanCount=orphanStars.size()==2?1:0;
            for (int index=0;index<NUM_STARS;++index) {
                Star &dst=newStars[index];
                if (starMap.find(index)!=starMap.end()) {
                    int destStarIndex = index;
                    
                    Star star = stars[starMap[index]];
                    for (int p=0;p<5;++p) {
                        if (dst.planets[p]!=-1&&dst.planets[p]<NUM_PLANETS) {
                            if (newPlanets[dst.planets[p]].data[PARENT_STAR]==destStarIndex) {
                                freePlanets.push_back(dst.planets[p]);//this will guarantee we pop these guys first to minimize change we can believe in
                            }else if (dst.planets[p]!=0&&dst.planets[p]<NUM_PLANETS) {
                                printf("Odder syste in save file that's cross referenced\n");
                            }
                            dst.planets[p]=-1;
                        }
                    }
                    bool didUltraRich=false;
                    bool isThisOrphan = orphanStars.find(destStarIndex)!=orphanStars.end();
                    if(isThisOrphan) {
                        dst.x=(minx+maxx)/2;
                        dst.y=(miny+maxy)/2;//put this in the middle of the map
                        if (orphanCount>0) {
                            double angle=0;
                            switch (orphanCount) {
                              case 1:
                                angle=0;
                                break;
                              case 2:
                                angle=M_PI;
                                break;
                              case 3:
                                angle=M_PI/2;
                                break;
                              case 4:
                                angle=3*M_PI/2;
                                break;
                              default:
                                angle = 3.1415926536*2*(.5+((orphanCount-5)/4.0));
                                break;
                            }
                            int del=(minx+maxx)/10;
                            int delx = (int)(del*cos(angle));
                            int dely = (int)(del*sin(angle));
                            dst.x+=delx;
                            dst.y+=dely;
                        }
                        ++orphanCount;
                    }
                    for (int p=0;p<5;++p) {
                            if (star.planets[p]!=-1&&star.planets[p]<NUM_PLANETS) {
                                if (freePlanets.size()) {
                                    int newPlanetIndex = freePlanets.back();
                                    freePlanets.pop_back();
                                    short originalOwner = newPlanets[newPlanetIndex].data[PARENT_STAR];
                                    if (originalOwner>=0&&originalOwner<NUM_STARS) {
                                        const Star &check = newStars[originalOwner];
                                        for (int pp=0;pp<5;++pp) {
                                            if (check.planets[pp]==newPlanetIndex&&check.planets[pp]!=-1) {
                                                printf("FATAL PLANETARY CROSS ALIGNMENT\n");
                                            }
                                        }
                                    }
                                    crossMapPlanetCopy(newPlanets[newPlanetIndex],planets[star.planets[p]]);
                                    
                                    if (isThisOrphan) {
                                        if (didUltraRich==false&&newPlanets[newPlanetIndex].data[TYPE]==0x3) {
                                            didUltraRich=true;
                                            if (NUM_STARS>50) {
                                                newPlanets[newPlanetIndex].data[MINERALS]=0x4;//set to ultra rich!!!!
                                                newPlanets[newPlanetIndex].data[G]=0x2;//set to heavy G!!!!
                                            }else {
                                                newPlanets[newPlanetIndex].data[MINERALS]=0x3;//set to rich!!!!
                                                newPlanets[newPlanetIndex].data[G]=0x1;//set to normal G!!!!
                                            }
                                            newPlanets[newPlanetIndex].data[PLANETSIZECLASS]=rand()%0x5;
                                            newPlanets[newPlanetIndex].data[ENVIRONMENT]=rand()%0xa;
                                        }else {
                                            newPlanets[newPlanetIndex].data[G]=0x1;//set to normal G!!!!
                                            
                                            if (NUM_STARS>50) {
                                                newPlanets[newPlanetIndex].data[MINERALS]=rand()%0x3+1;//not ultra rich
                                            }else {
                                                newPlanets[newPlanetIndex].data[MINERALS]=rand()%0x2+1;//not ultra poor
                                            }
                                            newPlanets[newPlanetIndex].data[PLANETSIZECLASS]=rand()%0x5;
                                            newPlanets[newPlanetIndex].data[ENVIRONMENT]=rand()%0xa;
                                        }
                                    }
                                    dst.planets[p]=newPlanetIndex;
                                    newPlanets[newPlanetIndex].data[PARENT_STAR]=destStarIndex;
                                }else {
                                    printf("Unable to allocate free planet for star %s\n",dst.name);
                                }
                            }
                        }
                }else {
                    printf("Could not locate source for %d\n",index);
                }
            }
            while (!freePlanets.empty()) {
                newPlanets[freePlanets.back()]=Planet();
                freePlanets.pop_back();
            }
            for (int index=0;index<NUM_STARS;++index) {
                bool error=false;
                for (int j=0;j<5;++j) {
                    int ind = newStars[index].planets[j];
                    if (ind!=-1&&ind<NUM_PLANETS) {
                        if (newPlanets[ind].data[PARENT_STAR]!=index) {
                            newStars[index].planets[j]=-1;
                            error=true;
                        }
                    }
                }
                if (error) {
                    if (starMap.find(index)!=starMap.end()) {
                        printf("MISMATCH ERROR in system %s index %d mapping to %s\n",newStars[index].name,index,stars[starMap[index]].name);
                    }else {
                        printf("MISMATCH ERROR in system %s index %d\n",newStars[index].name,index,stars[starMap[index]].name);
                    }
                }
            }
        }
        
    }
    free(data);
    if (argc>4) {//if we can write to a file
        output = fopen(argv[4],"w+b");//overwrite the output save file
        fwrite(writeData,1,writeFileSize,output);
        free(writeData);
        fseek(output,PLANET_OFFSET,SEEK_SET);
        for (int i=0;i<NUM_PLANETS;++i) {
            unsigned char planetData[PLANET_SIZE];
            newPlanets[i].writePlanet(planetData);
            fwrite(planetData,1,PLANET_SIZE,output);
        }
        fseek(output,STAR_OFFSET,SEEK_SET);
        for (int i=0;i<NUM_STARS;++i) {
            unsigned char starData[STAR_SIZE];
            newStars[i].writeStar(starData);
            fwrite(starData,1,STAR_SIZE,output);
        }
        fclose(output);
        return 0;
        char *args[2];
        args[0]=argv[0];
        args[1]=argv[4];
        return main(2,args);
    }else for (int i=0;i<NUM_STARS;++i) {
        newStars[i].printStar(newPlanets,newStars);
    }

}
