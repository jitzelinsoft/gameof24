#!/usr/bin/env bash

make clean
make build

while read line; do
	./bin/gameof24 <<< "$line"
done<./tests.in
