CC=gcc
MODULES = $(wildcard src/*.c)
DESTDIR=/opt/hipster

all: hipster.c 
	$(CC) hipster.c -o hipster $(MODULES)

install: hipster
	install -d $(DESTDIR)
	install hipster $(DESTDIR)
	install scripts/hipster.cfg $(DESTDIR)
