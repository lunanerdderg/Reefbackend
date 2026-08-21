#ifndef PROFILE_H
#define PROFILE_H
#include "Settings.h"

class Profile {
    public:
        Profile(std::string nameInput="");
        virtual ~Profile();
        bool deleteProfile();
        bool isProfileSelected();
        bool changeProfile(std::string newName="");
        bool closeProfile();
        std::string getName();
        bool rename(std::string newName);
        void addMod(std::string);
        void disableMod(std::string);
        void removeMod(std::string);

    private:
        std::string name;
        bool profileExists();
        std::string getTsvContents();
        void makeProfile();
};

#endif // PROFILE_H
