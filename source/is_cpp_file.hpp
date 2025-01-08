#pragma once
#include<filesystem>//std::filesystem
// 判断文件是否为C/C++源文件
bool is_cpp_file(std::filesystem::path const& file_path){
    static constexpr auto valid_extensions={
        ".h",".c",".hh",".cc",".hpp",".cpp",".hxx",".cxx",".inl"
    };
    std::string const extension=file_path.extension().string();
    for(auto const& element:valid_extensions){
        if(element==extension){return true;}
    }
    return false;
}
