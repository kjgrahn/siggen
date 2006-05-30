#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
#
# $Id: siggen.py,v 1.2 2006/05/30 21:47:04 grahn Exp $
#
# Copyright (c) 2006 Jörgen Grahn.
# All rights reserved.
"""formatting texts into filler parts of a sig file
"""
import re
import random

def _lentab(ss):
    nn = []
    n = 0
    for s in ss:
        n += len(s)
        nn.append(n)
        n += 1
    return nn

class Subs:
    def __init__(self, s):
        self.ss = s.split()
        self.nn = _lentab(self.ss)
    def consume(self, n):
        parts = 0
        for k in self.nn:
            if k > n: break
            parts += 1
        # include the first 'parts' of self.ss
        res = ' '.join(self.ss[:parts])
        del self.ss[:parts]
        self.nn = _lentab(self.ss)
        return res + ' ' * (n - len(res))

def fill(template, fortune):
    """
    """
    pat = re.compile(r'(#+)')
    subs = Subs(fortune)
    acc = []
    for t in pat.split(template):
        if not t.startswith('#'):
            acc.append(t)
            continue
        n = len(t)
        acc.append(subs.consume(n))
    return ''.join(acc)

class Fortunes:
    def __init__(self, f):
        lines = f.readlines()
        random.shuffle(lines)
        self._lines = lines
    def get(self):
        s = self._lines[0]
        del self._lines[0]
        return s

if __name__ == "__main__":
    import sys
    import os
    import getopt

    prog = os.path.split(sys.argv[0])[1]
    usage = 'usage: %s -f quotes-file signature-file' % prog
    try:
        opts, argv = getopt.getopt(sys.argv[1:], 'f:')
        fortunes = None
        for option, value in opts:
            if option == '-f': fortunes = value
        if not fortunes:
            raise ValueError('required argument missing')
        template, = argv
    except (ValueError, getopt.GetoptError), s:
        print >>sys.stderr, 'error:', s
        print >>sys.stderr, usage
        sys.exit(1)

    fortunes = Fortunes(open(fortunes, 'r'))
    template = open(template, 'r').read()
    sys.stdout.write(fill(template, fortunes.get()))
