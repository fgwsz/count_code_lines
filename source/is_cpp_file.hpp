#pragma once
#include<filesystem>//std::filesystem
#include<unordered_set>//std::unordered_set
#include<string_view>//std::string_view
// 判断文件是否为C/C++源文件
bool is_cpp_file(std::filesystem::path const& file_path){
    static std::unordered_set<std::string_view> const valid_extensions={
        ".h",".c",".hh",".cc",".hpp",".cpp",".hxx",".cxx",".inl"
    };
    return std::filesystem::is_regular_file(file_path)
        &&(valid_extensions.count(file_path.extension().c_str())!=0);
}
