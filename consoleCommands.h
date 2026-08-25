#include <limits.h> // Linux
#include <unistd.h> // Linux
#include <pwd.h> // Linux
 #include <signal.h> // Linux

#include <cpr/cpr.h> // Must be rebuilt for Windows

#include <iostream> // Remember to remove for GUI version
#include <ctime>
#include <string>
#include <sstream>
#include <vector>
#include <filesystem>
#include <fstream>
namespace fsys = std::filesystem;

// Cross-platform
unsigned short int readTo(std::string, char query='\t', unsigned int index=0);
unsigned int findInVector(std::vector<std::string> listOfStrings, std::string query);
unsigned short int fileExists(std::string, unsigned short int exitNum=1);
bool makeDirectory(std::string);
//bool makeFile(std::string fileName);
bool makeFile(std::string contents, std::string fileName);
bool copyFile(std::string, std::string);
bool deleteFile(std::string);
bool moveFile(std::string, std::string);
bool createNecessaryFolders();
std::string getProfiles();
std::string getMods();
//std::string getModParent(std::string);
//std::string getInternalFiles(std::string);
//bool extensionInside(std::string, std::string extension=".dll");
std::string getDateTimeString();

std::string getAsync(std::string url);
bool downloadFromURL(std::string url, std::string fileName);
std::vector<std::string> getBrowserDownloadURLsFromGithub(std::string url);
std::string dlFromGithub(std::string repositoryName, std::string contains="", bool excludePrereleases=true, std::string dlLocation="");
std::string getModVersionFromGithub(std::string repositoryName, bool excludePrereleases=true);

std::vector<std::vector<std::string>> getModList();
std::vector<std::string> getModList(std::string name);
bool addToLibraryFromModList(std::string name, bool safety=false);

// Changes needed for cross-platform, but not programming ones
bool sortModInLibrary(std::string mod);
bool addToLibraryFromGithub(std::string name, std::string repositoryName, std::string contains="", bool excludePrereleases=true);
bool addBepInExAndNautilusToLibrary();
bool removeModFromLibrary(std::string modName);

bool renameFile(std::string, std::string);

// Linux-only
//std::string getPath();
std::string getHomeDirectory();
unsigned short int findSubnautica();
//pid_t getSubnauticaPID();
//bool pidActive(pid_t pidNumber);
bool subnauticaOpen();
    // Literally uses commands
unsigned short int commandDoesNotExist(std::string, unsigned short int exitNum=1);
bool haveAllNecessaryDependencies();
unsigned short int unzip(std::string, std::string);
