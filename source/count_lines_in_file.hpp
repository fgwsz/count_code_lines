#pragma once
#include<cstddef>//std::size_t
#include<cstdio>//std::fopen
#include<filesystem>//std::filesystem
#include"is_cpp_file.hpp"
// 统计文件的行数
std::size_t count_lines_in_file(std::filesystem::path const& file_path){
    if(!is_cpp_file(file_path)){
        return 0;
    }
    static char buffer[1024]={};
    std::FILE* file=std::fopen(
        std::filesystem::absolute(file_path).string().c_str()
        ,"rb"
    );
    if(!file){
        std::fprintf(
            stderr,"Error: fopen(\"%s\") error!\n"
            ,std::filesystem::absolute(file_path).string().c_str()
        );
        return 0;
    }
    std::size_t count=0;
    std::size_t lines=0;
    std::size_t index=0;
    while((count=fread(buffer,sizeof(char),sizeof(buffer),file))>0){
        for(index=0;index<count;++index){
            if(buffer[index]=='\n'){
                ++lines;
            }
        }
    }
    if(ferror(file)){
        std::fprintf(
            stderr,"Error: fread(\"%s\") error!\n"
            ,std::filesystem::absolute(file_path).string().c_str()
        );
        std::fclose(file);
        return 0;
    }
    std::fclose(file);
    return lines;
}
