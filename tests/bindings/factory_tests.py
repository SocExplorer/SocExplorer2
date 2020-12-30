#!/usr/bin/env python

import unittest
from ddt import ddt, data, unpack
from SocExplorerBindings import SocExplorer
import struct


class MyFac(SocExplorer.SocCtor_t):
    def __init__(self):
        super(MyFac, self).__init__()

    def __dell__(self):
        print("oups")

    def __call__(self,name,parent=None):
        return SocExplorer.Soc(name,parent)


@ddt
class AFactory(unittest.TestCase):
    def test_can_be_constructed(self):
        f = SocExplorer.SocExplorerFactory()
        self.assertIsNotNone(f)

    def test_can_register_soc_factory_and_build_soc(self):
        f = SocExplorer.SocExplorerFactory()
        f.register_soc_ctor("MyFac",MyFac())
        s = f.new_soc("MyFac","A Soc")
        self.assertIsNotNone(s)
        self.assertEqual(s.name(),"A Soc")




if __name__ == '__main__':
    unittest.main()
