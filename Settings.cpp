#include "Settings.h"

Settings::Settings() {}

Settings::~Settings() {}

void Settings::resetAllSettings() {
    std::ifstream  defaultSettingsFile("default-settings.tsv", std::ios::binary);
    std::ofstream  settingsFile("settings.tsv",   std::ios::binary);
    settingsFile << defaultSettingsFile.rdbuf();
    defaultSettingsFile.close();
    settingsFile.close();
    this->changeSubnauticaDirectory(findSubnautica());
    this->changeSavesDirectory(findSubnautica());
}
std::string Settings::resetSetting(std::string settingString) {
    return this->resetSettingFromIndex(getSettingIndex(settingString));
}
std::string Settings::getSetting(std::string settingString) {
    return this->getSettingFromIndex(getSettingIndex(settingString));
}
std::string Settings::changeSetting(std::string settingString, std::string newSetting) {
    return this->changeSettingFromIndex(getSettingIndex(settingString), newSetting);
}

void Settings::changeSubnauticaDirectory(unsigned short int location) {
    if (location >= 4) {
        return;
    }
    std::string subnauticaDirectory = getHomeDirectory();
    if (location == 0) {
        subnauticaDirectory = "";
    }
    else if (location == 1) {
        subnauticaDirectory += "/.local/share/Steam/steamapps/common/Subnautica/"; // Windows: C:\\\\Program Files (x86)\\Steam\\steamapps\\common\\Subnautica
    }
    else if (location == 2) {
        subnauticaDirectory += "/Games/Heroic/Subnautica/"; // Windows: C:\\\\Users\\USERNAME\\Games\\Heroic\\Subnautica
    }
    else if (location == 3) {
        subnauticaDirectory += "/.lutris/epic-games-store/drive_c/Program Files/Epic Games/Subnautica/"; // Windows (Epic): C:\\\\Program Files\\Epic Games\\Subnautica
    }
    this->changeSettingFromIndex(getSettingIndex("subnauticaDirectory"), subnauticaDirectory);
}
void Settings::changeSavesDirectory(unsigned short int location) {
    if (location >= 4) {
        return;
    }
    std::string savesDirectory = getHomeDirectory();
    if (location == 0) {
        savesDirectory = "";
    }
    else if (location == 1) {
        savesDirectory += "/.local/share/Steam/steamapps/common/Subnautica/SNAppData/"; // Windows: C:\\\\Program Files (x86)\\Steam\\steamapps\\common\\Subnautica\\SNAppData
    }
    else if (location == 2) { // BOOKMARK
        savesDirectory += "/Games/Heroic/Subnautica/SNAppData/"; // Windows: C:\\\\Users\\h\\Games\\Heroic\\Subnautica\\SNAppData
    }
    else if (location == 3) {
        savesDirectory += "/.lutris/epic-games-store/drive_c/Users/*/AppData/LocalLow/Unknown Worlds/Subnautica/Subnautica/"; // Windows (Epic): C:\\\\Users\\h\\AppData\\LocalLow\\Unknown Worlds\\Subnautica\\Subnautica
    }
    this->changeSettingFromIndex(this->getSettingIndex("savesDirectory"), savesDirectory);
}

unsigned int Settings::getSettingIndex(std::string settingString) {
    if (settingString == "subnauticaDirectory") {return 0;}
    if (settingString == "saveDirectory" || settingString == "savesDirectory") {return 1;}
    if (settingString == "defaultProfile") {return 2;}
    return -1;
}

std::string Settings::resetSettingFromIndex(unsigned int settingIndex) {
    std::string originalSetting;
    if (settingIndex == this->getSettingIndex("subnauticaDirectory")) {
        originalSetting = this->getSettingFromIndex(settingIndex);
        this->changeSubnauticaDirectory(findSubnautica());
    }
    else if (settingIndex == this->getSettingIndex("savesDirectory")) {
        originalSetting = this->getSettingFromIndex(settingIndex);
        this->changeSavesDirectory(findSubnautica());
    }
    else {
        std::vector<std::string> settingsVector = this->getSettings();
        originalSetting = settingsVector.at(settingIndex);
        settingsVector[settingIndex] = getSettingFromIndex(settingIndex, true);
        this->writeToSettings(settingsVector);
    }
    return originalSetting;
}

std::string Settings::getSettingFromIndex(unsigned int settingsIndex, bool defaultSettings) {
    std::string fileName = "settings.tsv";
    if (defaultSettings) {
        fileName = "default-settings.tsv";
    }
    if (!fileExists(fileName)) { // Function to create "default-settings.tsv"
        this->resetAllSettings();
    }
    std::string setting;
    std::ifstream fin(fileName.c_str());
    for (unsigned int i = 0; std::getline(fin, setting); ++i) {
        if (i == settingsIndex) {
            return setting.substr(0, readTo(setting));
        }
    }
    fin.close();
    return "";
}
std::vector<std::string> Settings::getSettings(bool defaultSettings) { // Private
    std::string fileName = "settings.tsv";
    if (defaultSettings) {
        fileName = "default-settings.tsv";
    }
    if (!fileExists(fileName)) { // Function to create "default-settings.tsv"
        this->resetAllSettings();
    }
    std::vector<std::string> result;
    std::string setting;
    std::ifstream fin(fileName.c_str());
    while (std::getline(fin, setting)) {
        result.push_back(setting.substr(0, readTo(setting)));
    }
    fin.close();
    return result;
}

std::string Settings::changeSettingFromIndex(unsigned int settingIndex, std::string newSetting) {
    std::vector<std::string> settingsVector = this->getSettings();
    std::string originalSetting = settingsVector.at(settingIndex);
    settingsVector[settingIndex] = newSetting;
    this->writeToSettings(settingsVector);
    return originalSetting;
}

void Settings::writeToSettings(std::vector<std::string> settingsVector) {
    if (!fileExists("settings.tsv")) {
        this->resetAllSettings();
    }
    std::vector<std::string> settingsDescriptions = {"Subnautica directory", "Subnautica saves directory", "Default Profile (vanilla if blank)"};
    std::string setting;
    std::ofstream fout("settings.tsv");
    for (unsigned int i = 0; i < settingsVector.size(); ++i) {
        fout << settingsVector.at(i) << "\t" << settingsDescriptions.at(i) << std::endl;
    }
    fout.close();
}
