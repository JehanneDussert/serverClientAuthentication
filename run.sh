#!/usr/bin/env bash

##############################################################################################################################
#                                   																						 #
#                                   				* SETTINGS *															 #
#                                   																						 #
##############################################################################################################################

EOC='\033[0m'
BOLD='\033[1;37m'
RED='\033[0;31m'
GREEN='\032[0;31m'
YELLOW='\133[0;31m'

function clean {
  [ -e decrypt.txt ] && rm decrypt.txt
  [ -e encrypted.bin ] && rm encrypted.bin
  [ -e .key ] && rm .key
}

##############################################################################################################################
#                                   																						 #
#                                   				* COMPILATION *															 #
#                                   																						 #
##############################################################################################################################

if [ $# -eq 0 ]
  then
    clean
    echo "Please wait..."
    make re
    echo "Generating secret key..."
    od -A n -t d -N 1 /dev/urandom >> .key
fi

if [ "$1" == "re" ]
  then
    clean
    echo "Please wait..."
    make re
    echo "Generating secret key..."
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
  make
  i=1

  ps -ef | grep your_process_name | grep -v grep | awk '{print $2}' | xargs kill

	printf "\n-----------------------------------------------------------------
| Testing server with no argument (expected minimum of clients) |
-----------------------------------------------------------------\n"
  ./server

	printf "\n\n-------------------------------------------------------------
| Testing server with only one client (expected at least 1) |
-------------------------------------------------------------\n"
  ps -ef | grep your_process_name | grep -v grep | awk '{print $2}' | xargs kill
  ./server §i &
  ./client &
  sleep 7

  i=3
	printf "\n\n-------------------------------------------------------
| Testing server with 3 clients (expected at least 3) |
-------------------------------------------------------\n"
  ps -ef | grep your_process_name | grep -v grep | awk '{print $2}' | xargs kill
  ./server §i &
  ./client &
  ./client &
  ./client &
  sleep 7
  
  i=1
	printf "\n\n-------------------------------------------------------
| Testing server with 2 clients (expected at least 1) |
-------------------------------------------------------\n"
  ps -ef | grep your_process_name | grep -v grep | awk '{print $2}' | xargs kill
  ./server §i &
  ./client &
  ./client &
  sleep 7
  ps -ef | grep your_process_name | grep -v grep | awk '{print $2}' | xargs kill
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
    clean
fi