#include <iostream> // Remember to move to 'cli.h'
#include <limits.h> // Linux
#include <unistd.h> // Linux
// #include <windows.h> // Windows

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
namespace fsys = std::filesystem;

unsigned short int readTo(std::string, char query='\t', unsigned int index=0);
unsigned short int fileExists(std::string, unsigned short int exitNum=1);
bool inProject(std::string);
bool makeDirectory(std::string);
bool moveFile(std::string, std::string);
bool deleteFile(std::string);
std::string getInternalFiles(std::string);
std::string getModParent(std::string);
bool extensionInside(std::string, std::string extension=".dll");
bool createModLibraryFolder();

std::string getPath();

unsigned short int findSubnautica();
unsigned short int commandDoesNotExist(std::string, unsigned short int exitNum=1);
bool haveAllNecessaryDependencies();

bool copyFile(std::string, std::string);
bool renameFile(std::string, std::string);
unsigned short int unzip(std::string, std::string);

bool dlLatestGithubRelease(std::string, std::string, std::string, bool includeAllReleases=true, bool suffix=false, std::string removeStr="");
bool dlNautilus(std::string);
bool dlBepInEx(std::string);
bool installBepInEx(std::string);
bool addToLibrary(std::string, std::string finalName="");
bool addToLibrary(std::string, std::string, std::string, bool includeAllReleases=true, bool suffix=false, std::string removeStr="");

std::string getProfiles();
std::string getMods();
