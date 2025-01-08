#pragma once
#include<cstddef>//std::size_t
#include<filesystem>//std::filesystem
#include<fstream>//std::ifstream
#include<string>//std::getline
#include<vector>//std::vector
// 统计文件的行数
std::size_t count_lines_in_file(std::filesystem::path const& file_path){
    std::ifstream file(file_path);
    if(!file.is_open()){
        std::cerr<<"Error opening file: "<<file_path<<std::endl;
        return 0;
    }
    std::size_t lines=0;
    std::string line={};
    while(std::getline(file,line)){
        lines++;
    }
    return lines;
}
