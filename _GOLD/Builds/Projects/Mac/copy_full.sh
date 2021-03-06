#!/bin/sh
homedir=~
eval homedir=$homedir
echo $homedir # prints home path

mkdir $homedir/Library/Application\ Support/CLOUDS;

if [ -d $homedir/Library/Application\ Support/CLOUDS ]; then
	mv $DSTROOT/CloudsData $homedir/Library/Application\ Support/CLOUDS;
fi

if [ -d /Volumes/CLOUDS/.CloudsMedia.noindex ]; then
    sudo cp -rf /Volumes/CLOUDS/.CloudsMedia.noindex $homedir/Library/Application\ Support/CLOUDS/CloudsData/;
fi

open /Applications/

exit 0