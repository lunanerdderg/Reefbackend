#include "Profile.h"

Profile::Profile(std::string nameInput) { // Constructor assumes BepInEx already installed. Require user to install BepInEx first
    this->name = nameInput;
    if (this->name != "" && !this->profileExists()) {
        this->makeProfile();
    }
}

Profile::~Profile() {}

bool Profile::deleteProfile() {
    if (this->name == "") {
        return false;
    }
    deleteFile("Profiles/" + this->name);
    closeProfile();
    return true;
}

bool Profile::selectDifferentProfile(std::string newName) {
    this->name = newName;
    if (newName != "" && !this->profileExists()) {
        this->makeProfile();
    }
    return true;
}

bool Profile::closeProfile() {
    this->name = "";
    return true;
}

bool Profile::isProfileSelected() {
    return this->name != "";
}

std::string Profile::getName() {
    return this->name;
}

bool Profile::rename(std::string newName) {
    renameFile("Profiles/" + this->name, newName);
    this->name = newName;
    return true;
}

bool Profile::profileExists() {
    if (this->name == "") {
        return false;
    }
    for (auto const& folder : fsys::directory_iterator{"Profiles/"}) {
        if (folder.path().filename().string() == this->name) {
            return true;
        }
    }
    return false;
}

bool Profile::makeProfile() {
    makeDirectory("Profiles/" + this->name + "/cache");
    makeDirectory("Profiles/" + this->name + "/config");
//    makeDirectory("Profiles/" + this->name + "/patchers");
    makeDirectory("Profiles/" + this->name + "/Previous-Logs");
    std::ofstream fout("Profiles/" + this->name + "/mods.tsv");
    fout << "";
    fout.close();
    return true;
}

std::string Profile::getTsvContents() {
    std::ifstream fin("Profiles/" + this->name + "/mods.tsv");
    return std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());;
}

bool Profile::addMod(std::string mod) {
    std::string contents = this->getTsvContents();
    std::ofstream fout("Profiles/" + this->name + "/mods.tsv");
    if (contents != "") {
        fout << contents << std::endl;
    }
    fout << mod << "\t1";
    fout.close();
    return true;
}

bool Profile::disableMod(std::string mod) {
    std::string fileContents = this->getTsvContents();
    for (int i = 0; i < fileContents.length()-mod.length(); ++i) {
        if (fileContents.substr(i,mod.length()) == mod) {
            fileContents[i + mod.length() + 1] = '0';
            break;
        }
    }
    std::ofstream fout("Profiles/" + this->name + "/mods.tsv");
    fout << fileContents;
    fout.close();
    return true;
}

bool Profile::removeMod(std::string mod) {
    std::string fileContents = this->getTsvContents();
    std::ofstream fout("Profiles/" + this->name + "/mods.tsv");
    for (int i = 0; i < fileContents.length()-mod.length(); ++i) {
        if (fileContents.substr(i,mod.length()) == mod) {
            fileContents = fileContents.substr(0,i-1) + fileContents.substr(i + mod.length() + 2);
            break;
        }
    }
    fout << fileContents;
    fout.close();
    return true;
}

std::vector<std::string> Profile::installMod(std::string mod, std::vector<std::string> previousMods) { // Returns list of mods that were installed
    Settings config;
    if (findInVector(previousMods, mod) == -1) {
        if (fileExists("Mod-Library/" + mod + ".depend")) {
            std::string dependency;
            std::ifstream fin("Mod-Library/" + mod + ".depend");
            while (std::getline(fin, dependency)) {
                if (fileExists("Mod-Library/" + dependency)) {
                    previousMods = this->installMod(dependency, previousMods);
                }
            }
        }
        for (auto const& folder : fsys::directory_iterator{"Mod-Library/" + mod}) {
            for (auto const& file : fsys::directory_iterator{folder.path().string()}) {
                copyFile(file.path().string(), config.getSetting("subnauticaDirectory") + "/BepInEx/" + folder.path().filename().string());
            }
        }
        previousMods.push_back(mod);
    }
    return previousMods;
}

bool Profile::loadProfile() {
    Settings config;
    if (this->name == "" || !fileExists("Mod-Library/BepInEx") || !fileExists("Mod-Library/Nautilus") || config.getSetting("subnauticaDirectory") == "") {
        return false;
    }

    for (auto const& file : fsys::directory_iterator{"Mod-Library/BepInEx"}) {
        copyFile(file.path().string(), config.getSetting("subnauticaDirectory"));
    }
    for (auto const& folder : fsys::directory_iterator{"Mod-Library/Nautilus"}) {
        for (auto const& file : fsys::directory_iterator{folder.path().string()}) {
            copyFile(file.path().string(), config.getSetting("subnauticaDirectory") + "/BepInEx/" + folder.path().filename().string());
        }
    }

    std::istringstream mods(this->getTsvContents());
    std::string mod;
    {
        std::vector<std::string> previousMods;
        while (std::getline(mods, mod)) {
            if (mod.back() == '1') {
                std::cout << "Made it. " << mod << std::endl;
                mod = mod.substr(0, mod.size() - 2);
                previousMods = this->installMod(mod, previousMods);
            }
        }
    }

    for (auto const& folder : fsys::directory_iterator{"Profiles/" + this->name}) {
        if (fsys::is_directory(folder.path()) && folder.path().filename().string() != "Previous-Logs") {
            for (auto const& file : fsys::directory_iterator{folder.path().string()}) {
                copyFile(file.path().string(), config.getSetting("subnauticaDirectory") + "/BepInEx/" + folder.path().filename().string());
            }
        }
    }
    return true;
}
bool Profile::unloadAllMods() {
    Settings config;
    if (config.getSetting("subnauticaDirectory") == "") {
        return false;
    }
    for (auto const& file : fsys::directory_iterator{"Mod-Library/BepInEx"}) {
        std::string fileToBeDeleted = config.getSetting("subnauticaDirectory") + '/' + file.path().filename().string();
        if (fileExists(fileToBeDeleted)) {
            deleteFile(fileToBeDeleted);
        }
    }
    return true;
}
bool Profile::saveProfile() {
    Settings config;
    if (config.getSetting("subnauticaDirectory") == "" || !fileExists(config.getSetting("subnauticaDirectory") + "/BepInEx/plugins")) {
        return false;
    }
    if (fileExists(config.getSetting("subnauticaDirectory") + "/BepInEx/cache")) {
        copyFile(config.getSetting("subnauticaDirectory") + "/BepInEx/cache", "Profiles/" + this->name);
    }
    if (fileExists(config.getSetting("subnauticaDirectory") + "/BepInEx/LogOutput.log")) {
        copyFile(config.getSetting("subnauticaDirectory") + "/BepInEx/LogOutput.log", "Profiles/" + this->name + "/Previous-Logs");
        renameFile("Profiles/" + this->name + "/Previous-Logs/LogOutput.log", "LogOutput-" + getDateTimeString() + ".log"); // LogOutput-hh_mm_ss-DD_MM_YYYY.log
    }
    copyFile(config.getSetting("subnauticaDirectory") + "/BepInEx/config", "Profiles/" + this->name);
    return true;
}
bool Profile::unloadProfile() {
    return (this->saveProfile() && this->unloadAllMods());
}
bool Profile::loadNewProfile(std::string newProfile) {
    Settings config;
    if (!fileExists("Profiles/" + newProfile) || !fileExists("Mod-Library/BepInEx") || !fileExists("Mod-Library/Nautilus") || config.getSetting("subnauticaDirectory") == "") {
        return false;
    }
    this->selectDifferentProfile(newProfile);
    this->unloadProfile();
    return this->loadProfile();
}

