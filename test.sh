#!/bin/bash

run="./test 5 25 100000"

echo 'Line buffered stdout:'
./stdbuf -o L $run

echo 'Unbuffered stdout:'
./stdbuf -o 0 $run

echo 'Size of stdout buffer is 3 bytes:'
./stdbuf -o 3 $run
