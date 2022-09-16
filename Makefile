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
install: install-man1
install-man1:
	@echo 'I share/man/man1/'
	@mkdir -p $(DESTDIR)$(PREFIX)/share/man/man1
	@echo 'I share/man/man1/vcard2rec.1'
	@cp ./vcard2rec.1 $(DESTDIR)$(PREFIX)/share/man/man1
install: install-man3
install-man3:
	@echo 'I share/man/man3/'
	@mkdir -p $(DESTDIR)$(PREFIX)/share/man/man3
	@echo 'I share/man/man3/rfc6350.3'
	@cp ./rfc6350.3 $(DESTDIR)$(PREFIX)/share/man/man3
## -- manpages --
## -- license --
ifneq ($(PREFIX),)
install: install-license
install-license: LICENSE
	@echo 'I share/doc/c-vcard2rec/LICENSE'
	@mkdir -p $(DESTDIR)$(PREFIX)/share/doc/c-vcard2rec
	@cp LICENSE $(DESTDIR)$(PREFIX)/share/doc/c-vcard2rec
endif
## -- license --
