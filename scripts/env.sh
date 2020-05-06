#!/bin/bash
DIR=$(echo $PWD | rev | cut -d '/' -f1 | rev)
BUILD="../build"
PROJECT="../cafe80211.xcodeproj"
SRC="../cafe80211/"

if [ "$DIR" != "scripts" ]; then
BUILD="./build"
PROJECT="./cafe80211.xcodeproj"
SRC="./cafe80211/"
fi
