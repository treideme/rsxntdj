.PHONY: test

CFLAGS=-Wall
CC=gcc
CXX=g++
WINDRES=windres
RM=rm -f

# This test verifies that there are no serious bugs
# or typos in the headers.

# Expect warnings on c++ if compiler doesn't know of
# the comobject attribute

test:
	$(CC) $(CFLAGS) -I. -c test.c
	$(CXX) $(CFLAGS) -DNOCOMOBJECT -DUNICODE -I. -c test.c
	$(WINDRES) --include-dir . -i res.rc
	$(RM) test.o
