#include<cstddef>//std::size_t
#include<filesystem>//std::filesystem
#include<fstream>//std::ifstream
#include<string>//std::getline
#include<iostream>//std::cerr std::cout
namespace fs=std::filesystem;
// 判断文件是否为C/C++源文件
bool is_cpp_file(fs::path const& file_path){
    static constexpr auto valid_extensions={
        ".h",".c",".hh",".cc",".hpp",".cpp",".hxx",".cxx",".inl"
    };
    std::string const extension=file_path.extension().string();
    for(auto const& element:valid_extensions){
        if(element==extension){return true;}
    }
    return false;
}
// 统计文件的行数
std::size_t count_lines_in_file(fs::path const & file_path){
    std::ifstream file(file_path);
    if(!file.is_open()){
        std::cerr<<"Error opening file: "<<file_path<<std::endl;
        return 0;
    }
    std::size_t lines=0;
    std::string line;
    while(std::getline(file,line)){
        lines++;
    }
    return lines;
}
// 递归遍历目录并统计所有C/C++源文件的行数
std::size_t count_lines_in_directory(fs::path const& dir_path){
    int total_lines=0;
    for(const auto& entry:fs::recursive_directory_iterator(dir_path)){
        if(fs::is_regular_file(entry)&&is_cpp_file(entry.path())){
            total_lines+=count_lines_in_file(entry.path());
        }
    }
    return total_lines;
}
int main(int argc,char* argv[]){
    if(argc<2){
        std::cerr<<"Usage: "<<argv[0]<<" <directory>"<<std::endl;
        return 1;
    }
    fs::path directory={};
    std::size_t total_lines=0;
    std::size_t lines=0;
    for(int index=1;index<argc;++index){
        directory=argv[index];
        if (!fs::is_directory(directory)){
            std::cerr<<"Error: "<<directory<<" is not a valid directory."
                <<std::endl;
            continue;
        }
        lines=count_lines_in_directory(directory);
        std::cout<<"Lines of C++ code in \""<<directory.string()
            <<"\" : "<<lines<<std::endl;
        total_lines+=lines;
    }
    std::cout<<"Total lines of C++ code: "
        <<total_lines<<std::endl;
    return 0;
}
