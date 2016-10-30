#! /bin/bash 
read A


case $A in
	[9]?|100)
		echo "A"
		;;
	[8]?)
		echo "B"
		;;
	[7]?)
		echo "C"
		;;
	[6]?)
		echo "D"
		;;
	[0-5]?|0)
		echo "E"
		;;
	*)
		echo "ERROR"
		;;
esac

		


