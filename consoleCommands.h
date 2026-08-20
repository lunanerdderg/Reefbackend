#include <iostream> // Remember to move to 'cli.h'
#include <limits.h> // Linux
#include <unistd.h> // Linux
#include <pwd.h> // Linux

#include <cpr/cpr.h> // Must be rebuilt for Windows

#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
namespace fsys = std::filesystem;

// Cross-platform
unsigned short int readTo(std::string, char query='\t', unsigned int index=0);
unsigned short int fileExists(std::string, unsigned short int exitNum=1);
bool inProject(std::string);
bool makeDirectory(std::string);
bool moveFile(std::string, std::string);
bool deleteFile(std::string);
std::string getModParent(std::string);
//std::string getInternalFiles(std::string);
//bool extensionInside(std::string, std::string extension=".dll");

std::string getAsync(std::string url);
bool createFile(std::string contents, std::string fileName);
bool downloadFromURL(std::string url, std::string fileName);
std::vector<std::string> getBrowserDownloadURLsFromGithub(std::string url);
std::string dlFromGithub(std::string repositoryName, std::string contains="", bool excludePrereleases=true, std::string dlLocation="");
std::string getModVersionFromGithub(std::string repositoryName, bool excludePrereleases=true);

// Changes needed for cross-platform, but not programming ones
bool createModLibraryFolder();
bool sortModInLibrary(std::string mod);
bool addToLibraryFromGithub(std::string name, std::string repositoryName, std::string contains="", bool excludePrereleases=true);
bool addBepInExAndNautilusToLibrary();
bool removeModFromLibrary(std::string modName);

bool copyFile(std::string, std::string);
bool renameFile(std::string, std::string);

std::string getProfiles();
std::string getMods();

// Linux-only
std::string getPath();
std::string getHomeDirectory();
unsigned short int findSubnautica();
    // Literally uses commands
unsigned short int commandDoesNotExist(std::string, unsigned short int exitNum=1);
bool haveAllNecessaryDependencies();
unsigned short int unzip(std::string, std::string);

// To delete
//bool dlNautilus(std::string);
//bool dlBepInEx(std::string);
//bool installBepInEx(std::string);
//bool addToLibrary(std::string, std::string finalName="");
//bool addToLibrary(std::string, std::string, std::string, bool includeAllReleases=true, bool suffix=false, std::string removeStr="");
