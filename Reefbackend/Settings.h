#ifndef SETTINGS_H
#define SETTINGS_H
#include "consoleCommands.h"

class Settings {
    public:
        Settings();
        virtual ~Settings();
        void resetSettings();
        std::string getSubnauticaDirectory();
        std::string getSavesDirectory();
        unsigned short int changeSubnauticaDirectory(std::string);
        unsigned short int changeSubnauticaDirectory(unsigned short int);
        unsigned short int changeSavesDirectory(std::string);
        unsigned short int changeSavesDirectory(unsigned short int);

    private:
        std::string subnauticaDirectory;
        std::string savesDirectory;
        void readSettings();
        void writeToSettings();
};

#endif // SETTINGS_H
