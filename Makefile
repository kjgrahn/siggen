# $Id: Makefile,v 1.1 2006/05/30 21:47:04 grahn Exp $
#
# Makefile
#
# Copyright (c) 2003, 2004, 2005, 2006 Jörgen Grahn.
# All rights reserved.

INSTALLBASE=/usr/local

.PHONY: all
all:

.PHONY: install
install:
	install -m555 siggen.py $(INSTALLBASE)/bin/siggen
	install -m444 siggen.1 $(INSTALLBASE)/man/man1/

.PHONY: test
test: test_siggen.py
	for py in $^; \
	do PYTHONPATH=.. python $$py; \
	done

.PHONY: clean
clean:
	$(RM) *.pyc *.pyo

.PHONY: TAGS

love:
	@echo "not war?"
