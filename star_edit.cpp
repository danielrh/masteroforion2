#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <set>
#include <string>
#include <vector>


const char * possibleNames[]={"Rhodos","Delphi","Horta","Cassandra","Sethlans","Ismareos","Diomedes","Thrace","Pontus","Thesseus","Nortia","Stymphalus","Thebes","Hecaton","Arachne","Pactolus","Eretria","Hera","Leon","Euphrosyne","Augeas","Zephir","Eurus","Mummu","Ajax","Scyros","Icarus","Hehet","Dionysus","Ammon","Lerna","Neith","Postverta","Nekhbet","Thelxepia","Coeus","Astarte","Alcmene","Sphinx","Nepthys","Kingu","Iphicles","Sparta","Iapetus","Clytaemnestra","Kalkal","Alcestis","Iris","Tartarus","Bel","LotosAni","Calypso","Aglaia","Vladimir","Geb","Argos","Samos","Aegeus","Aplu","Apollo","Ninhursaga","Sobek","Antu","Imhotep","Khepry","Khnum","Vertumus","Paros","Perseus","Aeolus","Nabu","Clio","Marduk","Apsu","Inanna","Laius","Turan","Mammetum","Epimetheus","ZaltuAmaunet","Aton","Aia","Telamon","Ea","Bes","Polyhymnia","Charun","Shara","Union","Metope","Nin ildu","Hesione","Delos","Peisinoe","Thracia","Hades","Callen","Tenedos","Tyndareus","Peleus","Hecuba","Nemesis","Belet ili","Nammu","Nintu","Hestia","Laocoon","Atropos","Nemea","Clotho","Chalcis","Gibil","Aglaophonos","Sekhmet","Keket","Crete","Mut","Thalia","Tethys","Enki","Patroclus","Hecate","Enurta","Osiris","Tinia","Erebus","Amun","Enlil","Nin agal ","Ptah","Papsukkal ","Karl","Ishtar","Cetus","Sin","Minotaur","Seth","Cepheus","Maat","Molpe","Pandora","Isis","Olympia","Athena","Jocasta","Neoptolemos","Ninurta","Nanna","Lachesis","Hydra","Hathor","Hanish","Aruru","Selvans","Laomedon","Naxos","Anu","Soviet","Eris","Artemis","Megara","Thasos","Penthesilea","Calchas","Morpheus","Ennead","Iphigenia","Utu","ThothAether","Aphrodite","Choephori","Moscow","Euripides","Maia","Laran","Deidameia","Engels","Mount Ida","Hephaestus","Lykia","Heracleidae","Februus","Anuket","Apis","Oceanus","Nusku","Archimedes","Cautha","Nereid","Cronus","Leto","Serapis","Tiamat","Culsu","Plataea","Charontes","Andromeda","Erymanthia","Nethuns","Rhesus","Persephone","Phobe","Nike","Hippolyta","Theseus","Qingu","Nut","Hebe","Deadulus","Ellil","Atum","Calliope","Andromache","Agamemnon","Athens","Mami","Lycus","Berkeley","Hellespont","Siduri","Nemaea","Hypnos","Silenus","Ra","Kek","Asclepius","Enceladus","Trotsky","Khonsu","Midas","Meresger","Gerra","Lenin","Urania","Bastet","Feronia","Heh","Euterpe","Theba","Anshar","Nash","Erato","Melpomene","Argolida","Phrygia","Chios","Poseidon","Hyperion","Ninsun","Eros","Eos","Hercules","Terpischore","Apep","Myrmidon","Ishum","Thesan","Pyrrhus","Helene","Alexandros","Hesiod","Erinyes","Rhea","Ares","Mullitu","Lahmu","Anubis","Atlas","Menelaus","Thetis","Horus","Voltumna","Janus","Chryseis","Ashur","Cerynea","Cyclope","Friedrich","Pasiphae","Hespera ","Athos","Nimnah","Boreas","Red","Shamash","Aeschylus","Summanus","Hygeia","Anat","Ninlil","Naunet","Kakka","Oedipus","Fama","Notus","Kishar","Olympus","Leningrad","Dumkina","Zeus","Shu","Klytamnestra","Mors","Hermes","Gaea","Philoctetes","Antaios","Priam","Shullat","Sophocles","Min","Gushkin banda","Marx","Lahamu","Adad","Demeter"};
std::vector<std::string> starNames;
std::set<std::string> validNames;
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
        printf("Fallback in identifying %s as homeworld\n",star.name);
        retval = true;
    }
    if (retval) {//clear us from a valid name
        if (validNames.find(star.name)!=validNames.end()) {
            validNames.erase(star.name);
        }
    }
    return retval;
}

void wipeQuadrant(Star stars[],Planet planets[],double minx, double miny, double maxx, double maxy) {
    Star empty;//last star is our empty one?
    empty.x=0;
    empty.y=0;
    memset(empty.name,0,sizeof(empty.name));
    for (int i=0;i<NUM_PLANETS;++i) {
        int parent = planets[i].data[PARENT_STAR];
        if (parent!=-1) {
            if (!isHomeworld(stars[parent],planets)) {
                planets[i] = Planet();
            }
        }
    }
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
template <class Planet> int nextFree(Planet destPlanets[], int curFree, int max_planets) {
    for (int i=curFree;i<max_planets;++i) {
        if (destPlanets[i].isEmpty()) {
            return i;
        }
    }
    return -1;
}
void copyQuadrant(
    Star destStars[], Planet destPlanets[],double minx,double miny,double maxx,double maxy,
    Star stars[], Planet planets[], double sourceminx,double sourceminy,double sourcemaxx,double sourcemaxy,bool flipX,bool flipY) {
    int freeStar = nextFree(destStars,0,NUM_STARS);
    int freePlanet = nextFree(destPlanets,0,NUM_PLANETS);
    for (int i=0;i<NUM_STARS;++i) {
        if (stars[i].x>=sourceminx&&
            stars[i].x<=sourcemaxx&&
            stars[i].y>=sourceminy&&
            stars[i].y<=sourcemaxy&&
            !isHomeworld(stars[i],planets)) {
            destStars[freeStar] = stars[i];//copy relevant data about the star
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
            strncpy(destStars[freeStar].name,curName.c_str(),0xf);
            destStars[freeStar].name[0xe]='\0';//zero terminate
            //fixup x and y coordinates
            if (flipX&&sourceminx!=minx) {//only flip if we're on the opposite side
                int delx = stars[i].x-sourceminx;
                destStars[freeStar].x=maxx-delx;
            }
            if (flipY&&sourceminy!=miny) {//only flip if we're on the opposite side
                int dely = stars[i].y-sourceminy;
                destStars[freeStar].y=maxy-dely;
            }
            //fixup planets
            for (int j=0;j<5;++j) {
                if (stars[i].planets[j]!=-1) {//otherwise we have it covered because the gets operator should do it fine
                    if (freePlanet==-1) {
                        printf ("Failure to find available planet index for %s : quadrant too dense\n",stars[i].name);
                        destStars[freeStar].planets[j]=-1;
                    }else {
                        int planetIdx = stars[i].planets[j];
                        destPlanets[freePlanet] = planets[planetIdx];
                        destPlanets[freePlanet].data[PARENT_STAR] = freeStar;
                        destStars[freeStar].planets[j]=freePlanet;
                        freePlanet = nextFree(destPlanets,freePlanet,NUM_PLANETS);
                        if (freePlanet==-1) {
                            printf ("Failure to find available planet index: quadrant too dense\n");
                        }
                    }
                }
            }
            freeStar = nextFree(destStars,freeStar,NUM_STARS);
            if (freeStar==-1) {
                printf ("Failure to find available star index: quadrant too dense\n");
                return;
            }
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
                for (int j=0;j<5;++j) {
                    int planetIdx = stars[i].planets[j];
                    if (planetIdx!=-1) {
                        if (planets[planetIdx].data[PLANETSIZECLASS]==4) {//we know players cannot select huge planets in the race pix
                            planets[planetIdx].data[MINERALS]=2;//set huge planets to abundant for sure since they aren't home planets
                            
                        }
                    }
                }
                return true;
            }
        }
    }
    return false;
}

int main (int argc, char**argv) {
    Star stars[NUM_STARS];
    Planet planets[NUM_PLANETS];
    Star newStars[NUM_STARS];
    Planet newPlanets[NUM_PLANETS];
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
    if (argc==2) {
        for (int i=0;i<NUM_STARS;++i) {
            stars[i].printStar(planets,stars);
        }
        printf("Bounds: (%d,%d) - (%d,%d)\n",minx,miny,maxx,maxy);
        return 0;
    }
    printf("Bounds: (%d,%d) - (%d,%d)\n",minx,miny,maxx,maxy);
    if (true) {
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
                        printf("Searching range (%f %f, %f %f)\n",localminx,localminy,localmaxx,localmaxy);
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
                        wipeQuadrant(newStars,newPlanets,localminx,localminy,localmaxx,localmaxy);
                    }else {
                        copyQuadrant(newStars,newPlanets, localminx,localminy,localmaxx,localmaxy,
                                     stars,planets,sourceminx,sourceminy,sourcemaxx,sourcemaxy,flipX,flipY);
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
        char *args[2];
        args[0]=argv[0];
        args[1]=argv[4];
        return main(2,args);
    }else for (int i=0;i<NUM_STARS;++i) {
        newStars[i].printStar(newPlanets,newStars);
    }

}
