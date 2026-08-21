#include "cli.h"

bool cli(bool devMode) {
    Settings settings;
    Profile curProfile("");
    unsigned int index = 0;
    unsigned int index2 = 0;
    bool running = true;
    std::string command;
    unsigned short int result;
    if (!devMode) {
        createNecessaryFolders();
    }
    std::cout << "Type 'q' to quit.\n==============\n";
    while (running) {
        std::getline(std::cin, command);
        std::cout << "-------\n";
        if (command.length() == 0) {}
//        else if (command.substr(0,7) == "getPath" && devMode) {
//            std::cout << "Path:\n" << getPath() << std::endl;
//        }


        // ------------------------------------------------------------------------------------------------------------------------------------------------------------

        // =========================================================================================================================================    consoleCommands

        // ------------------------------------------------------------------------------------------------------------------------------------------------------------


        else if (command.substr(0,14) == "getAsyncToCout" && devMode) {
            index = readTo(command, '"', 16)-1;
            std::string location = command.substr(16, index - 15);
            std::cout << getAsync(location) << std::endl;
        }
        else if (command.substr(0,14) == "getAsyncToFile" && devMode) {
            index = readTo(command, '"', 16)-1;
            std::string location = command.substr(16, index - 15);
            if (downloadFromURL(location, "sample.zip")) {
                std::cout << "Success!\n";
            }
            else {
                std::cout << "Failure.\n";
            }
        }
        else if (command.substr(0,12) == "dependencies") { // Windows probably has none? Unsure
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
//        else if (command.substr(0,28) == "haveAllNecessaryDependencies") {
//            if (haveAllNecessaryDependencies()) {
//                std::cout << "All necessary dependencies are installed. Run 'dependencies' to see if optional dependencies installed\n";
//            }
//            else {
//                std::cout << "Necessary dependencies are NOT installed. Please run 'dependencies' to see what you're missing.\n";
//            }
//        }
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
        else if (command.substr(0,16) == "getHomeDirectory" && devMode) {
            std::cout << "Home is located at '" << getHomeDirectory() << "'\n";
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
        else if (command.substr(0,9) == "fileExists" && devMode) {
            index = readTo(command, '"', 11)-1;
            std::string temp = command.substr(11, index - 10);
            if (fileExists(temp)) {
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
                std::cout << "ERROR: Could not decompress rar. Please install unrar-free with your native package manager or unrar at 'https://www.rarlab.com/rar_add.htm'" << std::endl; // New message for Windows
            }
            else if (result == 7) {
                std::cout << "ERROR: Could not decompress 7z. Please install p7zip-full with your native package manager or 7zip at 'https://7-zip.org/download.html'" << std::endl;
            }
            else {
                std::cout << "Unzipped '" << command.substr(7, index-6) << "' to '" << command.substr(index+4,command.length()-index-5) << std::endl;
            }
        }

        else if (command.substr(0,32) == "getBrowserDownloadURLsFromGithub" && devMode) {
            index = readTo(command, '"', 34)-1;
            std::string url = command.substr(34, index - 33);
            std::vector<std::string> urls = getBrowserDownloadURLsFromGithub(url);
            for (unsigned int i = 0; i < urls.size(); ++i) {
                std::cout << '"' << urls.at(i) << "\", ";
            }
            std::cout << std::endl;
        }
        else if (command.substr(0,23) == "getModVersionFromGithub" && devMode) {
            index = readTo(command, '"', 25)-1;
            std::string repo = command.substr(25, index - 24);
            repo = getModVersionFromGithub(repo, false);
            std::cout << "Created '" << repo << "'\n";
        }
        else if (command.substr(0,12) == "dlFromGithub" && devMode) {
            index = readTo(command, '"', 14)-1;
            std::string repo = command.substr(14, index - 13);
            repo = dlFromGithub(repo);
            std::cout << "Created '" << repo << "'\n";
        }
        else if (command.substr(0,20) == "removeModFromLibrary" && devMode) {
            index = readTo(command, '"', 22)-1;
            std::string mod = command.substr(22, index - 21);
            removeModFromLibrary(mod);
            std::cout << "Removed '" << mod << "'\n";
        }
        else if (command.substr(0,16) == "sortModInLibrary" && devMode) {
            index = readTo(command, '"', 18)-1;
            std::string mod = command.substr(18, index - 17);
            sortModInLibrary(mod);
            std::cout << "Sorted '" << mod << "'\n";
        }
        else if (command.substr(0,22) == "addToLibraryFromGithub" && devMode) { // BOOKMARK
            addToLibraryFromGithub("Nautilus", "SubnauticaModding/Nautilus", "", false);
        }
        else if (command.substr(0,30) == "addBepInExAndNautilusToLibrary") {
            addBepInExAndNautilusToLibrary();
        }
        else if (command.substr(0,30) == "getModList") {
//            std::vector<std::string> result = getModList("Nautilus");
            std::vector<std::vector<std::string>> result = getModList();
            std::cout << "Mods:\n";
            for (std::vector<std::string> line : result) {
                std::cout << "- ";
                for (std::string value : line) {
//                for (std::string value : result) {
                    std::cout << value << ", ";
                }
                std::cout << std::endl;
            }
        }
        else if (command.substr(0,23) == "addToLibraryFromModList") {
            index = readTo(command, '"', 25)-1;
            std::string mod = command.substr(25, index - 24);
            if (addToLibraryFromModList(mod, !devMode)) {
                std::cout << "Added '" << mod << "' to Library.\n";
            }
            else {
                std::cout << "Failed.\n";
            }
        }
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
        else if (command.substr(0,25) == "getSavesDirectory" && devMode) {
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
        else if (command.substr(0,6) == "addMod") {
            index = readTo(command, '"', 8)-1;
            std::string name = command.substr(8, index - 7);
            curProfile.addMod(name);
            std::cout << "Added '" << name << "' to selected profile.\n";
        }
        else if (command.substr(0,9) == "removeMod") {
            index = readTo(command, '"', 11)-1;
            std::string name = command.substr(11, index - 10);
            curProfile.removeMod(name);
            std::cout << "Removed '" << name << "' from selected profile.\n";
        }
        else if (command.substr(0,10) == "disableMod") {
            index = readTo(command, '"', 12)-1;
            std::string name = command.substr(12, index - 11);
            curProfile.disableMod(name);
            std::cout << "Disabled '" << name << "' in selected profile.\n";
        }


        // ------------------------------------------------------------------------------------------------------------------------------------------------------------

        // =========================================================================================================================================    End

        // ------------------------------------------------------------------------------------------------------------------------------------------------------------


        else if (command.at(0) == 'q') {
            std::cout << "Quitting...\n";
            running = false;
        }
        else {
            std::cout << "Command not recognized.\n";
        }
        std::cout << "==============\n" << std::endl;
    }
    return true;
}

