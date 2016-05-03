CC=gcc
CFLAGS=-Wall -fgnu-tm

all:
	$(CC) -Wall -fgnu-tm -o tx_linked_list tx_linked_list.c
