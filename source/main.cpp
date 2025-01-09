#include<cstddef>//std::size_t
#include<cstdio>//std::fprintf std::printf
#include<filesystem>//std::filesystem
#include"count_lines_in_path.hpp"
#include"Timer.hpp"
int main(int argc,char* argv[]){
    if(argc<2){
        std::fprintf(
            stderr
            ,"Usage: %s <path 1> ... <path N(N>=1)>\n"
            ,argv[0]
        );
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
            std::fprintf(
                stderr
                ,"Error: %s is not a valid path.\n"
                ,path.string().c_str()
            );
            continue;
        }
        timer.start();
        lines=count_lines_in_path(path);
        timer.stop();
        std::printf(
            "Lines of C++ code in \"%s\": %ju (%s)\n"
            ,path.string().c_str()
            ,lines
            ,timer.delta_string().c_str()
        );
        total_lines+=lines;
    }
    total_timer.stop();
    std::printf(
        "Total lines of C++ code: %ju (%s)\n"
        ,total_lines
        ,total_timer.delta_string().c_str()
    );
    return 0;
}
