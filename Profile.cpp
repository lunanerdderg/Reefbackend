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

bool Profile::changeProfile(std::string newName) {
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

void Profile::makeProfile() {
    makeDirectory("Profiles/" + this->name + "/cache");
    makeDirectory("Profiles/" + this->name + "/config");
    makeDirectory("Profiles/" + this->name + "/patchers");
    makeDirectory("Profiles/" + this->name + "/Previous-Logs");
    std::ofstream fout("Profiles/" + this->name + "/plugins.tsv");
    fout << "";
    fout.close();
}

std::string Profile::getTsvContents() {
    std::ifstream fin("Profiles/" + this->name + "/plugins.tsv");
    return std::string(std::istreambuf_iterator<char>(fin), std::istreambuf_iterator<char>());;
}

void Profile::addMod(std::string mod) {
    std::string contents = this->getTsvContents();
    std::ofstream fout("Profiles/" + this->name + "/plugins.tsv");
    if (contents != "") {
        fout << contents << std::endl;
    }
    fout << mod << "\t1";
    fout.close();
}

void Profile::disableMod(std::string mod) {
    std::string fileContents = this->getTsvContents();
    for (int i = 0; i < fileContents.length()-mod.length(); ++i) {
        if (fileContents.substr(i,mod.length()) == mod) {
            fileContents[i + mod.length() + 1] = '0';
            break;
        }
    }
    std::ofstream fout("Profiles/" + this->name + "/plugins.tsv");
    fout << fileContents;
    fout.close();
}

void Profile::removeMod(std::string mod) {
    std::string fileContents = this->getTsvContents();
    std::ofstream fout("Profiles/" + this->name + "/plugins.tsv");
    for (int i = 0; i < fileContents.length()-mod.length(); ++i) {
        if (fileContents.substr(i,mod.length()) == mod) {
            fileContents = fileContents.substr(0,i-1) + fileContents.substr(i + mod.length() + 2);
            break;
        }
    }
    fout << fileContents;
    fout.close();
}
