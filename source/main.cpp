#include<cstddef>//std::size_t
#include<filesystem>//std::filesystem
#include<iostream>//std::cerr std::cout
#include"count_lines_in_path.hpp"
#include"Timer.hpp"
int main(int argc,char* argv[]){
    if(argc<2){
        std::cerr<<"Usage: "<<argv[0]
            <<" <path 1> ... <path N(N>=1)>"
            <<std::endl;
        return 1;
    }
    std::filesystem::path path={};
    std::size_t total_lines=0;
    std::size_t lines=0;
    Timer total_timer={};
    Timer timer={};
    total_timer.start();
    for(int index=1;index<argc;++index){
        path=argv[index];
        if (!std::filesystem::exists(path)){
            std::cerr<<"Error: "<<path<<" is not a valid path."<<std::endl;
            continue;
        }
        timer.start();
        lines=count_lines_in_path(path);
        timer.stop();
        std::cout<<"Lines of C++ code in \""<<path.string()
            <<"\": "<<lines
            <<" ("<<timer.delta_string()<<")"<<std::endl;
        total_lines+=lines;
    }
    total_timer.stop();
    std::cout<<"Total lines of C++ code: "<<total_lines
        <<" ("<<total_timer.delta_string()<<")"<<std::endl;
    return 0;
}
