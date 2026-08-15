#include "Settings.h"

void Settings::resetSettings() {
    std::ifstream  defaultSettingsFile("default-settings.tsv", std::ios::binary);
    std::ofstream  settingsFile("settings.tsv",   std::ios::binary);
    settingsFile << defaultSettingsFile.rdbuf();
    this->readSettings();
    defaultSettingsFile.close();
    settingsFile.close();
}
void Settings::readSettings() {
    if (!inProject("settings.tsv")) {
        this->resetSettings();
    }
    std::string setting;
    std::ifstream fin("settings.tsv");
    std::getline(fin, setting);
    this->subnauticaDirectory = setting.substr(0, readTo(setting));
    std::getline(fin, setting);
    this->savesDirectory = setting.substr(0, readTo(setting));
    fin.close();
}
Settings::Settings() {
    readSettings();
}

Settings::~Settings() {
    writeToSettings();
}

std::string Settings::getSubnauticaDirectory() {
    this->readSettings();
    return this->subnauticaDirectory;
}
std::string Settings::getSavesDirectory() {
    this->readSettings();
    return this->savesDirectory;
}


unsigned short int Settings::changeSubnauticaDirectory(std::string location) {
    this->subnauticaDirectory = location;
    writeToSettings();
    return 4;
}
unsigned short int Settings::changeSubnauticaDirectory(unsigned short int location) {
    if (location >= 4) {
        return 0;
    }
    if (location == 1) {
        this->subnauticaDirectory = "$HOME/.local/share/Steam/steamapps/common/Subnautica/"; // Windows: C:\\\\Program Files (x86)\\Steam\\steamapps\\common\\Subnautica
    }
    else if (location == 2) {
        this->subnauticaDirectory = "$HOME/Games/Heroic/Subnautica/"; // Windows: C:\\\\Users\\USERNAME\\Games\\Heroic\\Subnautica
    }
    else if (location == 3) {
        this->subnauticaDirectory = "$HOME/.lutris/epic-games-store/drive_c/Program Files/Epic Games/Subnautica/"; // Windows (Epic): C:\\\\Program Files\\Epic Games\\Subnautica
    }
    if (location == 0 && location <= 3) {
        writeToSettings();
    }
    return location;
}
unsigned short int Settings::changeSavesDirectory(std::string location) {
    this->savesDirectory = location;
    writeToSettings();
    return 4;
}
unsigned short int Settings::changeSavesDirectory(unsigned short int location) {
    if (location >= 4) {
        return 0;
    }
    if (location == 1) {
        this->savesDirectory = "$HOME/.local/share/Steam/steamapps/common/Subnautica/SNAppData/"; // Windows: C:\\\\Program Files (x86)\\Steam\\steamapps\\common\\Subnautica\\SNAppData
    }
//    else if (location == 2) {
//        this->savesDirectory = "$HOME/Games/Heroic/Subnautica/SNAppData/"; // Windows: C:\\\\Users\\h\\Games\\Heroic\\Subnautica\\SNAppData
//    }
//    else if (location == 3) {
//        this->savesDirectory = "$HOME/.lutris/epic-games-store/drive_c/Users/*/AppData/LocalLow/Unknown Worlds/Subnautica/Subnautica/"; // Windows (Epic): C:\\\\Users\\h\\AppData\\LocalLow\\Unknown Worlds\\Subnautica\\Subnautica
//    }
//    if (location != 0 && location <= 3) {
    if (location == 1) {
        writeToSettings();
    }
    return location;
}

void Settings::writeToSettings() {
    if (!inProject("settings.tsv")) {
        this->resetSettings();
    }
    std::string setting;
    std::ofstream fout("settings.tsv");
    fout << this->subnauticaDirectory << "\tSubnautica directory" << std::endl;
    fout << this->savesDirectory << "\tSubnautica saves directory" << std::endl;
    fout.close();
}
