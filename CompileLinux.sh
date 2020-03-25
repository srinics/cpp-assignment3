#!/bin/bash
op="$1"
binary_name="linux-out"
binary_name2="linux-proc"
if [ "$op" = "clean" ]; then
	rm -rf $binary_name
	rm -rf $binary_name2
	exit 0;
fi
g++ -g Main.cpp -o $binary_name -lpthread -lrt
g++ -g LinuxProc.cpp -o $binary_name2 -lpthread -lrt
