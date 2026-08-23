If Vortex does actually end up getting full SteamOS compatibility, production of this program will probably cease.

**__This project is unfinished, and should not be used!__**

*(No QMM or SMLHelper compatibility planned.)*

<sub>_[(How version numbering works in all my programs.)](https://github.com/lunanerdderg/lunanerdderg.github.io/blob/main/version-numbering.md)_</sub>

# To do before Pre-Release:

* Open with nondefault Profile/vanilla
* Implement Nexus compatibility (using API key)
  * List available mods from Nexus
  * Keep track of Nexus mod versions
  * Download mod files from Nexus
  * Keep track of Nexus mod dependencies
* Implement `help` command
* Safeguards for users
* Major bug fixes (minor bugs may remain)

# To do before Release:

* Remove files in `config` if their associated mod is uninstalled
* Add ability to scan for mod updates
* Add ability to update mods (manually and automatically)
* Return only specific settings to default, not all simultaneously
* Automatically save all changes to Profile made in-game once Subnautica is closed, and remove profile to automatically return to vanilla
* Automatically save previous logs once Subnautica is closed
* Automatically install mod dependencies with mods
* Allow mods to be added directly to Profiles without requiring manual installation to Library first (automatic instead)
* Test as many mods as possible to ensure sorting algorithm can handle all possible variations
* Filter Nexus mods to exclude mods which require SMLHelper
* Automatically create all files necessary for function of program if not detected in directory
* Implement unzip library
* Implement 7zip library
* Implement unrar library
* Implement tar library
* Polish features
* Add bug-catching

# Possible future features:
* Find a way to automatically set Launch Options
* GUI (will be in different repository)
* Maybe allow users to download and manage saves
* Maybe Subnautica 2 compatibility? No promises. (I don't own Below Zero so I can't test it but maybe I might try adding compatibility for that too)
* Possibly create a Windows version? Again, no promises. (Likelihood of Mac version is 5%, but rising with each cross-platform addition.)
* Maybe make a solution converter from `cbp` to `sln`? Once more, no promises.
* Mod dependency tracking capability (`MOD_NAME.depend` files in `Mod-Library`?)
* Function to save all changes to Profile (manual, not automatic)
* Manually save previous log

# Finished:

* Access and utilize Settings
* Return settings to default
* Download files asynchronously
* Target and download specific Github repository releases
* Add auto-sort for freshly-downloaded mods
* Add mods to library from Github
* Read mod versions from Github
* BepInEx + Nautilus installation script
* Keep track of Github mod versions
* Read Modlist for functions which need it, and print it at request for user
* Add mods to library from Modlist
* Remove mods from Modlist
* Create Profiles
* Delete Profiles
* Rename Profiles
* Add mods to Profiles from Library 
* Remove mods from Profiles
* Apply Profiles to actual Subnautica game directory
* Switch back from modded to vanilla and between Profiles
* Eliminated all absolute (non-relative) paths, (aside from Subnautica directory, which is necessary)
* Set default Profile (or vanilla)

# Building

The project is too early for building to be worth it, but if you really want to, then `cd` into whatever directory you wish to build it in and run:

```
git clone https://github.com/lunanerdderg/Reefbackend.git
cd Reefbackend
chmod +x bootstrap.sh
bootstrap.sh
```

`Reefbackend.cbp` is a [Code::Blocks](https://www.codeblocks.org/downloads/binaries/) solution file, so you will need that software to open the project. You can try a converter, but I don't know how effective they are.

**Solution conversion software:**
| Format | Converter |
| - | - |
| GNU make | [cbp2make](https://github.com/mirai-computing/cbp2make) |
| cmake | [cbp2cmake](https://codeberg.org/Hesti/cbp2cmake) |

# License

You may view the GNU General Public License v3.0 [here](https://github.com/lunanerdderg/Reefbackend/blob/main/LICENSE), but the TL;DR is that you can use this project for whatever you like, as long as:

* You credit me
* Your project is open-source
* Your project uses a [GNU license](https://choosealicense.com/licenses/)
* You state the changes you made (which will most likely happen anyway if you write a descriptive README or description for your project)

_(This is a simplified summary of the license and should not be taken as legal advice. Please consult a lawyer before taking any action.)_

**Dependencies:**
* [CPR (1.14.2)](https://github.com/libcpr/cpr/tree/1.14.2) is under the [MIT License](https://github.com/libcpr/cpr/blob/1.14.2/LICENSE).
