#!/usr/bin/env python

import unittest
from ddt import ddt, data
from SocExplorerBindings import SocExplorer
import struct


@ddt
class ASocExplorerObject(unittest.TestCase):

    @data("", "SomeRandomName", "1otherN@me")
    def test_gets_its_name_from_ctor(self, name):
        p = SocExplorer.SocExplorerObject(name)
        self.assertEqual(p.name(), name)

    @data("", "SomeRandomName", "1otherN@me")
    def test_can_be_renamed(self, name):
        p = SocExplorer.SocExplorerObject("")
        p.set_name(name)
        self.assertEqual(p.name(), name)


if __name__ == '__main__':
    unittest.main()
