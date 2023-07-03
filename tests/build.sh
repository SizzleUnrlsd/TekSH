#!/bin/bash

make

make_exit_code=$?
if [[ $make_exit_code != 0 ]]; then
    echo "Error : Compilation failure"
    exit 1
fi

function run_command {
    echo "Command: [$1]"
    echo "---------------------------"

    output=$(timeout 5s ./teksh <<< "$1" 2>&1)
    exit_code=$?

    if [[ $exit_code == 124 ]]; then
        echo "Error : Time out"
        echo
        exit 1
    fi

    echo "$output"
    echo "---------------------------"
    echo
}

run_command "ls"
run_command "ls ; ls"
run_command "ls -a > toto ; cat toto"
