#include <iostream>
#include <fstream>
#include <regex>
#include <string>

#include <filesystem>
#include <vector>


namespace fs = std::filesystem;


// 参数 1.目录 2.后缀名 3.文件
void getFilesWithExtension(const std::string& directory, const std::string& extension, std::vector<std::string>& files) {
    for (const auto& entry : fs::directory_iterator(directory)) {
        if (entry.is_regular_file() && entry.path().extension() == extension) {
            files.push_back(entry.path().filename().string());
        }
    }


}

void convertVttToLrc(const std::string& vttFile, const std::string& lrcFile) {
    std::ifstream vtt(vttFile);
    std::ofstream lrc(lrcFile);
    std::string line;
    std::regex timeRegex(R"((\d{2}):(\d{2}):(\d{2})\.(\d{3}))");

    if (!vtt.is_open() || !lrc.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    while (std::getline(vtt, line)) {
        std::smatch match;
        if (std::regex_search(line, match, timeRegex)) {
            
            int milliseconds = std::stoi(match[4].str());



            /*
            * 按秒来输入
            * 
            * 
            * 
            * 
            int hours = std::stoi(match[1].str());
            int minutes = std::stoi(match[2].str());
            int seconds = std::stoi(match[3].str());
            int totalSeconds = hours * 3600 + minutes * 60 + seconds;
            lrc << "[" << totalSeconds << "." << milliseconds / 10 << "]";
            */


            //时分秒      若没有超过1小时 隐藏小时
            if (match[1].str() == "00")
            {
                lrc << "[" << match[2].str() << ":" << match[3].str() << "." << milliseconds / 10 << "]";
            }
            else
            {
                lrc << "[" << match[1].str() << ":" << match[2].str() << ":" << match[3].str() << "." << milliseconds / 10 << "]";
            }
           


        }
        else if (!line.empty() && line[0] != 'W' && line[0] != '0') {
            lrc << line << std::endl;
        }
    }

    vtt.close();
    lrc.close();
}




int main() 
{
    using namespace std;
    //创建两个字符串存储vtt文件路径和lrc文件路径

    cout << "将vtt文件放入本程序目录下运行" << endl;
    system("pause");

    string vttFile;
    string lrcFile;





    string path = "./"; // 当前目录
    string ext = ".vtt"; // 需要查找的文件后缀
    string new_ext = ".lrc";//新的文件后缀

    vector<string> files;


    getFilesWithExtension(path, ext, files);    //获取当前目录下后缀为...的文件,存入files中


    //将files中的文件路径对应到 vtt和lrc的路径
    for (const auto& file : files) 
    {
       cout << file << endl;
        vttFile = file;
        lrcFile = file;
        lrcFile.replace(lrcFile.length() - 4, 4, new_ext);

        convertVttToLrc(vttFile, lrcFile);
        cout  <<"Conversion complete!" << endl;
    }
    system("pause");
    return 0;













}
