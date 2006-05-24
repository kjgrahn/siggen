#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
#
# $Id: test_siggen.py,v 1.2 2006/05/24 23:55:02 grahn Exp $
#
# Copyright (c) 2006 Jörgen Grahn.
# All rights reserved.
import unittest
import siggen

class test(unittest.TestCase):
    ten_three = ('=============\n'
                 '==##########=\n'
                 '=##########==\n'
                 '==##########=\n'
                 '=============\n')
    def assertExp(self, template, fortune, result):
        self.assertEqual(siggen.fill(template, fortune),
                         result)
    def testSimple(self):
        self.assertExp(self.ten_three, 'foobar foobar foobar',
                       '=============\n'
                       '==foobar    =\n'
                       '=foobar    ==\n'
                       '==foobar    =\n'
                       '=============\n')

    def testHunger(self):
        self.assertExp(self.ten_three, 'foo',
                       '=============\n'
                       '==foo       =\n'
                       '=          ==\n'
                       '==          =\n'
                       '=============\n')
    def testSpacing(self):
        self.assertExp(self.ten_three, '  foo,  foo   ',
                       '=============\n'
                       '==foo, foo  =\n'
                       '=          ==\n'
                       '==          =\n'
                       '=============\n')
    def testMoreSpacing(self):
        self.assertExp(self.ten_three, 'a b c d e f g h i jj k l m n oo',
                       '=============\n'
                       '==a b c d e =\n'
                       '=f g h i jj==\n'
                       '==k l m n oo=\n'
                       '=============\n')
    def testStuffing(self):
        self.assertExp(self.ten_three, 'power to the user',
                       '=============\n'
                       '==power to  =\n'
                       '=the user  ==\n'
                       '==          =\n'
                       '=============\n')

if __name__ == "__main__":
    unittest.main()
