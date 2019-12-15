#include <sys/personality.h>  
#include <unistd.h>
#include <vector>
#include <queue>
#include <string>
#include <iostream>
#include <experimental/filesystem>
#include <fstream>

namespace fs = std::experimental::filesystem;

struct coords
{
    std::string x,y,z;
};

std::vector<std::string> getFileNames(std::string path, std::string prefix)
{
    std::vector<std::string> tmp;
    for(auto& p: fs::directory_iterator(fs::path(path)))
    {   
        if (std::string(p.path().filename()).rfind(prefix, 0) == 0)
            {
                tmp.push_back(p.path());

            }
        
    }
     
    return tmp;
}

struct __attribute__((packed)) pdbfile
{
    char rname[6]; //1-6
    char serial[5];//7-11

    char pad1[1];//12

    char name[4];//13-16
    char altloc[1];//17
    char resname[3];//18-20

    char pad2[1];//21

    char chainId[1];//22
    char resseq[4];//23-26
    char icode[1];//27

    char pad3[3];//28-30

    char x[8];//31-38
    char y[8];//39-46
    char z[8];//47-54
    char occupancy[6];//55-60
    char tempFactor[6];//61-66

    char pad4[10];//67-76

    char element[2];//77-78
    char charge[2];//79-80
    char endl[1];//endl
    char nullchar = '\0';//null
};


void doRow(std::string filePath, std::vector<coords>& vec)
{
    std::ifstream input_file(filePath);
    std::string strb;
    
    getline(input_file, strb);
    //std::cout<<sizeof(pdbfile)<<std::endl;
    
    auto strEqual = [](std::string a, std::string b)
    {
        return a.find(b)!=std::string::npos;
    };
    while(true)
    {  
        getline(input_file, strb);
        if(strb.size()!=80) return;
        pdbfile& line  = *((pdbfile*) &strb[0]);

        std::string rname(line.rname,sizeof(line.rname));
        std::string isca(line.name, sizeof(line.name));
        
        if(!strEqual(rname,"ATOM") || !strEqual(isca,"CA ")) continue;
        vec.push_back({
            std::string(line.x,sizeof(line.x)),
            std::string(line.y,sizeof(line.y)),
            std::string(line.z,sizeof(line.z))
            });
    }
}

int main(int argc, char *argv[])
{
    std::string f_path = fs::current_path();
    std::string f_prefix = "pre_";

    if(argc == 2)
    {
        f_prefix = std::string(argv[1]);
    }
    if(argc == 3)
    {
       f_path = std::string(argv[1]);
        f_prefix = std::string(argv[2]);
    }
    if(argc != 3 && argc != 2)
    {
        std::cout<<"program [prefix]"<<std::endl;
        std::cout<<"program [path] [prefix]"<<std::endl;
        return 0;
    }

    std::vector<std::vector<coords>> matr;

    matr.push_back({});

    auto filenames = getFileNames(f_path, f_prefix);
    doRow(filenames[0], matr[0]);

    unsigned int  row   = filenames.size();
    unsigned int  column = matr[0].size();

    matr.resize(row);

    #pragma omp parallel for
    for(int i = 1; i<filenames.size(); ++i)
    {
        matr[i].reserve(row);
        doRow(filenames[i], matr[i]);
    }

    std::ofstream output_file(f_prefix+"OUTPUT.mat");

    for (auto& vec : matr)
    {
        for(coords& val:vec)
        {
            output_file<<val.x<<" "<<val.y<<" "<<val.z<<" ";
        }
        output_file<<std::endl;
    }
}

