#! /bin/bash

filelist=`find ./build/test -type f`

for file in $filelist
do
	if [ -x $file ]
	then
		echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
		echo " "
		echo "RUN TEST $file"
		echo " "
		echo "++++++++++++++++++++++++++++++++++++++++++++++++++++++++++"
		$file
		echo "----------------------------------------------------------"
		echo " "
		echo " "
	fi
done