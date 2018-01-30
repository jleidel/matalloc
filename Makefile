#!/bin/bash

CC=gcc
CFLAGS=-O0 -Wall -g

all: 2d.exe 3d.exe
2d.exe: ./src/2d.c
	$(CC) $(CFLAGS) -o $@ $<
3d.exe: ./src/3d.c
	$(CC) $(CFLAGS) -o $@ $<
clean:
	rm -Rf 2d.exe 3d.exe
