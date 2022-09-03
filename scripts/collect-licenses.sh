#!/bin/bash

licenses=$(find build/ -iname "*license*" && find build/ -iname "*copyright*")

mkdir licenses

for license in $licenses
do
  src=$(basename $(dirname $license))
  libname=${src%-src}
  licenseCopy=$libname-${license##*/}
  cp $license licenses/$licenseCopy
done

if [[ -f "LICENSE" ]]
then
  cp LICENSE licenses/LICENSE
fi

> licenses/README.md cat << EOF
# Third Party and Software Licenses

This software includes third party libraries and/or software
with their licenses included in this directory.
EOF
