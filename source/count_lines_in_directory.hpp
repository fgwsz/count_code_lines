#pragma once
#include<cstddef>//std::size_t
#include<filesystem>//std::filesystem
#include"count_lines_in_file.hpp"
//递归遍历目录并统计所有C/C++源文件的行数
inline std::size_t count_lines_in_directory(
    std::filesystem::path const& dir_path
){
    if(!std::filesystem::is_directory(dir_path)){
        return 0;
    }
    std::size_t total_lines=0;
    for(
        auto const& entry:
            std::filesystem::recursive_directory_iterator(dir_path)
    ){
        total_lines+=count_lines_in_file(entry.path());
    }
    return total_lines;
}
