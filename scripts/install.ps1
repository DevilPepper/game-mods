. ./scripts/paths.ps1

if (Test-Path -Path $MHW) {
  # Copy-Force "${PWD}/build/mods/mhw/loader/loader.dll" "${MHW}/loader.dll"
  Copy-Force "${PWD}/build/_deps/yaml-cpp-build/yaml-cppd.dll" "${MHW}/yaml-cppd.dll"
  Copy-Force "${PWD}/build/libs/gamepad/GamepadLib.dll" "${MHW}/GamepadLib.dll"
  Copy-Force "${PWD}/build/libs/updateAddresses/UpdateAddresses.dll" "${MHW}/nativePC/plugins/!UpdateAddresses.dll"

  Copy-Force "${PWD}/build/mods/mhw/gamepad/GamepadHook.dll" "${MHW}/nativePC/plugins/GamepadHook.dll"
  Copy-Force "${PWD}/build/mods/mhw/hudToggler/HUDToggler.dll" "${MHW}/nativePC/plugins/HUDToggler.dll"
  Copy-Force "${PWD}/build/mods/mhw/lockOn2MapPin/LockOn2MapPin.dll" "${MHW}/nativePC/plugins/LockOn2MapPin.dll"
  Copy-Force "${PWD}/build/mods/mhw/returnTimer/ReturnTimer.dll" "${MHW}/nativePC/plugins/ReturnTimer.dll"
  Copy-Force "${PWD}/build/mods/mhw/theFlash/TheFlash.dll" "${MHW}/nativePC/plugins/TheFlash.dll"
}
