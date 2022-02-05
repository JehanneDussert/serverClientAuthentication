#!/usr/bin/env bash

openssl enc -d -aes-256-cbc -in files/encrypted -out files/decrypted.txt -pass pass:.key 