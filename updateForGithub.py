fileList = ["cli.cpp","cli.h","consoleCommands.cpp","consoleCommands.h","Profile.cpp","Profile.h","Settings.cpp","Settings.h", "main.cpp",
            "Reefbackend.cbp","Reefbackend.layout",
            "Reefbackend.depend","default-settings.tsv","Mod-List.tsv","mod-dependencies.tsv"]

for fileName in fileList:
    file = open("/home/luna/Documents/Programming/C++/Reefbackend/" + fileName, "rt")
    fileContents = file.read()
    file.close()
    file = open("/home/luna/Documents/Programming/C++/Reefbackend/.build-for-Github-MEGA_EXCLUDED/Reefbackend/" + fileName, "wt")
    file.write(fileContents)
    file.close()