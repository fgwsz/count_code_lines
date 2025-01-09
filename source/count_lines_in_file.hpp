#pragma once
#include<cstddef>//std::size_t
#include<cstdio>
//std::FILE std::fopen std::fclose std::fread std::fprintf std::ferror
#include<filesystem>//std::filesystem
#include"is_cpp_file.hpp"
//统计文件的行数
inline std::size_t count_lines_in_file(
    std::filesystem::path const& file_path
){
    if(!is_cpp_file(file_path)){
        return 0;
    }
    static char buffer[1024*1024]={};
    std::string const&& path=file_path.string();
    std::FILE* file=std::fopen(path.c_str(),"rb");
    if(!file){
        std::fprintf(
            stderr
            ,"Error: std::fopen(\"%s\") failed!\n"
            ,path.c_str()
        );
        return 0;
    }
    std::size_t count=0;
    std::size_t lines=0;
    std::size_t index=0;
    std::size_t size=0;
    while((count=std::fread(buffer,sizeof(char),sizeof(buffer),file))>0){
        for(index=0;index<count;++index){
            if(buffer[index]=='\n'){
                ++lines;
            }
        }
        size=count;
    }
    if(std::ferror(file)){
        std::fprintf(
            stderr
            ,"Error: std::fread(\"%s\") failed!\n"
            ,path.c_str()
        );
        std::fclose(file);
        return 0;
    }
    //最后一行为一行数据但不含'\n'
    if((size>0)&&(buffer[size-1]!='\n')){
        ++lines;
    }
    std::fclose(file);
    return lines;
}
