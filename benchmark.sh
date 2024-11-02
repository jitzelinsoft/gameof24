#!/usr/bin/env bash

while read line; do
	./bin/gameof24 <<< "$line"
done < ./tests.in

