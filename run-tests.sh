#!/usr/bin/env bash

make clean
make build

while read line; do
	e=$(./bin/gameof24 <<< "$line" | tail -1)
	n=$(echo "$line" | tr -d ' ')
	printf "$n: "
	if [ "$e" = "No solution" ]; then
		echo "$e"
	else
		r=$(echo "scale=5; $e" | bc)
		echo "$e = $r"
		# Define a tolerance for the comparison
		diff=$(echo "scale=5; $r - 24" | bc -l)
		if (( $(echo "$diff < -0.1 || $diff > 0.1" | bc -l) )); then
			echo "Test failed!"
			exit 1
		fi
	fi
done < ./tests.in

