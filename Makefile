#
# Makefile
#
# Copyright (c) 2010--2024 Jörgen Grahn
# All rights reserved.

SHELL=/bin/bash
INSTALLBASE=/usr/local
CXXFLAGS=-Wall -Wextra -pedantic -std=c++17 -g -Os -Wold-style-cast
CPPFLAGS=
ARFLAGS=rTP

.PHONY: all
all: siggen
all: tests

.PHONY: install
install: siggen siggen.1
	install -d $(INSTALLBASE)/{bin,man/man1}
	install -m755 siggen $(INSTALLBASE)/bin/
	install -m644 siggen.1 $(INSTALLBASE)/man/man1/

.PHONY: check checkv
check: tests
	./tests
checkv: tests
	valgrind -q ./tests -v

libsiggen.a: render.o
libsiggen.a: fortune.o
libsiggen.a: split.o
libsiggen.a: files...o
	$(AR) $(ARFLAGS) $@ $^

siggen: siggen.o libsiggen.a
	$(CXX) $(CXXFLAGS) -o $@ siggen.o -L. -lsiggen

libtest.a: test/render.o
libtest.a: test/split.o
libtest.a: test/files...o
	$(AR) $(ARFLAGS) $@ $^

test/%.o: CPPFLAGS+=-I.

test.cc: libtest.a
	orchis -o$@ $^

tests: test.o libsiggen.a libtest.a
	$(CXX) $(CXXFLAGS) -o $@ test.o -L. -ltest -lsiggen

.PHONY: tags TAGS
tags: TAGS
TAGS:
	ctags --exclude='test' -eR . --extra=q

.PHONY: clean
clean:
	$(RM) siggen
	$(RM) {,test/}*.o
	$(RM) lib*.a
	$(RM) test.cc tests
	$(RM) TAGS
	$(RM) -r dep/

love:
	@echo "not war?"

$(shell mkdir -p dep/test)
DEPFLAGS=-MT $@ -MMD -MP -MF dep/$*.Td
COMPILE.cc=$(CXX) $(DEPFLAGS) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c

%.o: %.cc
	$(COMPILE.cc) $(OUTPUT_OPTION) $<
	@mv dep/$*.{Td,d}

dep/%.d: ;
dep/test/%.d: ;
-include dep/*.d
-include dep/test/*.d
