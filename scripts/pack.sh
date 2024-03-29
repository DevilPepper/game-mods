#!/bin/bash

# region helpers
function enter_temp() {
  mkdir temp
  cd temp
}

function zipit_and_cleanup() {
  zip $1.zip -r *
  cd ..
  mv temp/$1.zip .
  rm -rf temp
}

function copy_licenses() {
  cp -r ../../licenses/ .
}

function copy_yaml_ccp() {
  find ../../build/_deps -name "yaml-cpp*.dll" | xargs -I {} cp {} .
}

function copy_gamepad_lib() {
  find ../../build/libs -name "GamepadLib.dll" | xargs -I {} cp {} .
}

function copy_aob_scan() {
  find ../../build/libs -name "UpdateAddresses.dll" | xargs -I {} cp {} ${1:-.}
}
# endregion helpers

mkdir zips
cd zips

# region MHW_Plugins
enter_temp
copy_licenses
copy_yaml_ccp
copy_gamepad_lib

mkdir -p nativePC/plugins/config
copy_aob_scan nativePC/plugins/!UpdateAddresses.dll
find ../../build/mods/mhw -name "*.dll" | xargs -I {} mv {} nativePC/plugins/
rm nativePC/plugins/loader.dll
cp ../../mods/mhw/*.yaml nativePC/plugins/config/
mv nativePC/plugins/config/UpdateAddresses.yaml .

zipit_and_cleanup MHW_Plugins
# endregion MHW_Plugins

# region MHW_Configs
enter_temp

mkdir -p nativePC/plugins/config
cp ../../mods/mhw/hudToggler/HUD_toggles.json \
   ../../mods/mhw/theFlash/TheFlash.yaml \
   nativePC/plugins/config/

zipit_and_cleanup MHW_Configs
# endregion MHW_Configs
