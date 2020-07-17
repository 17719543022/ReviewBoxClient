#!/bin/bash
LibDir=$PWD"/lib"
Target=$1
lib_array=($(ldd $Target | grep -v "/usr/lib" | grep -o "/.*" | grep -o "/.*/[^[:space:]]*"))
$(mkdir $LibDir)
for Variable in ${lib_array[@]}
do
    cp "$Variable" $LibDir
done
