#!/bin/sh

gcc -lcrypto -lgmp -o bin/key2wif src/base58check.c src/key2wif.c
