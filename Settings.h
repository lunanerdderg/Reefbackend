#ifndef SETTINGS_H
#define SETTINGS_H
#include "consoleCommands.h"

class Settings {
    public:
        Settings();
        virtual ~Settings();
        void resetAllSettings();
        std::string resetSetting(std::string);
        std::string getSetting(std::string);
        std::string changeSetting(std::string, std::string);

        void changeSubnauticaDirectory(unsigned short int);
        void changeSavesDirectory(unsigned short int);
//        bool changeDefaultProfile(std::string);

    private:
        unsigned int getSettingIndex(std::string);
        std::string resetSettingFromIndex(unsigned int);
        std::string getSettingFromIndex(unsigned int settingsIndex, bool defaultSettings=false);
        std::vector<std::string> getSettings(bool defaultSettings=false);
        std::string changeSettingFromIndex(unsigned int, std::string);
        void writeToSettings(std::vector<std::string>);
};

#endif // SETTINGS_H
