If Vortex does actually end up getting full SteamOS compatibility, production of this program will probably cease.

**__This project is unfinished, and should not be used!__**

*(No QMM or SMLHelper compatibility planned.)*

# To do before Pre-Release:

* BepInEx installation script
* Nautilus installation script
* Install mods from Mod List
* Install mods from Github
* Apply Profiles to actual Subnautica game directory
* Keep track of mod versions
* Implement Nexus compatibility (using API key)
* Implement `help` command
* Safeguards for users

# To do before Release:

* Add ability to update mods
* Implement unzip library
* Implement unrar library
* Implement 7zip library
* Implement tar library
* Polish features
* Add bug-catching

# Possible future features:
* Find a way to automatically set Launch Options
* GUI (will be in different repository)
* Maybe allow users to download and manage saves
* Maybe make a solution converter from `cbp` to `sln`? No promises.
* Maybe Subnautica 2 compatibility? Again, no promises. (I don't own Below Zero so I can't test it but maybe I might try adding compatibility for that too)
* Possibly create a Windows version? Once more, no promises. (Likelihood of Mac version is 5%, but rising with each cross-platform addition.)

# Finished:

* Create and manage Profiles
* Access and utilize Settings
* Download files asynchronously
* Target and download specific Github repository releases
* Add auto-sort for mod folders

# Building

The project is too early for building to be worth it but if you really want to, then `cd` into whatever directory you wish to build it in and run:

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
* You state the changes you made (which will happen anyway if you write a description/README of your project)

(This is a simplified summary of the license and should not be taken as legal advice. Please consult a lawyer before taking any action.)

**Dependencies:**
* [CPR (1.14.2)](https://github.com/libcpr/cpr/tree/1.14.2) is under the [MIT License](https://github.com/libcpr/cpr/blob/1.14.2/LICENSE).
