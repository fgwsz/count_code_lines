#include<cstddef>//std::size_t
#include<filesystem>//std::filesystem
#include<iostream>//std::cerr std::cout
#include"count_lines_in_directory.hpp"
#include"Timer.hpp"
int main(int argc,char* argv[]){
    if(argc<2){
        std::cerr<<"Usage: "<<argv[0]
            <<" <directory 1> ... <directory N(N>=1)>"
            <<std::endl;
        return 1;
    }
    std::filesystem::path directory={};
    std::size_t total_lines=0;
    std::size_t lines=0;
    Timer total_timer={};
    Timer timer={};
    total_timer.start();
    for(int index=1;index<argc;++index){
        directory=argv[index];
        if (!std::filesystem::is_directory(directory)){
            std::cerr<<"Error: "<<directory<<" is not a valid directory."
                <<std::endl;
            continue;
        }
        timer.start();
        lines=count_lines_in_directory(directory);
        timer.stop();
        std::cout<<"Lines of C++ code in \""<<directory.string()
            <<"\" : "<<lines
            <<" ("<<timer.delta_string()<<")"<<std::endl;
        total_lines+=lines;
    }
    total_timer.stop();
    std::cout<<"Total lines of C++ code: "<<total_lines
        <<" ("<<total_timer.delta_string()<<")"<<std::endl;
    return 0;
}
