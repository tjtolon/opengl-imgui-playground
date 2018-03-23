#!/bin/bash

url=https://github.com/ocornut/imgui/archive/master.zip
wget $url
unzip master.zip
mkdir -p extern/imgui
mv imgui-master/* extern/imgui
rm -fr imgui-master
rm master.zip