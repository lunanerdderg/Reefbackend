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
    if (fsys::exists(file)) {
        return exitNum;
    }
    return 0;
}
bool inProject(std::string file) { // Get if file is in executable directory
    return fileExists(getPath() + '/' + file);
}
bool makeDirectory(std::string destination) {
    return fsys::create_directories(destination);
}
bool moveFile(std::string file, std::string destination) {
    copyFile(file, destination);
    deleteFile(file);
    return true;
}
bool deleteFile(std::string destination) {
    fsys::remove_all(destination);
    return true;
}
std::string getInternalFiles(std::string directory) {
    std::string result = "";
    for (auto const& folder : fsys::recursive_directory_iterator{directory}) {
        if (!folder.is_directory() || fsys::is_empty(folder)) {
            result += folder.path().string();
            result += '\n';
        }
    }
    return result;
}
std::string getModParent(std::string directory) {
    for (auto const& folder : fsys::recursive_directory_iterator{directory}) {
        if (folder.is_directory() && (folder.path().filename().string() == "plugins" || folder.path().filename().string() == "config")) {
            return folder.path().parent_path().string();
        }
    }
    return "";
}
bool extensionInside(std::string directory, std::string extension) {
    for (auto const& folder : fsys::recursive_directory_iterator{directory}) {
        if (!folder.is_directory() && folder.path().extension().string() == extension) {
            return true;
        }
    }
    return false;
}
bool createModLibraryFolder() { // Returns true if any folders needed to be created
    if (!inProject("Mod-Library")) {
        makeDirectory(getPath() + '/' + "Mod-Library");
        return true;
    }
    return false;
}



// Changes required, but not coding ones

unsigned short int findSubnautica() { // 0 = Could not find, 1 = Steam, 2 = Heroic, 3 = Lutris (Linux only) / Epic Launcher (Windows only)
    unsigned short int result;
    result = fileExists("$HOME/.local/share/Steam/steamapps/common/Subnautica/", 1); // Windows: C:\\\\Program Files (x86)\\Steam\\steamapps\\common\\Subnautica
    if (result == 0) {
        result = fileExists("$HOME/Games/Heroic/Subnautica/", 2); // Windows: C:\\\\Users\\USERNAME\\Games\\Heroic\\Subnautica
        if (result == 0) {
            result = fileExists("$HOME/.lutris/epic-games-store/drive_c/Program Files/Epic Games/Subnautica/", 3); // Windows (Epic): C:\\\\Program Files\\Epic Games\\Subnautica
        }
    }
    return result;
}
bool copyFile(std::string file, std::string destination) {
    makeDirectory(file.substr(file.find_last_of('/') + 1));
    fsys::copy(file, destination + '/' + file.substr(file.find_last_of('/') + 1), fsys::copy_options::overwrite_existing | fsys::copy_options::recursive);
    return true;
}
bool renameFile(std::string file, std::string newName) {
    fsys::rename(file, file.substr(0, file.find_last_of('/')) + '/' + newName);
    return true;
}
bool installBepInEx(std::string subnauticaDirectory) {
    if (inProject("Mod-Library/BepInEx")) {
        return false;
    }
    std::string path = getPath() + "/Mod-Library/BepInEx";
    makeDirectory(path);
    moveFile(subnauticaDirectory + "/BepInEx", path);
    moveFile(subnauticaDirectory + "/changelog.txt", path);
    moveFile(subnauticaDirectory + "/doorstop_config.ini", path);
    moveFile(subnauticaDirectory + "/libdoorstop.dylib", path);
    moveFile(subnauticaDirectory + "/run_bepinex.sh", path);
    moveFile(subnauticaDirectory + "/.doorstop_version", path);
    copyFile(subnauticaDirectory + "/winhttp.dll", path);
    return true;
}
bool addToLibrary(std::string filePath, std::string finalName) {
    bool isPath = false;
    for (int i = 1; i < filePath.size() && filePath.at(i - 1); ++i) {
        if (filePath.at(i) == '/') { // Windows: if (filePath.at(i) == '\\') {
            isPath = true;
        }
    }
    if (isPath) {
        if (finalName == "") {
            finalName = fsys::path(filePath.c_str()).stem().string();
        }
        std::string path = getPath() + "/Mod-Library/" + finalName;
        std::string parentPath;
        std::string internalFiles;
        bool isArchive;
        {
            std::string extension = fsys::path(filePath.c_str()).extension().string();
            isArchive = (extension == ".zip" || extension == ".rar" || extension == ".7z" || extension.substr(0,4) == ".tar");
        }
        makeDirectory(path);
        if (isArchive) {
            unzip(filePath, path);
        }
        std::string archive = path + '/' + filePath;
        deleteFile(path + '/' + filePath);
        parentPath = getModParent(path);
        if (parentPath == "") {
            makeDirectory(path + "/plugins");
            bool dllInside = extensionInside(path);
            for (auto const& file : fsys::directory_iterator{path}) {
                if (file.path().string() != path + "/plugins") {
                    if (!dllInside && file.path().extension().string() == ".txt") {
                        makeDirectory(path + "/plugins/CustomCraft3/WorkingFiles");
                        moveFile(file.path().string(), path + "/plugins/CustomCraft3/WorkingFiles");
                    }
                    else if (!dllInside && file.path().extension().string() == ".structure") {
                        makeDirectory(path + "/plugins/EpicStructureLoader/Structures");
                        moveFile(file.path().string(), path + "/plugins/EpicStructureLoader/Structures");
                    }
                    else if (!dllInside && file.path().extension().string() == ".optoctreepatch") {
                        makeDirectory(path + "/plugins/TerrainPatcher/patches");
                        moveFile(file.path().string(), path + "/plugins/TerrainPatcher/patches");
                    }
                    else {
                        moveFile(file.path().string(), path + "/plugins");
                    }
                }
            }
        }
        else if (parentPath != path) {
            for (auto const& file : fsys::directory_iterator{parentPath}) {
                moveFile(file.path().string(),path);
            }
            deleteFile(parentPath);
        }
        if (fileExists(getPath() + '/' + finalName)) {
            deleteFile(getPath() + '/' + finalName);
        }
    }
    else { // install "BepInEx Tweaks"
        std::ifstream fin("Mod-List.tsv");
        std::string line;
        while (std::getline(fin, line)) {
            if (line.substr(0,filePath.size()) == filePath) {
                unsigned int prevIndex = 0;
                std::vector<std::string> parameters = {};
                for (int i = 0; i < line.size(); ++i) {
                    if (line.at(i) == '\t') {
                        parameters.push_back(line.substr(prevIndex, i - prevIndex));
                        prevIndex = i + 1;
                    }
                }
                parameters[3][0] -= '0';
                parameters[4][0] -= '0';
                return addToLibrary(parameters.at(1),parameters.at(2),parameters.at(0),parameters.at(3).at(0),parameters.at(4).at(0),parameters.at(5));
            }
        }
    }
    return true;
}
bool addToLibrary(std::string repo, std::string fileName, std::string finalName, bool includeAllReleases, bool suffix, std::string removeStr) {
    std::string path = getPath() + "/Mod-Library/" + finalName;
    std::string parentPath;
    std::string internalFiles;
    makeDirectory(path);
    bool result = dlLatestGithubRelease(repo, fileName, path, includeAllReleases, suffix, removeStr);
    if (!result) {
        return false;
    }
    std::string archive = path + '/' + fileName;
    if (suffix) {
        archive = archive.substr(0, archive.length()-4) + '*' + archive.substr(archive.length()-4, 4);
        unzip(archive, path);
    }
    else {
        unzip(archive, path);
    }
    deleteFile(path + '/' + fileName);
    parentPath = getModParent(path);
    if (parentPath == "") {
        makeDirectory(path + "/plugins");
        bool dllInside = extensionInside(path);
        for (auto const& file : fsys::directory_iterator{path}) {
            if (file.path().string() != path + "/plugins") {
                if (!dllInside && file.path().extension().string() == ".txt") {
                    makeDirectory(path + "/plugins/CustomCraft3/WorkingFiles");
                    moveFile(file.path().string(), path + "/plugins/CustomCraft3/WorkingFiles");
                }
                else if (!dllInside && file.path().extension().string() == ".structure") {
                    makeDirectory(path + "/plugins/EpicStructureLoader/Structures");
                    moveFile(file.path().string(), path + "/plugins/EpicStructureLoader/Structures");
                }
                else if (!dllInside && file.path().extension().string() == ".optoctreepatch") {
                    makeDirectory(path + "/plugins/TerrainPatcher/patches");
                    moveFile(file.path().string(), path + "/plugins/TerrainPatcher/patches");
                }
                else {
                    moveFile(file.path().string(), path + "/plugins");
                }
            }
        }
    }
    else if (parentPath != path) {
        for (auto const& file : fsys::directory_iterator{parentPath}) {
            moveFile(file.path().string(),path);
        }
        deleteFile(parentPath);
    }
    if (fileExists(getPath() + '/' + finalName)) {
        deleteFile(getPath() + '/' + finalName);
    }
    return true;
}
std::string getProfiles() {
    std::string result = "";
    for (auto const& folder : fsys::directory_iterator{getPath() + "/Profiles/"}) {
        if (folder.is_directory()) {
            result += folder.path().filename().string();
            result += '\n';
        }
    }
    return result;
}
std::string getMods() {
    std::string result = "";
    for (auto const& folder : fsys::directory_iterator{getPath() + "/Mod-Library/"}) {
        if (folder.is_directory()) {
            result += folder.path().filename().string();
            result += '\n';
        }
    }
    return result;
}



// Linux
// Suppress Linux console: >/dev/null 2>&1

std::string getPath() {
    char result[PATH_MAX];
    long long int count = readlink("/proc/self/exe", result, PATH_MAX);
    std::string returnVal(result, (count > 0) ? count : 0);
    int index = returnVal.length();
    for (int i = 0; i < returnVal.length()-5; ++i) {
        if (returnVal.substr(i, 5) == "/bin/") {
            index = i;
        }
    }
    return returnVal.substr(0,index);
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
    if (commandDoesNotExist("curl")) {
        return false;
    }
    if (commandDoesNotExist("wget")) {
        return false;
    }
    if (commandDoesNotExist("grep")) {
        return false;
    }
    if (commandDoesNotExist("unzip")) {
        return false;
    }
    return true;
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

bool dlLatestGithubRelease(std::string repo, std::string fileName, std::string location, bool includeAllReleases, bool suffix, std::string removeStr) {
    unsigned short int result;
    if (commandDoesNotExist("curl") || commandDoesNotExist("wget") || commandDoesNotExist("grep")) {
        return false;
    }
    std::string command = "";
    std::string pre = "";
    if (removeStr != "") {
        pre = '%' + removeStr + "*}${curTag#*" + removeStr;
    }
    if (suffix && includeAllReleases && fileName.length() > 8 && fileName.substr(fileName.length()-8, 5) == ".tar.") {
        command = "cd \"" + location + "\"\ncurTag=$(curl -s https://api.github.com/repos/" + repo + "/releases | jq -r '.[0].tag_name')\nsuffix=\"${curTag" + pre + "}\"\nwget \"https://github.com/" + repo + "/releases/download/${curTag}/" + fileName.substr(0, fileName.length()-8) + "${suffix}" + fileName.substr(fileName.length()-8, 8) + "\"\nmv \"" + fileName.substr(0, fileName.length()-8) + "${suffix}" + fileName.substr(fileName.length()-8, 8) + "\" \"" + fileName + '"';
    }
    else if (suffix && includeAllReleases && fileName.length() > 7 && fileName.substr(fileName.length()-7, 5) == ".tar.") {
        command = "cd \"" + location + "\"\ncurTag=$(curl -s https://api.github.com/repos/" + repo + "/releases | jq -r '.[0].tag_name')\nsuffix=\"${curTag" + pre + "}\"\nwget \"https://github.com/" + repo + "/releases/download/${curTag}/" + fileName.substr(0, fileName.length()-7) + "${suffix}" + fileName.substr(fileName.length()-7, 7) + "\"\nmv \"" + fileName.substr(0, fileName.length()-7) + "${suffix}" + fileName.substr(fileName.length()-7, 7) + "\" \"" + fileName + '"';
    }
    else if (suffix && includeAllReleases && fileName.length() > 4) {
        command = "cd \"" + location + "\"\ncurTag=$(curl -s https://api.github.com/repos/" + repo + "/releases | jq -r '.[0].tag_name')\nsuffix=\"${curTag" + pre + "}\"\nwget \"https://github.com/" + repo + "/releases/download/${curTag}/" + fileName.substr(0, fileName.length()-4) + "${suffix}" + fileName.substr(fileName.length()-4, 4) + "\"\nmv \"" + fileName.substr(0, fileName.length()-4) + "${suffix}" + fileName.substr(fileName.length()-4, 4) + "\" \"" + fileName + '"';
    }
    else if (includeAllReleases) {
        command = "cd \"" + location + "\"\ncurTag=$(curl -s https://api.github.com/repos/" + repo + "/releases | jq -r '.[0].tag_name')\nwget \"https://github.com/" + repo + "/releases/download/${curTag}/" + fileName + '"';
    }
    else if (suffix && fileName.length() > 4) {
        command = "cd \"" + location + "\"\ncurl -s https://api.github.com/repos/" + repo + "/releases/latest \\\n| grep \"browser_download_url.*" + fileName.substr(1, fileName.length()-5) + '*' + fileName.substr(fileName.length()-4, 4) + "\" \\\n| cut -d : -f 2,3 \\\n| tr -d \\\" \\\n| wget -qi -";
    }
    else {
        command = "cd \"" + location + "\"\ncurl -s https://api.github.com/repos/" + repo + "/releases/latest \\\n| grep \"browser_download_url.*" + fileName.substr(1, fileName.length()-1) + "\" \\\n| cut -d : -f 2,3 \\\n| tr -d \\\" \\\n| wget -qi -";
    }
    result = system(command.c_str());
    return result == 0;
}
bool dlBepInEx(std::string subnauticaDirectory) {
    std::string directory = subnauticaDirectory + "/BepInEx"; // Windows: td::string directory = subnauticaDirectory + "\\BepInEx";
    if (fileExists(directory)) {
        return false;
    }
    dlLatestGithubRelease("toebeann/BepInEx.Subnautica", "Tobey.s.BepInEx.Pack.for.Subnautica.zip", subnauticaDirectory); // Windows: dlLatestGithubRelease("toebeann\\BepInEx.Subnautica", "Tobey.s.BepInEx.Pack.for.Subnautica.zip", subnauticaDirectory);
    directory = subnauticaDirectory + "/Tobey.s.BepInEx.Pack.for.Subnautica.zip"; // Windows: directory = subnauticaDirectory + "\\Tobey.s.BepInEx.Pack.for.Subnautica.zip";
    unzip(directory, subnauticaDirectory);
    deleteFile(directory);
    return true;
}



// Windows
// Suppress Windows console: >nul 2>nul

//std::string getPath() {
//  char result[MAX_PATH];
//  return std::string(result, GetModuleFileName(NULL, result, MAX_PATH));
//}
