#include "Profile.h"

// Function to install Profile to Subnautica directory

bool Profile::profileExists() {
    for (auto const& folder : fsys::directory_iterator{getPath() + "/Profiles/"}) {
        if (folder.path().filename().string() == this->name) {
            return true;
        }
    }
    return false;
}

void Profile::makeProfile() {
    makeDirectory(getPath() + "/Profiles/" + this->name + "/config");
    makeDirectory(getPath() + "/Profiles/" + this->name + "/patchers");
    std::ofstream fout(getPath() + "/Profiles/" + this->name + "/plugins.tsv");
    fout << "Nautilus\t1\nBepInEx Tweaks\t1";
    fout.close();
}

std::string Profile::getTsvContents() {
    std::ifstream fin(getPath() + "/Profiles/" + this->name + "/plugins.tsv");
    std::string fileContents = "";
    std::string line;
    while (std::getline(fin, line)) {
        fileContents += line;
        fileContents += '\n';
    }
    return fileContents;
}

void Profile::addMod(std::string mod) {
    std::string contents = this->getTsvContents();
    std::ofstream fout(getPath() + "/Profiles/" + this->name + "/plugins.tsv");
    fout << contents << mod << "\t1";
    fout.close();
}

void Profile::disableMod(std::string mod) {
    std::string fileContents = this->getTsvContents();
    std::ofstream fout(getPath() + "/Profiles/" + this->name + "/plugins.tsv");
    for (int i = 0; i < fileContents.length()-mod.length(); ++i) {
        if (fileContents.substr(i,mod.length()) == mod) {
            fileContents[i + mod.length() + 1] = '0';
            break;
        }
    }
    fout << fileContents;
    fout.close();
}

void Profile::removeMod(std::string mod) {
    std::string fileContents = this->getTsvContents();
    std::ofstream fout(getPath() + "/Profiles/" + this->name + "/plugins.tsv");
    for (int i = 0; i < fileContents.length()-mod.length(); ++i) {
        if (fileContents.substr(i,mod.length()) == mod) {
            fileContents = fileContents.substr(0,i-1) + fileContents.substr(i + mod.length() + 2);
            break;
        }
    }
    fout << fileContents;
    fout.close();
}

Profile::Profile(std::string nameInput) { // Constructor assumes BepInEx already installed. Require user to install BepInEx first
    this->name = nameInput;
    if (this->name != "" && !this->profileExists()) {
        this->makeProfile();
    }
}

Profile::~Profile() {}

bool Profile::profileSelected() {
    return this->name != "";
}

std::string Profile::getName() {
    return this->name;
}

bool Profile::changeName(std::string newName) {
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
