#include<cstddef>//std::size_t
#include<cstdio>//std::fprintf std::printf
#include<filesystem>//std::filesystem
#include<fstream>//std:ifstream
#include<string>//std::string std::getline std::to_string
#include<map>//std::map
#include<set>//std::set

#include"count_lines.h"
#include"language_of_extension.hpp"
#include"Timer.hpp"

static std::map<std::string,std::size_t> _lines_of_language={};

static std::size_t _get_file_lines(std::filesystem::path const& file_path);
static std::size_t _get_dir_lines(std::filesystem::path const& dir_path);
static std::size_t _get_lines(std::filesystem::path const& path);
static bool _check_extension(std::string const& extension);
static std::string _extension_to_language(std::string const& extension);
static void _update_language_info(
    std::string const& extension
    ,std::size_t lines
);

struct _LanguageInfo{
    std::string language_;
    std::size_t lines_;
};
struct _LanguageInfoGreater{
    bool operator()(_LanguageInfo const& lhs,_LanguageInfo const& rhs)const{
        if(lhs.lines_==rhs.lines_){
            return lhs.language_>rhs.language_;
        }
        return lhs.lines_>rhs.lines_;
    }
};

void count_lines(char const** path_list,std::size_t count){
    if(count==0){
        return;
    }
    for(std::size_t index=0;index<count;++index){
        if (!std::filesystem::exists(path_list[index])){
            std::fprintf(
                stderr
                ,"Error: \"%s\" is not a valid path.\n"
                ,path_list[index]
            );
            return;
        }
    }
    std::size_t total_lines=0;
    std::size_t lines=0;
    Timer total_timer={};
    Timer timer={};
    total_timer.start();
    for(std::size_t index=0;index<count;++index){
        timer.start();
        lines=_get_lines(path_list[index]);
        timer.stop();
        total_lines+=lines;
    }
    total_timer.stop();
    std::printf(
        "Total lines: %ju (%s)\n"
        ,total_lines
        ,total_timer.delta_string().c_str()
    );
    std::set<_LanguageInfo,_LanguageInfoGreater> result={};
    for(auto const& pair:_lines_of_language){
        result.emplace(_LanguageInfo{pair.first,pair.second});
    }
    std::size_t lines_width=std::to_string((std::size_t)-1).size();
    std::string lines_title="Lines";
    lines_title.resize(lines_width,' ');
    std::printf("%s|Percent\t |Language\n",lines_title.c_str());
    std::string info_lines={};
    for(auto const& info:result){
        info_lines=std::to_string(info.lines_);
        info_lines.resize(lines_width,' ');
        std::printf(
            "%s|%.2f\t%%|%s\n"
            ,info_lines.c_str()
            ,double(info.lines_)/double(total_lines)*100
            ,info.language_.c_str()
        );
    }
}
static std::size_t _get_file_lines(std::filesystem::path const& file_path){
    if(!std::filesystem::is_regular_file(file_path)){
        return 0;
    }
    std::string const&& extension=file_path.extension().string();
    if(!_check_extension(extension)){
        return 0;
    }
    std::ifstream ifs(file_path);
    if(!ifs.is_open()){
        return 0;
    }
    static std::string dummy_line={};
    std::size_t lines=0;
    while(std::getline(ifs,dummy_line)){
        ++lines;
    }
    _update_language_info(extension,lines);
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
static bool _check_extension(std::string const& extension){
    return language_of_extension.count(extension)!=0;
}
static std::string _extension_to_language(std::string const& extension){
    return language_of_extension.at(extension);
}
static void _update_language_info(
    std::string const& extension
    ,std::size_t lines
){
    _lines_of_language[_extension_to_language(extension)]+=lines;
}
