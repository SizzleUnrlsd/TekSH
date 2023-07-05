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
run_command "       ls        ;;;;;;;;;;;;;;;;;               "
run_command "ls ; ls"
run_command "ls -a > toto ; cat toto"
run_command "ls | rev > toto ; cat toto ; rm toto ; ls -alt | cat | cat | cat > toto ; cat toto ; rm toto"
run_command "           ls -a       "
run_command "env"
run_command "setenv toto ; setenv toto tutu ; env"
run_command "setenv toto tutu ; unsetenv tutu toto; env"
run_command "setenv toto tutu ; unsetenv tutu toto |"
run_command ";;"
run_command "; ;"
run_command "<<"
run_command ">>"
run_command "rm toto && ls"
run_command "rm toto || ls"
run_command "ls | ls && ls -a"
run_command "ls || ls -a && ls -alt"
run_command "ls | rev > toto ; cat toto ; rm toto ; ls -alt | | cat | cat | cat > toto ; cat toto ; rm toto"
run_command "ls;ls -a     ;ls -alt > toto; cat toto; rm toto"