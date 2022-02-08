#!/usr/bin/env bash

##############################################################################################################################
#                                   																						                                             #
#                                   				* SETTINGS *															                                       #
#                                   																						                                             #
##############################################################################################################################

EOC='\033[0m'
BOLD='\033[1;37m'

function clean {
  [ -e decrypt.txt ] && rm decrypt.txt
  [ -e encrypted.bin ] && rm encrypted.bin
  [ -e .key ] && rm .key
  [ -e decrypt.txt ] && rm decrypt.txt
  [ -e encrypted.bin ] && rm encrypted.bin
}

##############################################################################################################################
#                                   																						                                             #
#                                   				* COMPILATION *															                                     #
#                                   																						                                             #
##############################################################################################################################

function compile {
    echo "Please wait..."
    make
    clean
    echo "Generating secret key..."
    od -A n -t d -N 1 /dev/urandom >> .key
}

if [ $# -eq 0 ]
  then
    compile
fi

if [ "$1" == "re" ]
  then
    clean
    echo "Please wait..."
    make re
    echo "Generating secret key..."
    od -A n -t d -N 1 /dev/urandom >> .key
fi

if [ "$1" == "up" ]
  then
    clean
    echo "Generating secret key..."
    od -A n -t d -N 1 /dev/urandom >> .key
    make
fi

##############################################################################################################################
#                                   																						                                             #
#                                   				*CLEAN *																                                         #
#                                   																						                                             #
##############################################################################################################################

if [ "$1" == "clean" ]
  then
    make fclean
    clean
fi
