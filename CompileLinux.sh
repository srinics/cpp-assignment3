#!/bin/bash
op="$1"
binary_name="linux-out"
if [ "$op" = "clean" ]; then
	rm -rf $binary_name
	exit 0;
fi
g++ -g Main.cpp -o $binary_name -lpthread -lrt
