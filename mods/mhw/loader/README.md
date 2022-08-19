# Stracker's Loader

## What is this?

This is [Stracker's Loader](https://github.com/Strackeror/MHW-QuestLoader/tree/master/MHWLoader).
My fork deviated a bit and at this point, it's not even worth trying to merge my changes.
So I copied just the code for just _loader.dll_ here.

## Major changes from the original

In addition to some minor refactoring and changes in dependencies I:

- removed the AOB scan.
  - I think Stracker used to release this with the game version address hard coded anyway.
  - The game version is in the title bar, so I'm grabbing it from there instead.
- added plugin hot reloading.
  - Nice for dev.
  - Assumes plugin cleans up when asked to unload. Won't be so nice otherwise...

Basically everything else is pretty much the same. But you probably don't want to use this.
Go here instead: [The real one](https://www.nexusmods.com/monsterhunterworld/mods/1982).
