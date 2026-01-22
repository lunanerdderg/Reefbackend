#ifndef PROFILE_H
#define PROFILE_H
#include "Settings.h"

class Profile {
    public:
        Profile(std::string nameInput="");
        virtual ~Profile();
        bool profileSelected();
        std::string getName();
        bool changeName(std::string newName="");
        bool closeProfile();
        bool addMod(std::string);
        bool disableMod(std::string);

    private:
        std::string name;
        bool profileExists();
        std::string getTsvContents();
        void makeProfile();
};

#endif // PROFILE_H
