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

bool Profile::loadProfile() {
    Settings config;
    if (this->name == "" || !fileExists("Mod-Library/BepInEx") || !fileExists("Mod-Library/Nautilus") || config.getSubnauticaDirectory() == "") {
        return false;
    }

    for (auto const& file : fsys::directory_iterator{"Mod-Library/BepInEx"}) {
        copyFile(file.path().string(), config.getSubnauticaDirectory());
    }
    for (auto const& folder : fsys::directory_iterator{"Mod-Library/Nautilus"}) {
        for (auto const& file : fsys::directory_iterator{folder.path().string()}) {
            copyFile(file.path().string(), config.getSubnauticaDirectory() + "/BepInEx/" + folder.path().filename().string());
        }
    }

    std::istringstream mods(this->getTsvContents());
    std::string mod;
    while (std::getline(mods, mod)) {
        if (mod.back() == '1') {
            mod = mod.substr(0, mod.size() - 2);
            for (auto const& folder : fsys::directory_iterator{"Mod-Library/" + mod}) {
                for (auto const& file : fsys::directory_iterator{folder.path().string()}) {
                    copyFile(file.path().string(), config.getSubnauticaDirectory() + "/BepInEx/" + folder.path().filename().string());
                }
            }
        }
    }

    for (auto const& folder : fsys::directory_iterator{"Profiles/" + this->name}) {
        if (fsys::is_directory(folder.path())) {
            for (auto const& file : fsys::directory_iterator{folder.path().string()}) {
                copyFile(file.path().string(), config.getSubnauticaDirectory() + "/BepInEx/" + folder.path().filename().string());
            }
        }
    }
    return true;
}
bool Profile::unloadAllMods() {
    Settings config;
    if (config.getSubnauticaDirectory() == "") {
        return false;
    }
    for (auto const& file : fsys::directory_iterator{"Mod-Library/BepInEx"}) {
        std::string fileToBeDeleted = config.getSubnauticaDirectory() + '/' + file.path().filename().string();
        if (fileExists(fileToBeDeleted)) {
            deleteFile(fileToBeDeleted);
        }
    }
    return true;
}
bool Profile::saveProfile() { // BOOKMARK
    return true;
}
bool Profile::unloadProfile() {
    return (this->saveProfile() && this->unloadAllMods());
}
bool Profile::loadNewProfile(std::string newProfile) {
    Settings config;
    if (!fileExists("Profiles/" + newProfile) || !fileExists("Mod-Library/BepInEx") || !fileExists("Mod-Library/Nautilus") || config.getSubnauticaDirectory() == "") {
        return false;
    }
    this->selectDifferentProfile(newProfile);
    this->unloadProfile();
    return this->loadProfile();
}

