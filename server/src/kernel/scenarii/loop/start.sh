#!/bin/bash

./drt --config-file scenarii/loop/1 > /dev/null 2>&1 &
./drt --config-file scenarii/loop/2 > /dev/null 2>&1 &
./drt --config-file scenarii/loop/3

killall drt

