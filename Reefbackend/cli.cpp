#include "cli.h"

bool cli(bool devMode) {
    Settings settings;
    Profile curProfile("");
    unsigned int index = 0;
    unsigned int index2 = 0;
    bool running = true;
    std::string command;
    unsigned short int result;
    createModLibraryFolder();
    while (running) {
        std::getline(std::cin, command);
        std::cout << "-------\n";
        if (command.length() == 0) {}
        else if (command.substr(0,7) == "getPath" && devMode) {
            std::cout << "Path:\n" << getPath() << std::endl;
        }
        else if (command.substr(0,22) == "createModLibraryFolder" && devMode) {
            if (createModLibraryFolder()) {
                std::cout << "Mod-Library folder successfully created!\n";
            }
            else {
                std::cout << "Mod-Library already exists.\n";
            }

        }
        else if (command.substr(0,12) == "dependencies") { // Windows probably has none? Unsure
            if (commandDoesNotExist("curl")) {
                std::cout << "curl is necessary and needs to be installed through your package manager!!!\n";
            }
            else {
                std::cout << "curl is installed\n";
            }
            if (commandDoesNotExist("wget")) {
                std::cout << "wget is necessary and needs to be installed through your package manager!!!\n";
            }
            else {
                std::cout << "wget is installed\n";
            }
            if (commandDoesNotExist("grep")) {
                std::cout << "grep is necessary and needs to be installed through your package manager!!!\n";
            }
            else {
                std::cout << "grep is installed\n";
            }
            if (commandDoesNotExist("unzip")) {
                std::cout << "unzip is necessary and needs to be installed through your package manager!!!\n";
            }
            else {
                std::cout << "unzip is installed\n";
            }
            if (commandDoesNotExist("tar")) {
                std::cout << "tar is not installed, but unnecessary unless the mod is compressed through .tar\n";
            }
            else {
                std::cout << "tar is installed\n";
            }
            if (commandDoesNotExist("unrar")) {
                std::cout << "unrar-free is not installed, but unnecessary unless the mod is compressed through .rar\n";
            }
            else {
                std::cout << "unrar-free is installed\n";
            }
            if (commandDoesNotExist("7z")) {
                std::cout << "7zip is not installed, but unnecessary unless the mod is compressed through .7z\n";
            }
            else {
                std::cout << "7zip is installed\n";
            }
        }


        // ------------------------------------------------------------------------------------------------------------------------------------------------------------

        // =========================================================================================================================================    consoleCommands

        // ------------------------------------------------------------------------------------------------------------------------------------------------------------


        else if (command.substr(0,28) == "haveAllNecessaryDependencies") {
            if (haveAllNecessaryDependencies()) {
                std::cout << "All necessary dependencies are installed. Run 'dependencies' to see if optional dependencies installed\n";
            }
            else {
                std::cout << "Necessary dependencies are NOT installed. Please run 'dependencies' to see what you're missing.\n";
            }
        }
        else if (command.substr(0,10) == "fileExists" && devMode) {
            index = readTo(command, '"', 12)-1;
            std::string location = command.substr(12, index - 11);
            if (fileExists(location)) {
                std::cout << "File '" << location << "' exists.\n";
            }
            else {
                std::cout << "File does not exist.\n";
            }
        }
        else if (command.substr(0,19) == "commandDoesNotExist" && devMode) {
            index = readTo(command, '"', 21)-1;
            std::string temp = command.substr(21, index - 20);
            if (commandDoesNotExist(temp)) {
                std::cout << "Command '" << temp << "' does not exist.\n";
            }
            else {
                std::cout << "Command '" << temp << "' exists.\n";
            }
        }
        else if (command.substr(0,9) == "inProject" && devMode) {
            index = readTo(command, '"', 11)-1;
            std::string temp = command.substr(11, index - 10);
            if (inProject(temp)) {
                std::cout << "File '" << temp << "' is in project.\n";
            }
            else {
                std::cout << "File '" << temp << "' is NOT in project.\n";
            }
        }
        else if (command.substr(0,14) == "findSubnautica") {
            result = findSubnautica();
            if (result == 1) {
                std::cout << "Subnautica found at Steam.\n";
            }
            else if (result == 2) {
                std::cout << "Subnautica found at Heroic.\n";
            }
            else if (result == 3) {
                std::cout << "Subnautica found at Lutris.\n"; // Epic on Windows
            }
            else {
                std::cout << "Subnautica not found.\n";
            }
        }

        else if (command.substr(0,8) == "copyFile" && devMode) {
            index = readTo(command, '"', 10)-1;
            std::string fileName = command.substr(10, index - 9);
            index2 = readTo(command, '"', index + 4)-1;
            std::string destination = command.substr(index + 4, index2 - index - 3);
            if (copyFile(fileName, destination)) {
                std::cout << "File '" << fileName << "' has been copied to '" + destination + "'.\n";
            }
            else {
                std::cout << "File '" << fileName << "' failed to copy.\n";
            }
        }
        else if (command.substr(0,8) == "moveFile" && devMode) {
            index = readTo(command, '"', 10)-1;
            std::string fileName = command.substr(10, index - 9);
            index2 = readTo(command, '"', index + 4)-1;
            std::string destination = command.substr(index + 4, index2 - index - 3);
            if (moveFile(fileName, destination)) {
                std::cout << "File '" << fileName << "' has been moved to '" + destination + "'.\n";
            }
            else {
                std::cout << "File '" << fileName << "' failed to move.\n";
            }
        }
        else if (command.substr(0,10) == "renameFile" && devMode) {
            index = readTo(command, '"', 12)-1;
            std::string fileName = command.substr(12, index - 11);
            index2 = readTo(command, '"', index + 4)-1;
            std::string newName = command.substr(index + 4, index2 - index - 3);
            if (renameFile(fileName, newName)) {
                std::cout << "File '" << fileName << "' has been renamed to '" + newName + "'.\n";
            }
            else {
                std::cout << "Rename failed.\n";
            }
        }
        else if (command.substr(0,13) == "makeDirectory" && devMode) {
            index = readTo(command, '"', 15)-1;
            std::string temp = command.substr(15, index - 14);
            if (makeDirectory(temp)) {
                std::cout << "Directory '" << temp << "' has been created.\n";
            }
            else {
                std::cout << "Directory '" << temp << "' has NOT been created.\n";
            }
        }
        else if (command.substr(0,10) == "deleteFile" && devMode) {
            index = readTo(command, '"', 12)-1;
            std::string temp = command.substr(12, index - 11);
            if (deleteFile(temp)) {
                std::cout << "File '" << temp << "' has been deleted.\n";
            }
            else {
                std::cout << "File '" << temp << "' has NOT been deleted.\n";
            }
        }
        else if (command.substr(0,5) == "unzip" && devMode) {
            index = readTo(command, '"', 7)-1;
            result = unzip(command.substr(7, index-6),command.substr(index+4,command.length()-index-5));
            if (result == 1) {
                std::cout << "ERROR: Could not decompress rar. Please install unrar-free with your native package manager or unrar at 'https://www.rarlab.com/rar_add.htm'" << std::endl; // New message for Window
            }
            else if (result == 7) {
                std::cout << "ERROR: Could not decompress 7z. Please install p7zip-full with your native package manager or 7zip at 'https://7-zip.org/download.html'" << std::endl;
            }
            else {
                std::cout << "Unzipped '" << command.substr(7, index-6) << "' to '" << command.substr(index+4,command.length()-index-5) << std::endl;
            }
        }

        else if (command.substr(0,21) == "dlLatestGithubRelease" && devMode) { // TEST: dlLatestGithubRelease "SubnauticaModding/Nautilus" "Nautilus_SN.STABLE_.zip" "$HOME/Documents/Programming/C++/Reefbackend/.templates MEGA_EXCLUDED/test" 1 1 "-pre"
            index = readTo(command, '"', 23)-1;
            std::string repo = command.substr(23, index - 22);
            index2 = readTo(command, '"', index + 4)-1;
            std::string fileName = command.substr(index + 4, index2 - index - 3);
            index = readTo(command, '"', index2 + 4)-1;
            std::string location = command.substr(index2 + 4, index - index2 - 3);
            unsigned short int includePreReleases = false;
            unsigned short int suffix = false;
            std::string removeStr = "";
            if (command.length() > index + 3) {
                includePreReleases = command.at(index + 3) != '0';
            }
            if (command.length() > index + 5) {
                suffix = command.at(index + 5) != '0';
            }
            if (command.length() > index + 8) {
                removeStr = command.substr(index + 8, command.length() - index - 9);
            }
            if (dlLatestGithubRelease(repo, fileName, location, includePreReleases, suffix, removeStr)) {
                std::cout << '\'' << fileName << "' successfully installed to '" << location << "'\n";
            }
            else {
                std::cout << "Installation failed\n";
            }
        }
        else if (command.substr(0,9) == "dlBepInEx") {
            index = readTo(command, '"', 11)-1;
            std::string location = command.substr(11, index - 10);
            if (dlBepInEx(location)) {
                std::cout << "\nBepInEx successfully downloaded.\nNow open Subnautica, quit from main menu, and run 'installBepInEx' to get started!\n";
            }
            else {
                std::cout << "\nBepInEx already installed.\n";
            }
        }
        else if (command.substr(0,14) == "installBepInEx") {
            std::string location;
            if (command.length() > 16) {
                index = readTo(command, '"', 16)-1;
                location = command.substr(16, index - 15);
            }
            else {
                location = settings.getSubnauticaDirectory();
            }

            std::ifstream fin("Mod-List.tsv");
            std::string repo;
            std::string fileName;
            std::string finalName;
            std::string includeAllReleases;
            std::string suffix;
            std::string removeStr;
            std::string temp;
            for (short int i = 0; i < 2; ++i) {
                std::getline(fin, repo, '\t');
                std::getline(fin, fileName, '\t');
                std::getline(fin, finalName, '\t');
                std::getline(fin, includeAllReleases, '\t');
                std::getline(fin, suffix, '\t');
                std::getline(fin, removeStr, '\t');
                std::getline(fin, temp);
                std::cout << repo << ", " << fileName << ", " << finalName << ", " << includeAllReleases << ", " << suffix << ", " << removeStr << std::endl;
                addToLibrary(repo, fileName, finalName, includeAllReleases.at(0) == '1', suffix.at(0) == '1', removeStr);
            }

            if (installBepInEx(location)) {
                std::cout << "\nBepInEx successfully installed!\n";
            }
            else {
                std::cout << "\nBepInEx already installed.\n";
            }
        }
        else if (command.substr(0,12) == "addToLibrary") {
            index = readTo(command, '"', 14)-1;
            std::string filePath = command.substr(14, index - 13);
            std::string finalName;
            if (command.length() > index + 4) {
                index2 = readTo(command, '"', index + 4)-1;
                finalName = command.substr(index + 4, index2 - index - 3);
            }
            else {
                finalName = "";
            }
            if (addToLibrary(filePath, finalName)) {
                std::cout << '\'' << fsys::path(filePath).stem().string() << "' successfully added to your library!\n";
            }
            else {
                std::cout << "Installation failed.\n";
            }
        }
        else if (command.substr(0,14) == "addToLibraryGh" && devMode) {
            index = readTo(command, '"', 16)-1;
            std::string repo = command.substr(16, index - 15);
            index2 = readTo(command, '"', index + 4)-1;
            std::string fileName = command.substr(index + 4, index2 - index - 3);
            index = readTo(command, '"', index2 + 4)-1;
            std::string finalName = command.substr(index2 + 4, index - index2 - 3);
            unsigned short int includePreReleases = false;
            unsigned short int suffix = false;
            std::string removeStr = "";
            if (command.length() > index + 3) {
                includePreReleases = command.at(index + 3) != '0';
            }
            if (command.length() > index + 5) {
                suffix = command.at(index + 5) != '0';
            }
            if (command.length() > index + 8) {
                removeStr = command.substr(index + 8, command.length() - index - 9);
            }
            if (addToLibrary(repo, fileName, finalName, includePreReleases, suffix, removeStr)) {
                std::cout << '\'' << finalName << "' successfully added to your library!\n";
            }
            else {
                std::cout << "Installation failed.\n";
            }
        }
        else if (command.substr(0,19) == "listInstallableMods") {
            std::ifstream fin("Mod-List.tsv");
            std::string tempText;
            while (std::getline(fin, command)) {
                tempText = "";
                short int counter = 0;
                for (int i = 0; i < command.size() && counter < 3; ++i) {
                    if (command.at(i) == '\t') {
                        ++counter;
                    }
                    else if (counter == 2) {
                        tempText += command.at(i);
                    }
                }
                std::cout << "\n- " << tempText << std::endl;
                tempText = "";
                for (int i = command.size() - 1; i >= 0 && command.at(i) != '\t'; --i) {
                    tempText = command.at(i) + tempText;
                }
                counter = 0;
                for (int i = 0; i < tempText.size(); ++i) {
                    std::cout << tempText.at(i);
                    ++counter;
                    if (counter > 50 && tempText.at(i) == ' ') {
                        std::cout << std::endl;
                        counter = 0;
                    }
                }
                std::cout << std::endl;
            }
        }
        else if (command.substr(0,7) == "install") {}

        else if (command.substr(0,7) == "getMods") {
            command = getMods();
            if (command == "") {
                std::cout << "There are no mods in your library.\n";
            }
            else {
                std::cout << "The mods are:\n\n" << command;
            }
        }
        else if (command.substr(0,11) == "getProfiles") {
            command = getProfiles();
            if (command == "") {
                std::cout << "There are no profiles.\n";
            }
            else {
                std::cout << "The profiles are:\n\n" << command;
            }
        }


        // ------------------------------------------------------------------------------------------------------------------------------------------------------------

        // =========================================================================================================================================    Settings

        // ------------------------------------------------------------------------------------------------------------------------------------------------------------


        else if (command.substr(0,13) == "resetSettings") {
            settings.resetSettings();
            std::cout << "Settings reset to defaults.\n";
        }
        else if (command.substr(0,26) == "autosetSubnauticaDirectory") {
            index = findSubnautica();
            if (index != 0 && index <=3) {
                settings.changeSubnauticaDirectory(index);
                settings.changeSavesDirectory(index);
            }
            if (index == 1) {
                std::cout << "Subnautica directory set to Steam.\n";
            }
            else if (index == 2) {
                std::cout << "Subnautica directory set to Heroic.\n";
            }
            else if (index == 3) {
                std::cout << "Subnautica directory set to Lutris.\n"; // Windows: std::cout << "Subnautica directory set to Epic.\n";
            }
            else {
                std::cout << "Subnautica directory could not be found.\n";

            }
        }
        else if (command.substr(0,25) == "getSubnauticaDirectory") {
            std::cout << "Current Subnautica directory is '" << settings.getSubnauticaDirectory() << "'\n";
        }
        else if (command.substr(0,25) == "getSavesDirectory") {
            std::cout << "Current saves directory is '" << settings.getSavesDirectory() << "'\n";
        }
        else if (command.substr(0,25) == "changeSubnauticaDirectory") {
            index = readTo(command, '"', 27)-1;
            std::string location = command.substr(27, index - 26);
            settings.changeSubnauticaDirectory(location);
            std::cout << "Subnautica directory set to '" << location << "'\n";
        }
        else if (command.substr(0,20) == "changeSavesDirectory" && devMode) {
            index = readTo(command, '"', 22)-1;
            std::string location = command.substr(22, index - 21);
            settings.changeSavesDirectory(location);
            std::cout << "Saves directory set to '" << location << "'\n";
            std::cout << "SAVE FUNCTIONALITY DOES NOT EXIST YET!\n";
        }


        // ------------------------------------------------------------------------------------------------------------------------------------------------------------

        // =========================================================================================================================================    Profiles

        // ------------------------------------------------------------------------------------------------------------------------------------------------------------


        else if (command.substr(0,11) == "openProfile") {
            index = readTo(command, '"', 13)-1;
            std::string name = command.substr(13, index - 12);
            curProfile.changeName(name);
            std::cout << "Profile '" << name << "' opened.\n";
        }
        else if (command.substr(0,12) == "closeProfile") {
            curProfile.closeProfile();
            std::cout << "Selected profile closed.\n";
        }
        else if (command.substr(0,14) == "getProfileName") {
            std::cout << "Selected profile is named '" << curProfile.getName() << "'\n";
        }
        else if (command.substr(0,13) == "changeProfile") {
            index = readTo(command, '"', 15)-1;
            std::string name = command.substr(15, index - 14);
            curProfile.changeName(name);
            std::cout << "Selected profile changed to '" << name << "'\n";
        }


        // ------------------------------------------------------------------------------------------------------------------------------------------------------------

        // =========================================================================================================================================    End

        // ------------------------------------------------------------------------------------------------------------------------------------------------------------


        else if (command.at(0) == 'q') {
            running = false;
        }
        else {
            std::cout << "Command not recognized.\n";
        }
        std::cout << "==============\n" << std::endl;
    }
    return true;
}

