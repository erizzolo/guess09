#!/bin/bash
stty_orig=`stty -g`
stty -echo
./guess09
stty $stty_orig
