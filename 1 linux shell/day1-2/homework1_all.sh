#! /bin/bash 

dst=dir

if [ -d $dst ]; then echo "$dst existed"
else
	echo "mkdir $dst"
	mkdir ./$dst
fi

function fun {
	for f in `find . -type f`
	do
		if [ -f $f ]
		then
			#echo "copy $f"
			cp $f ./$dst
			echo "copy $f" >>1.txt
		fi
		#cat 1.txt | wc -l 

	done
}

fun

echo "return value $?"
cat 1.txt | wc -l 
