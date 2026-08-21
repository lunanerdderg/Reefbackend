#include "consoleCommands.h"



// Both operating systems

unsigned short int readTo(std::string stringIn, char query, unsigned int index) {
    for (unsigned short int i = index; i < stringIn.length(); ++i) {
        if (stringIn.at(i) == query) {
            return i;
        }
    }
    return stringIn.length();
}
unsigned short int fileExists(std::string file, unsigned short int exitNum) { // Get if file exists on computer
    std::filesystem::path filePath(file.c_str());
    if (fsys::exists(filePath)) {
        return exitNum;
    }
    return 0;
}
//bool makeFile(std::string fileName) {
//    std::ofstream foutOne(fileName.c_str());
//    foutOne << "";
//    foutOne.close();
//    return true;
//}
bool makeFile(std::string contents, std::string fileName) {
    std::ofstream foutOne(fileName.c_str(), std::ios::binary);
    foutOne << contents;
    foutOne.close();
    return true;
}
bool makeDirectory(std::string destination) {
    if (fileExists(destination)) {
        return false;
    }
    return fsys::create_directories(destination);
}
bool copyFile(std::string file, std::string destination) {
    makeDirectory(destination);
    if (fsys::is_directory(file)) {
        unsigned int slash = file.find_last_of('/');
        if (slash != 0) {
            ++slash;
        }
//        if (destination == "") {
//            destination += '/';
//        }
        destination += file.substr(slash);
    }
    fsys::copy(file, destination, fsys::copy_options::overwrite_existing | fsys::copy_options::recursive);
    return true;
}
bool deleteFile(std::string destination) {
    fsys::remove_all(destination);
    return true;
}
bool moveFile(std::string file, std::string destination) {
    copyFile(file, destination);
    deleteFile(file);
    return true;
}
bool createNecessaryFolders() { // Returns true if any folders needed to be created
    if (!fileExists("Mod-Library")) {
        makeDirectory("Mod-Library");
    }
    if (!fileExists("Profiles")) {
        makeDirectory("Profiles");
    }
    return true;
}
std::string getProfiles() {
    std::string result = "";
    for (auto const& folder : fsys::directory_iterator{"Profiles"}) {
        if (folder.is_directory()) {
            result += folder.path().filename().string();
            result += '\n';
        }
    }
    return result;
}
std::string getMods() {
    std::string result = "";
    for (auto const& folder : fsys::directory_iterator{"Mod-Library"}) {
        if (folder.is_directory()) {
            result += folder.path().filename().string();
            result += '\n';
        }
    }
    return result;
}

//std::string getModParent(std::string directory) {
//    for (auto const& folder : fsys::recursive_directory_iterator{directory}) {
//        if (folder.is_directory() && (folder.path().filename().string() == "plugins" || folder.path().filename().string() == "config")) {
//            return folder.path().parent_path().string();
//        }
//    }
//    return "";
//}
//std::string getInternalFiles(std::string directory) {
//    std::string result = "";
//    for (auto const& folder : fsys::recursive_directory_iterator{directory}) {
//        if (!folder.is_directory() || fsys::is_empty(folder)) {
//            result += folder.path().string();
//            result += '\n';
//        }
//    }
//    return result;
//}
//bool extensionInside(std::string directory, std::string extension) {
//    for (auto const& folder : fsys::recursive_directory_iterator{directory}) {
//        if (!folder.is_directory() && folder.path().extension().string() == extension) {
//            return true;
//        }
//    }
//    return false;
//}

std::string getAsync(std::string url) {
    cpr::AsyncResponse fr = cpr::GetAsync(cpr::Url{url});
    cpr::Response r = fr.get();
    return r.text;
}
bool downloadFromURL(std::string url, std::string fileName) {
    if (url.back() == '/') {
        url.pop_back();
    }
    return makeFile(getAsync(url), fileName);
}
std::vector<std::string> getBrowserDownloadURLsFromGithub(std::string url) { // Gets the LATEST download links, NOT any from prior releases. Requires FULL url
    std::vector<std::string> result;
    std::stringstream json(getAsync(url));
    std::string curLine;
    bool prevURL = false;
    short tagCount = 0;
    while (!json.eof() && json >> curLine && tagCount <= 1) {
        tagCount += (curLine == "\"tag_name\":");
        if (curLine == "\"browser_download_url\":") {
            prevURL = true;
        }
        else if (prevURL) {
            prevURL = false;
            result.push_back(curLine.substr(1,curLine.size() - 2));
        }
    }
    return result;
}
std::string dlFromGithub(std::string repositoryName, std::string contains, bool excludePrereleases, std::string dlLocation) { // Returns the name of the file created. Requires specifically the repository name ("user/repository"), NOT url
    unsigned int fileNameBeginningIndex = 0;
    std::vector<std::string> dlUrlList;
    std::string dlUrl = "";
    std::string repoUrl = "https://api.github.com/repos/";
    repoUrl += repositoryName;
    repoUrl += "/releases";
    if (excludePrereleases) {
        repoUrl += "/latest";
    }
    dlUrlList = getBrowserDownloadURLsFromGithub(repoUrl);
    if (dlUrlList.size() < 1) {
        return "";
    }
    else if (dlUrlList.size() == 1 || contains.size() == 0) {
        dlUrl = dlUrlList.at(0);
        for (unsigned int i = dlUrl.size() - 2; i != -1 && dlUrl.at(i + 1) != '/'; --i) {
            if (dlUrl.at(i) == '/') {
                fileNameBeginningIndex = i + 1;
            }
        }

    }
    else {
        for (unsigned int i = 0; i < dlUrlList.size() && dlUrl.size() == 0; ++i) {
            for (unsigned int k = dlUrlList.at(i).size() - contains.size(); k != -1 && dlUrlList.at(i).at(k + 1) != '/'; --k) {
                if (dlUrlList.at(i).at(k) == '/') {
                    fileNameBeginningIndex = k + 1;
                }
                if (dlUrlList.at(i).substr(k, contains.size()) == contains) {
                    dlUrl = dlUrlList.at(i);
                }
            }
        }
    }
    dlLocation += dlUrl.substr(fileNameBeginningIndex);
    downloadFromURL(dlUrl, dlLocation);
    return dlUrl.substr(fileNameBeginningIndex);
}
std::string getModVersionFromGithub(std::string repositoryName, bool excludePrereleases) {
    repositoryName = "https://api.github.com/repos/" + repositoryName + "/releases";
    if (excludePrereleases) {
        repositoryName += "/latest";
    }
    std::string result = "";
    std::stringstream json(getAsync(repositoryName));
    std::string curLine;
    bool tag = false;
    while (!json.eof() && json >> curLine && result == "") {
        if (tag) {
            result = curLine.substr(1,curLine.size() - 3);
        }
        tag = (curLine == "\"tag_name\":");
    }
    return result;
}
std::vector<std::vector<std::string>> getModList() {
    std::vector<std::vector<std::string>> result(1);
    std::ifstream modList("mod-list.tsv");
    std::string line;
    for (unsigned int lineIndex = 0; std::getline(modList, line);++lineIndex) {
        result.at(lineIndex).resize(0);
        for (unsigned int prevIndex = 0, nextIndex = 0; result.at(lineIndex).size() < 5 && prevIndex < line.size() && nextIndex < line.size(); prevIndex = nextIndex + 1) {
            nextIndex = readTo(line, '\t', prevIndex);
            result.at(lineIndex).push_back(line.substr(prevIndex, nextIndex - prevIndex));
        }
        result.resize(result.size() + 1);
    }
    return result;
}
std::vector<std::string> getModList(std::string name) {
    std::vector<std::string> result;
    std::ifstream modList("mod-list.tsv");
    for (std::string line; std::getline(modList, line);) {
        if (line.size() > name.size() && line.substr(0, name.size()) == name) {
            for (unsigned int prevIndex = 0, nextIndex = 0; result.size() < 5 && prevIndex < line.size() && nextIndex < line.size(); prevIndex = nextIndex + 1) {
                nextIndex = readTo(line, '\t', prevIndex);
                result.push_back(line.substr(prevIndex, nextIndex - prevIndex));
            }
            return result;
        }
    }
    return result;
}
bool addToLibraryFromModList(std::string name, bool safety) { // BOOKMARK
    if (safety && fileExists("Mod-Library/" + name)) {
        return false;
    }
    std::vector<std::string> mod = getModList(name);
    if (mod.size() < 5) {
        return false;
    }
    return addToLibraryFromGithub(mod.at(0), mod.at(1), mod.at(2), (mod.at(3) == "1"));
}


// Changes required, but not coding ones

bool sortModInLibrary(std::string mod) {
    std::string location = "Mod-Library/" + mod;
    if (fileExists(location + "/BepInEx")) {
        if (fileExists(location + "doorstop_config.ini")) {
            deleteFile(location + "doorstop_config.ini");
        }
        if (fileExists(location + "winhttp.dll")) {
            deleteFile(location + "winhttp.dll");
        }
        if (fileExists(location + ".doorstop_version")) {
            deleteFile(location + ".doorstop_version");
        }
        renameFile(location, ".temp");
        renameFile("Mod-Library/.temp/BepInEx", mod);
        moveFile("Mod-Library/.temp/" + mod, "Mod-Library/" + mod);
        deleteFile("Mod-Library/.temp/");
    }
    if (fileExists(location + "/plugin") || fileExists(location + "/config") || fileExists(location + "/patchers") || fileExists(location + "/core")) {
        return true;
    }

//    bool containsDLL = false;
//    for (auto const& file : fsys::recursive_directory_iterator(location)) { // Testing whether the mod contains a .dll might help to organize it if it requires CustomCraft3 or contains a structure file and needs to be placed in those directories
//        std::string fileString = file.path().string();
//        if (fileString.size() > 4 && fileString.substr(fileString.size() - 4) == ".dll") {
//            containsDLL = true;
//            break;
//        }
//    }

    makeDirectory(location + "/plugins");
    for (auto const& file : fsys::directory_iterator(location)) {
        std::string fileString = file.path().string();
        if (fileString != location + "/plugins") {
            std::cout << fileString  << ", " << location << "/plugins" << std::endl;
            moveFile(fileString, location + "/plugins");
        }
    }
    return true;
}
bool addToLibraryFromGithub(std::string name, std::string repositoryName, std::string contains, bool excludePrereleases) {
    std::string location = "Mod-Library/";
    location += name;
    makeFile(getModVersionFromGithub(repositoryName, excludePrereleases), location + ".version");
    location += '/';
    makeDirectory(location);
    std::string modFile = dlFromGithub(repositoryName, contains, excludePrereleases, location);
    if (modFile.size() == 0) {
        return false;
    }
    else if (modFile.size() >= 5 && modFile.substr(modFile.size() - 4) == ".dll") {
        //
    }
    else {
        if (unzip(location + modFile, location) > 0) { // Absolute path
            deleteFile(location);
            return false;
        }
        deleteFile(location + modFile);
    }
    if (repositoryName == "toebeann/BepInEx.Subnautica") {
        return true;
    }
    return sortModInLibrary(name);
}
bool addBepInExAndNautilusToLibrary() {
    return (addToLibraryFromGithub("BepInEx", "toebeann/BepInEx.Subnautica") && addToLibraryFromGithub("Nautilus", "SubnauticaModding/Nautilus", "SN.STABLE", false));
}
bool removeModFromLibrary(std::string modName) {
    return (deleteFile("Mod-Library/" + modName) && deleteFile("Mod-Library/" + modName + ".version"));
}
bool renameFile(std::string file, std::string newName) {
    fsys::rename(file, file.substr(0, file.find_last_of('/') + 1) + newName);
    return true;
}

// Linux
// Suppress Linux console: >/dev/null 2>&1

//std::string getPath() {
//    char result[PATH_MAX];
//    long long int count = readlink("/proc/self/exe", result, PATH_MAX);
//    std::string returnVal(result, (count > 0) ? count : 0);
//    int index = returnVal.length();
//    for (int i = 0; i < returnVal.length()-5; ++i) {
//        if (returnVal.substr(i, 5) == "/bin/") {
//            index = i;
//        }
//    }
//    return returnVal.substr(0,index);
//}
std::string getHomeDirectory() {
    const char *homedir;
    if ((homedir = getenv("HOME")) == NULL) {
        homedir = getpwuid(getuid())->pw_dir;
    }
    std::string result = homedir;
    return homedir;
}

unsigned short int findSubnautica() { // 0 = Could not find, 1 = Steam, 2 = Heroic, 3 = Lutris (Linux only) / Epic Launcher (Windows only)
    unsigned short int result;
    std::string home = getHomeDirectory();
    std::string path = home;
    path += "/.local/share/Steam/steamapps/common/Subnautica/";
    result = fileExists(path.c_str(), 1); // Windows: C:\\\\Program Files (x86)\\Steam\\steamapps\\common\\Subnautica
    if (result == 0) {
        path = home;
        path += "/Games/Heroic/Subnautica/";
        result = fileExists(path.c_str(), 2); // Windows: C:\\\\Users\\USERNAME\\Games\\Heroic\\Subnautica
        if (result == 0) {
            path = home;
            path += "/.lutris/epic-games-store/drive_c/Program Files/Epic Games/Subnautica/";
            result = fileExists(path.c_str(), 3); // Windows (Epic): C:\\\\Program Files\\Epic Games\\Subnautica
        }
    }
    return result;
}




unsigned short int commandDoesNotExist(std::string command, unsigned short int exitNum) {
    command = "if ! command -v " + command + " >/dev/null 2>&1; then exit ";
    command += exitNum;
    command += "; fi >/dev/null 2>&1";
    if (system(command.c_str()) == 0) {
        return 0;
    }
    return exitNum;
}
bool haveAllNecessaryDependencies() {
    return (!commandDoesNotExist("unzip"));
}

unsigned short int unzip(std::string file, std::string location) { // Returns 0 if successful, 1 if failed on rar, and 7 if failed on 7z
    unsigned short int result = 0;
    if (file.substr(file.length()-4,4) == ".zip") {
        file = "unzip \"" + file + "\" -d \"" + location + "\"";
    }
    else if (file.substr(file.length()-4,4) == ".rar") {
        result = commandDoesNotExist("unrar");
        if (result == 0) {
            file = "unrar x \"" + file + "\" \"" + location + "\"";
        }
    }
    else if (file.substr(file.length()-3,3) == ".7z") {
        result = commandDoesNotExist("7z", 7);
        if (result == 0) {
            file = "7z x \"" + file + "\" -o\"" + location + "\"";
        }
    }
    else if (file.substr(file.length()-4,4) == ".tar" || file.substr(file.length()-7,5) == ".tar." || file.substr(file.length()-8,5) == ".tar.") {
        file = "tar -xf \"" + file + "\" -C \"" + location + "\"";
    }
    system(file.c_str());
    return result;
}


// Windows
// Suppress Windows console: >nul 2>nul

//std::string getPath() {
//  char result[MAX_PATH];
//  return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
//}
