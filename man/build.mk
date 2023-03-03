MANDIR	= $(DESTDIR)$(PREFIX)/share/man/

install-man:
	install -d $(MANDIR)man8/
	install -m 644 man/istar-cli.8 $(MANDIR)man8/
	install -d $(MANDIR)man5/
	install -m 644 man/istar.lisp.5 $(MANDIR)man5/
