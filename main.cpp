#include <iostream>
#include <fstream>
#include <regex>
#include <string>

#include <filesystem>
#include <vector>


namespace fs = std::filesystem;


// ���� 1.Ŀ¼ 2.��׺�� 3.�ļ�
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
            * ����������
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


            //ʱ����      ��û�г���1Сʱ ����Сʱ
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
    //���������ַ����洢vtt�ļ�·����lrc�ļ�·��

    cout << "��vtt�ļ����뱾����Ŀ¼������" << endl;
    system("pause");

    string vttFile;
    string lrcFile;





    string path = "./"; // ��ǰĿ¼
    string ext = ".vtt"; // ��Ҫ���ҵ��ļ���׺
    string new_ext = ".lrc";//�µ��ļ���׺

    vector<string> files;


    getFilesWithExtension(path, ext, files);    //��ȡ��ǰĿ¼�º�׺Ϊ...���ļ�,����files��


    //��files�е��ļ�·����Ӧ�� vtt��lrc��·��
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
