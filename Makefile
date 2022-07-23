DESTDIR    =
PREFIX     =/usr/local
CC         =gcc
CFLAGS     =-Wall -g
CFLAGS_ALL =$(LDFLAGS) $(CFLAGS) $(CPPFLAGS)
PROGRAMS   =vcard2rec$(EXE)
HEADERS    =rfc6350.h

##
all: $(PROGRAMS)
clean:
	rm -f $(PROGRAMS)
install: $(PROGRAMS)
	install -d $(DESTDIR)$(PREFIX)/bin
	install -m755 $(PROGRAMS) $(DESTDIR)$(PREFIX)/bin
	install -d $(DESTDIR)$(PREFIX)/include
	install -m644 $(HEADERS) $(DESTDIR)$(PREFIX)/include

vcard2rec$(EXE): vcard2rec.c rfc6350.h
	$(CC) -o $@ vcard2rec.c $(CFLAGS_ALL) $(LIBS)

## -- manpages --
ifneq ($(PREFIX),)
MAN_1=./vcard2rec.1 
install: install-man1
install-man1: $(MAN_1)
	mkdir -p $(DESTDIR)$(PREFIX)/share/man/man1
	cp $(MAN_1) $(DESTDIR)$(PREFIX)/share/man/man1
MAN_3=./rfc6350.3 
install: install-man3
install-man3: $(MAN_3)
	mkdir -p $(DESTDIR)$(PREFIX)/share/man/man3
	cp $(MAN_3) $(DESTDIR)$(PREFIX)/share/man/man3
endif
## -- manpages --
## -- license --
ifneq ($(PREFIX),)
install: install-license
install-license: LICENSE
	mkdir -p $(DESTDIR)$(PREFIX)/share/doc/c-vcard2rec
	cp LICENSE $(DESTDIR)$(PREFIX)/share/doc/c-vcard2rec
endif
## -- license --
