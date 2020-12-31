#!/usr/bin/env python

import unittest
from SocExplorerBindings import SocExplorer, Endianness


class ASoc(unittest.TestCase):
    def test_can_be_constructed(self):
        p = SocExplorer.Soc("")
        self.assertIsNotNone(p)

    def test_default_endianness_is_unknown(self):
        p = SocExplorer.Soc("")
        self.assertEquals(p.endianness(), Endianness.Endianness.unknown)

    def test_can_set_and_read_variables(self):
        p = SocExplorer.Soc("")
        p.set_value("some key", 10)
        self.assertEquals(p.value("some key"), 10)

    def test_can_overwrite_variable(self):
        p = SocExplorer.Soc("")
        p.set_value("some key", 10)
        p.set_value("some key", "another value")
        self.assertEquals(p.value("some key"), "another value")



if __name__ == '__main__':
    unittest.main()
