#!/bin/bash
make
if [[ $2 = *".dfa" ]]; then
	./part2 $1 $2
else
	./part1 $1 $2
fi