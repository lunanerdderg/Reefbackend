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

    private:
        std::string name;
        bool profileExists();
        void makeProfile();
};

#endif // PROFILE_H
