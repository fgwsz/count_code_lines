#pragma once
#include<cstddef>//std::size_t
#include<filesystem>//std::filesystem
#include<fstream>//std::ifstream
#include<string>//std::getline
#include<vector>//std::vector
#include"is_cpp_file.hpp"
// 统计文件的行数
std::size_t count_lines_in_file(std::filesystem::path const& file_path){
    if(!is_cpp_file(file_path)){
        return 0;
    }
    std::ifstream file(file_path);
    if(!file.is_open()){
        std::cerr<<"Error opening file: "<<file_path<<std::endl;
        return 0;
    }
    static std::string line={};
    std::size_t lines=0;
    while(std::getline(file,line)){
        lines++;
    }
    return lines;
}
