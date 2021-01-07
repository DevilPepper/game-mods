# HUDToggler

## What is this?

It's an HUD Toggler. I've seen a few that exist, so it's not a new thing.
This one is a Stracker plugin, so it has direct access to memory
and it's hooked to the controller input listener/poller
so it checks for input every frame.

There's also a subtitles toggle that I've been meaning to make it's own plugin.
It lets you toggle subtitles on and off in the middle of a scene.

## Game Settings

I recommend going to **Game Settings->HUD Display** and setting everything to off.

## Limitations

- Currently only made for gamepads, but feel free to open a PR adding keyboard and mouse support
- Buttons are hard coded as **L1** for HUD and **Select** for subtitles because there's no clean built in way of parsing a string to an enum.
  - If you require different buttons, for now you'll have to rebuild after you edit it here:
  - <https://github.com/SupaStuff/MHW-GamepadPlugins/blob/c96cb990c24c69d122a9f1f7060bf039dc64d2e8/HUDToggler/dllmain.cpp#L25-L26>
