# MHW Plugins

One stop shop for my plugins. Check out the releases labeled by date.

This is also where I'll keep _addresses.yaml_ updated

## Plugins in this pack

- [TheFlash](https://github.com/Stuff-Mods/MHW-TheFlash)
- [GamepadHook](https://github.com/Stuff-Mods/MHW-GamepadHook)
- [HUDToggler](https://github.com/Stuff-Mods/MHW-HUDToggler)
- [LockOn2MapPin](https://github.com/Stuff-Mods/MHW-LockOn2MapPin)
- [ReturnTimer](https://github.com/Stuff-Mods/MHW-ReturnTimer)

## Symlink

To make my life easier I symlink _addresses.yaml_ so that the changes I make are available to me without me having to copy it over to _nativePC/..._. I do this once by opening `cmd` as admin, navigating to this repo and running this:

```cmd
mklink "C:\Program Files (x86)\Steam\steamapps\common\Monster Hunter World\nativePC\plugins\config\addresses.yaml" "%cd%\addresses.yaml"

```
