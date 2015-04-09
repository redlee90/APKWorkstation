#!/bin/sh

#sh showjava.sh outDir

BASEDIR=$(dirname $0)

function traverse() {
	for file in "$1"/*
	do 
	if [ ! -d "${file}" ]; then	
		if [ ${file: -6} == ".class" ]; then
			java -jar $BASEDIR/showjava.jar "${file}" >/dev/null 2>&1
			rm "${file}"
		fi
	else 
		traverse "${file}"
	fi
done
}

function main() {
	unzip "$1"/base.jar -d "$1"/java >/dev/null 2>&1
	if [ -d "$1"/java ]; then
		traverse "$1"/java/
	fi
	#rm "$1"/base.jar
}

main "$1"