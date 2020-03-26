#!/bin/bash
op="$1"
binary_name="linux-si"
binary_name2="linux-pl"
if [ "$op" = "clean" ]; then
	rm -rf $binary_name
	rm -rf $binary_name2
	exit 0;
fi
g++ -g SingleInstanceApp.cpp -o $binary_name -lpthread -lrt
g++ -g ProcessList.cpp -o $binary_name2 -lpthread -lrt
