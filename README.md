# Manhunt.PluginMH
A plugin for Manhunt.

# Installation

PluginMH requires https://github.com/ThirteenAG/Ultimate-ASI-Loader/releases .
Extract dinput8.dll to your Manhunt folder, then rename it to ddraw.dll.


Download PluginMH.zip from *Releases* to obtain binary .asi file and .ini, extract it 
to your Manhunt folder.


```NOTE: modloader and data folder must be in the root folder of the game!```

Check PluginMH.ini for available features.


# Building

PluginMH was compiled & tested using Visual Studio 2017.
You will need to have some sort of RenderWare SDK in RWSDK PATH variable.

Dummy SDK:
https://github.com/GTAmodding/re3/tree/master/src/fakerw




# Features

## Hotkeys
PluginMH adds few useful hotkeys:

| Hotkey | Effect | 
|     ---      |   ---        | 
| **~**  |  Opens/Closes console. | 
| **F1** | Opens Rockstar Games developer menu. | 
| **F2** | Opens custom PluginMH menu, based on [my Manhunt 2 menu](https://github.com/ermaccer/Manhunt2.DebugMenu). |
| **F3** | Toggles Screenshot Mode. | 
| **F4** | Toggles HUD.|



**These keys can be configured in the PluginMH.ini file!**


# Custom Menu
An almost direct backport of [Manhunt 2 menu](https://github.com/ermaccer/Manhunt2.DebugMenu).

![](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/pmh/4.jpg)

### Features

#### Player
- Infinite Health
- God Mode (Invulnerability)
- Disable/Enable Fall Damage
- Save/Load Custom Waypoint
- Display Player Coordinates

#### Weapon Spawner
This section allows you to spawn any **loaded** weapon and grant you
maximum ammunition if you create a firearm.

Missing weapons are NOT a bug of this menu, it is how Manhunt works.
Only used weapons are loaded into each level.

#### HUD 
- Display Timer (0:00, doesn't work)
- Display Body Count .
- Enable Body Counts, this makes body count count up all kills & executions.


#### Cheats
This section allows you to quickly toggle cheat codes and clear/set cheats flag, 
which locks/allows saving.

#### World
You can hide stars and moon here.

#### Weather
You can change current weather to:
- Free (random weather)
- Clear
- Cloudy
- Thunder
- Rainy
- Foggy
- Windy


# Console
A custom console recreated using leftover and new code.
![](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/pmh/3.jpg)

Type **help 1** or **help 2** to get a list of available commands.

Some commands string parameters *are* case-sensitive!


# New Frontend
PluginMH completely replaces main menu functionality with a new one.

Changes:
- All buttons are now on the left side on the screen
- PluginMH version info is in upper left corner

## New pages

### Stats
![](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/pmh/2.jpg)
A feature inspired by Grand Theft Auto menu of the same name, you can
track your game data here.

### Skins
![](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/pmh/9.jpg)
PluginMH completely changes the way player skins work, you can load multiple skins 
using simple .ini files and they will show up in a new menu - Skins.

Needless to say, PIGGSUIT, HELLSUIT and BUNYSUIT cheats have no longer any effect.

Selected skin is saved to a PluginMH.ini file which will be located in your Manhunt User Files directory.


### Modifications
A page used to see mods loaded by Modloader.

### Screenshot Mode
Press one key to instantly freeze the game, hide hud and be able to freely move camera!
![](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/pmh/8.jpg)




## First Person Mode

Allows to play the game in first person perspective.
![](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/pmh/5.jpg)
![](https://raw.githubusercontent.com/ermaccer/ermaccer.github.io/gh-pages/assets/mods/pmh/7.jpg)





# Modloader
Modloader is a feature inspired by GTA Modloader by link2012,
it is not as powerful as the GTA version but it is still pretty useful.


## How to use Modloader

#### What isn't supported?

Currently, Manhunt version of modloader doesn't support swapping:

- INI
- PAK
- Any audio file 

#### How to load mods?

It depends on type, but every mod needs a folder.
Create a folder with any name inside modloader folder.

Modloader comes with a custom DFF loader which allows to load multiple .dff files a
nd append them to the model list.

Some files are ignored from beign loaded, they are specified
in modloader.ini file.

By default, your .dff filename cannot be gmodelspc.dff or modelscpc.dff.
Model requires TXD to be loaded too, you'll need a filename with .txd extension which is the same as the model name (Katana.dff requires Katana.txd).


Example folder tree:

```
---- My Custom Katana
-------Katana.dff
-------Katana.txd
```

The .dff file will be loaded and any model that it replaces will 
be replaced.


Swapping normal files

To swap normal files, you'll need to recreate the original path.

Example folder tree
```
---- My Custom Loading
-------pictures
--------TITLE
---------title_pc.txd
```

The file will be loaded in place of the original.

You can view list of loaded mods in the "Modifications" menu.


# Modding Limits

PluginMH replaces existing animation loader with a new one which 
allows to use more than 1000 anims in one file (number adjustable in .ini).

Map material limit was increased from 300 to 2500.

Additionally, TOC (Table Of Contents) no longer needs to be updated!


# Credits
**Fire_Head** - big help with RenderWare research.

https://github.com/GTAmodding/re3 - Skins menu is mostly based on RE3 skins code.