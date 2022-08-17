. ./scripts/paths.ps1

if (Test-Path -Path $MHW) {
  Copy-Safe "${PWD}/mods/mhw/UpdateAddresses.yaml" "${MHW}/UpdateAddresses.yaml"
  Symlink "${PWD}/mods/mhw/addresses.meta.yaml" "${MHW}/nativePC/plugins/config/addresses.meta.yaml"
  Symlink "${PWD}/mods/mhw/addresses.yaml" "${MHW}/nativePC/plugins/config/addresses.yaml"

  Copy-Safe "${PWD}/mods/mhw/hudToggler/HUD_toggles.json" "${MHW}/nativePC/plugins/config/HUD_toggles.json"
  Copy-Safe "${PWD}mods/mhw/theFlash/TheFlash.yaml" "${MHW}/nativePC/plugins/config/TheFlash.yaml"
}
