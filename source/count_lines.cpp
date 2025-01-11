#include<cstddef>//std::size_t
#include<cstdio>//std::fprintf std::printf
//std::FILE std::fopen std::fclose std::fread std::ferror

#include<filesystem>//std::filesystem
#include<fstream>//std:ifstream
#include<string>//std::string std::getline
#include<map>//std::map
#include<set>//std::set

#include"count_lines.h"
#include"Timer.hpp"

#define _1MB (1024*1024)

static std::size_t _get_small_file_lines(
    std::filesystem::path const& file_path
);
static std::size_t _get_big_file_lines(
    std::filesystem::path const& file_path
);
static std::size_t _get_file_lines(std::filesystem::path const& file_path);
static std::size_t _get_dir_lines(std::filesystem::path const& dir_path);
static std::size_t _get_lines(std::filesystem::path const& path);
static std::map<std::string,std::size_t> _lines_of_extension={};

struct _ExtensionInfo{
    std::string extension_;
    std::size_t lines_;
};
struct _ExtensionInfoGreater{
    bool operator()(_ExtensionInfo const& lhs,_ExtensionInfo const& rhs)const{
        if(lhs.lines_==rhs.lines_){
            return lhs.extension_>rhs.extension_;
        }
        return lhs.lines_>rhs.lines_;
    }
};
void count_lines(char const** path_list,std::size_t count){
    if(count==0){
        return;
    }
    std::filesystem::path path={};
    std::size_t total_lines=0;
    std::size_t lines=0;
    Timer total_timer={};
    Timer timer={};
    total_timer.start();
    for(std::size_t index=0;index<count;++index){
        path=path_list[index];
        if (!std::filesystem::exists(path)){
            std::fprintf(
                stderr
                ,"Error: \"%s\" is not a valid path.\n"
                ,path.string().c_str()
            );
            continue;
        }
        timer.start();
        lines=_get_lines(path);
        timer.stop();
        std::printf(
            "Lines in \"%s\": %ju (%s)\n"
            ,path.string().c_str()
            ,lines
            ,timer.delta_string().c_str()
        );
        total_lines+=lines;
    }
    total_timer.stop();
    std::printf(
        "Total lines: %ju (%s)\n"
        ,total_lines
        ,total_timer.delta_string().c_str()
    );
    std::set<_ExtensionInfo,_ExtensionInfoGreater> result={};
    for(auto const& pair:_lines_of_extension){
        result.emplace(_ExtensionInfo{pair.first,pair.second});
    }
    std::printf("LINES\t\t|PERCENT |EXTENSION\n");
    for(auto const& info:result){
        std::printf(
            "%ju\t\t|%.2f\t%%|\"%s\"\n"
            ,info.lines_
            ,double(info.lines_)/double(total_lines)*100
            ,info.extension_.c_str()
        );
    }
}
static std::size_t _get_small_file_lines(
    std::filesystem::path const& file_path
){
    std::ifstream ifs(file_path);
    if(!ifs.is_open()){
        return 0;
    }
    static std::string dummy_line={};
    std::size_t lines=0;
    while(std::getline(ifs,dummy_line)){
        ++lines;
    }
    return lines;
}
static std::size_t _get_big_file_lines(
    std::filesystem::path const& file_path
){
    static char buffer[_1MB]={};
    std::string const&& path=file_path.string();
    std::FILE* file=std::fopen(path.c_str(),"rb");
    if(!file){
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
static std::size_t _get_file_lines(std::filesystem::path const& file_path){
    if(!std::filesystem::is_regular_file(file_path)){
        return 0;
    }
    std::size_t lines=0;
    if(std::filesystem::file_size(file_path)<_1MB){
        lines=_get_small_file_lines(file_path);
    }else{
        lines=_get_big_file_lines(file_path);
    }
    _lines_of_extension[file_path.extension().string()]+=lines;
    return lines;
}
static std::size_t _get_dir_lines(std::filesystem::path const& dir_path){
    std::size_t lines=0;
    for(
        auto const& entry:
            std::filesystem::recursive_directory_iterator(dir_path)
    ){
        lines+=_get_file_lines(entry.path());
    }
    return lines;
}
static std::size_t _get_lines(std::filesystem::path const& path){
    if(std::filesystem::is_directory(path)){
        return _get_dir_lines(path);
    }
    return _get_file_lines(path);
}
