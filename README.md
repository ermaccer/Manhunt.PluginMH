# Manhunt.PluginMH
A plugin for Manhunt.

# Installation

## NOTE

PluginMH requires https://github.com/ThirteenAG/Ultimate-ASI-Loader or https://github.com/aap/simpledllloader.
Check PluginMH.ini for available features.



# Features



## First Person Mode

Allows to freely move in first person perspective

## TOC Disabler

Removes the need to constantly update toc.txt

## Player Model Loader

Allows you to load more player models and set them with one ini option, no need to replace existing files.

## Custom Menu

Menu based on Manhunt 2 menu, it allows you to quickly spawn available weapons and more!

## Console

Custom console recreated using leftover and custom code.

## Screenshot Mode

Press one key to instantly freeze the game, hide hud and move camera!

## Modloader

Load mods easily (read below)!

## Custom Animations Manager

Replaces animations loader with a custom one, allows to load more than 1000 animations

## Stats

Track your game data!

## Tweaks

Disable autoaim, BSP warnings and more!

```NOTE: modloader and data folder must be in the root folder of the game!```


# How to use Modloader
Modloader is a feature inspired by GTA Modloader by Link,
it is not as powerful as the GTA version but it is still pretty useful.

What isn't supported?

Currently, MH Modloader doesn't support swapping:

- INI
- PAK
- Any audio file 

How to load mods?

It depends on type, but every mod needs a folder.
Create a folder with any name inside modloader folder.

MH Modloader comes with a custom DFF loader which allows
to load multiple .dff files and append them to the model list.

Some files are ignored from beign loaded, they are specified
in modloader.ini file.

By default, your .dff filename cannot be gmodelspc.dff or modelscpc.dff.
Model require txds to be loaded too, how to load texture for custom models?
You'll need a filename with .txd extension which is the same as the model name.
eg.
Katana.dff requires Katana.txd.

So, how to load model mods?

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

## Check the readme in releases and .ini file for more info!