#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
#
# $Id: siggen.py,v 1.1 2006/05/20 18:25:38 grahn Exp $
#
# Copyright (c) 2006 Jörgen Grahn.
# All rights reserved.
"""formatting texts into filler parts of a sig file
"""
import re

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

if __name__ == "__main__":
    pass
