#!/usr/bin/env python
# -*- coding: iso-8859-1 -*-
#
# $Id: test_siggen.py,v 1.1 2006/05/20 18:25:38 grahn Exp $
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
                       '==foo,      =\n'
                       '=foo       ==\n'
                       '==          =\n'
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
