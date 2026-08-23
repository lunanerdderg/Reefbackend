#ifndef PROFILE_H
#define PROFILE_H
#include "Settings.h"

class Profile {
    public:
        Profile(std::string nameInput="");
        virtual ~Profile();
        bool deleteProfile();
        bool isProfileSelected();
        bool selectDifferentProfile(std::string newName="");
        bool closeProfile();
        std::string getName();
        bool rename(std::string);

        bool addMod(std::string);
        bool disableMod(std::string);
        bool removeMod(std::string);

        bool loadProfile();
        bool unloadAllMods();
        bool saveProfile();
        bool unloadProfile();
        bool loadNewProfile(std::string);
        bool changeDefaultProfile(bool autoLoad=true);
        bool changeDefaultProfile(std::string profile, bool autoLoad=true);


    private:
        std::string name;
        bool profileExists();
        bool profileExists(std::string);
        std::string getTsvContents();
        bool makeProfile();
        std::vector<std::string> installMod(std::string, std::vector<std::string>);
};

#endif // PROFILE_H
