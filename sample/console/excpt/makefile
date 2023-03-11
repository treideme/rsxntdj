#
# Makefile for try1,try2,try3
#

include ..\..\rsxntmak.gnu

all: try1.exe try2.exe try3.exe

try1.exe: try1.o $(RSXNTDJ)\lib\excpt.a
	$(CC) $(LDFLAGS) $< -lex -o try1.exe

try2.exe: try2.o $(RSXNTDJ)\lib\excpt.a
	$(CC) $(LDFLAGS) $< -lex -o try2.exe

try3.exe: try3.o $(RSXNTDJ)\lib\excpt2.a
	$(CC) $(LDFLAGS) $< -lex2 -o try3.exe

###

try1.o: try1.c $(RSXNTDJ)\include\excpt.h

try2.o: try2.c $(RSXNTDJ)\include\excpt.h

try3.o: try3.c $(RSXNTDJ)\include\excpt.h
