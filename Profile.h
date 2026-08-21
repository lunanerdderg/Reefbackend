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
        bool saveProfile();
        bool unloadProfile();
        bool unloadAllMods();
        bool loadNewProfile(std::string);

    private:
        std::string name;
        bool profileExists();
        std::string getTsvContents();
        bool makeProfile();
};

#endif // PROFILE_H
