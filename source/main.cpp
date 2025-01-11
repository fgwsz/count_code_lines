#include<cstdio>//std::fprintf
#include"count_lines.h"
int main(int argc,char* argv[]){
    if(argc<2){
        std::fprintf(
            stderr
            ,"Usage: %s <path 1> ... <path N(N>=1)>\n"
            ,argv[0]
        );
        return 1;
    }
    count_lines((char const**)&(argv[1]),argc-1);
    return 0;
}
