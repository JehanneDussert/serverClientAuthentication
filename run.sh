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
    openssl enc -e -aes-256-cbc -in files/toEncrypt.txt -out files/encrypted -pass pass:.key
fi

##############################################################################################################################
#                                   																						 #
#                                   				* TEST *																 #
#                                   																						 #
##############################################################################################################################

function test {
  i=1;
	echo "Testing server with only one client..."
  nc localhost 8080
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

##############################################################################################################################
#                                   																						 #
#                                   				*CLEAN *																 #
#                                   																						 #
##############################################################################################################################

if [ "$1" == "clean" ]
  then
    make fclean
    rm .key
    rm files/decrypted.txt
    rm files/encrypted
    rm files/recv
 fi