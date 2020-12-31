#!/usr/bin/env python

import unittest
from SocExplorerBindings import SocExplorer


class MyFac(SocExplorer.SEObjectCtor_t):
    def __init__(self):
        super(MyFac, self).__init__()

    def __call__(self,name,parent=None):
        return SocExplorer.Soc(name,parent)

class MyModuleFac(SocExplorer.SEObjectCtor_t):
    def __init__(self):
        super(MyModuleFac, self).__init__()

    def __call__(self,name,soc,parent=None):
        return SocExplorer.PySocModule(name,soc,parent)


class AFactory(unittest.TestCase):
    def test_can_be_constructed(self):
        f = SocExplorer.SocExplorerFactory()
        self.assertIsNotNone(f)

    def test_can_register_soc_factory_and_build_it(self):
        f = SocExplorer.SocExplorerFactory()
        f.register_ctor("MyFac",MyFac())
        s = f.new_object("MyFac","A Soc")
        self.assertIsNotNone(s)
        self.assertEqual(s.name(),"A Soc")

    def test_can_register_module_factory_and_build_it(self):
        f = SocExplorer.SocExplorerFactory()
        f.register_ctor("MyFac",MyFac())
        f.register_ctor("MyModuleFac",MyModuleFac())
        m = f.new_object("MyModuleFac","A Module",f.new_object("MyFac","A Soc"))
        self.assertIsNotNone(m)
        self.assertEqual(m.name(),"A Module")


if __name__ == '__main__':
    unittest.main()
