#! /bin/bash

filelist=`find ./build/test -type f`
num=0
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
		if [ $? -ne 0 ]; then
			num=1
			echo "Return $num"
		fi
		echo "----------------------------------------------------------"
		echo " "
		echo " "
	fi
done

if [ $num -ne 0 ]; then
	exit 1
fi
