#!/bin/bash

GREEN='\033[0;32m'
RED='\033[0;31m'
NC='\033[0m'

check_status()
{
    if [ $1 -eq 0 ]; then
        echo -e "${GREEN}--[OK]--${NC}"
    else
        echo -e "${RED}--[KO]--${NC}"
        exit 1
    fi
}

build_and_run_image()
{
    local image_name=$1
    local dockerfile=$2

    local lowercase_image_name=$(echo "$image_name" | tr '[:upper:]' '[:lower:]')

    echo "BUILDING $image_name TEST"
    docker build -t building_$lowercase_image_name --no-cache -f $dockerfile .. >/dev/null 2>&1
    check_status $?

    echo "RUNNING $image_name TEST"
    docker run --rm building_$lowercase_image_name >/dev/null 2>&1
    check_status $?
}


build_and_run_image "ARCHLINUX" "Dockerfile_archlinux"
build_and_run_image "DEBIAN" "Dockerfile_debian"
build_and_run_image "FEDORA" "Dockerfile_fedora"
