#include "Profile.h"



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
    std::ofstream fout("plugins.tsv");
    fout << "Nautilus\t1\nBepInEx Tweaks\t1";
    fout.close();
}

std::string Profile::getTsvContents() {
    std::string fileContents = "";
    std::string line;
    while (std::getLine(fin, line)) {
        fileContents += line;
        fileContents += '\n';
    }
    return fileContents;
}

bool Profile::addMod(std::string mod) {
    std::ofstream fout("plugins.tsv");
    fout << this->getTsvContents() << mod << "\t1;
    fout.close();
}

bool Profile::disableMod(std::string mod) {
    std::string fileContents = this->getTsvContents();
    std::ofstream fout("plugins.tsv");
    for (int i = 0; i < fileContents.length()-mod.length(); ++i) {
        if (fileContents.substr(i,mod.length()) == mod) {
            fileContents[i + mod.length() + 1] = '0';
            break;
        }
    }
    fout << fileContents;
    fout.close();
}

Profile::Profile(std::string nameInput) { // Constructor assumes BepInEx already installed. Require user to install BepInEx first
    this->name = nameInput;
    if (this->name != "") {}
    if (!profileExists()) {
        makeProfile();
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
    return true;
}

bool Profile::closeProfile() {
    this->name = "";
    return true;
}
