#!/usr/bin/env bash

##############################################################################################################################
#                                   																						 #
#                                   				* SETTINGS *															 #
#                                   																						 #
##############################################################################################################################

EOC="\033[0m"
BOLD="\033[1;37m"
RED="\033[0;31m"
GREEN="\032[0;31m"
YELLOW="\133[0;31m"

unameOut="$(uname -s)"
case "${unameOut}" in
    Linux*)     machine=Linux;;
    Darwin*)    machine=Mac;;
esac

function clean {
  rm files/decrypted.txt
  rm files/encrypted
  rm files/recv
}

# CHECK IF OPENSSL IS INSTALLED

##############################################################################################################################
#                                   																						 #
#                                   				* COMPILATION *															 #
#                                   																						 #
##############################################################################################################################

if [ $# -eq 0 ]
  then
    echo "Please wait..."
    make re
    echo "Generating secret key..."
    openssl rand -base64 32 > .key
fi

if [ "$1" == "re" ]
  then
    clean
    echo "Please wait..."
    make re
    echo "Generating secret key..."
    openssl rand -base64 32 > .key
fi

if [ "$1" == "up" ]
  then
    clean
    make
fi

##############################################################################################################################
#                                   																						 #
#                                   				* TEST *																 #
#                                   																						 #
##############################################################################################################################

function test {
  i=1;
	echo "Testing server with only one client..."
  ./server 1
}

function testClient {
  ./client
  filename='.key'
  n=1
  while read line; do
  # reading each line
    echo "Line No. $n : $line"
    n=$((n+1))
  done < $filename
}

if [ "$1" == "test" ]
  then
    test
fi

if [ "$1" == "client" ]
  then
    testClient
fi

##############################################################################################################################
#                                   																						 #
#                                   				*CLEAN *																 #
#                                   																						 #
##############################################################################################################################

if [ "$1" == "clean" ]
  then
    make fclean
    rm .key
    clean
fi