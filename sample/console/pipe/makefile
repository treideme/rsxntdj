#
# Makefile for pipe
#
# call 'make crt=1' to use C runtime DLL
#

include ..\..\rsxntmak.gnu

applications: pipe.exe pipew.exe piper.exe

pipe.exe: pipe.o
	$(CC) $(LDFLAGS) $< -o $@

pipew.exe: pipew.o
	$(CC) $(LDFLAGS) $< -o $@

piper.exe: piper.o
	$(CC) $(LDFLAGS) $< -o $@
