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

# if [ "$(uname)" == "Darwin" ]; then  
# 	REQUIRED_PKG="boost"
# 	echo Checking for $REQUIRED_PKG: $PKG_OK
#     if [ "" = "$PKG_OK" ]; then
#         echo "No $REQUIRED_PKG. Setting up $REQUIRED_PKG."
#         brew install $REQUIRED_PKG
#     fi
# elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
# 	REQUIRED_PKG="libboost-all-dev"
# 	echo Checking for $REQUIRED_PKG: $PKG_OK
#     PKG_OK=$(dpkg-query -W --showformat='${Status}\n' $REQUIRED_PKG|grep "install ok installed")
#     if [ "" = "$PKG_OK" ]; then
#         echo "No $REQUIRED_PKG. Setting up $REQUIRED_PKG."
#         sudo apt-get --yes install $REQUIRED_PKG
#     fi
# fi

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
    if [ "$(uname)" == "Darwin" ]; then
      openssl rand -base64 32 > .key
      openssl enc -e -aes-256-cbc -in files/toEncrypt.txt -out files/encrypted -pass pass:.key
      # openssl enc -d -aes-256-cbc -in files/encrypted.txt -out files/decrypted.txt -pass pass:.key
    elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
      openssl rand -base64 32 > .key
      openssl enc -e -aes-256-cbc -in files/toEncrypt.txt -out files/encrypted -pass pass:.key
      # date +%s | sha256sum | base64 | head -c 32 > .key
    fi  
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

# if clean is called
# make fclean
# rm .key
if [ "$1" == "clean" ]
  then
    make fclean
    rm .key
    rm files/decrypted
    rm files/encrypted
    rm recv
 fi