#pragma once
#include<cstddef>//std::size_t
#include<filesystem>//std::filesystem
#include"count_lines_in_file.hpp"
#include"count_lines_in_directory.hpp"
//统计路径中所有C/C++源文件的行数
inline std::size_t count_lines_in_path(std::filesystem::path const& path){
    if(std::filesystem::is_regular_file(path)){
        return count_lines_in_file(path);
    }
    if(std::filesystem::is_directory(path)){
        return count_lines_in_directory(path);
    }
    return 0;
}
