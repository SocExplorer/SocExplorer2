#!/usr/bin/env python

import unittest
from SocExplorerBindings import SocExplorer


class AWorkspace(unittest.TestCase):
    def test_can_be_constructed(self):
        s = SocExplorer.Soc("Leon3")
        w = SocExplorer.Workspace(s,"Workspace")
        self.assertIsNotNone(w)

    def test_gives_access_to_its_soc(self):
        s = SocExplorer.Soc("Leon3")
        w = SocExplorer.Workspace(s,"Workspace")
        self.assertIs(s, w.soc())

    def test_allows_to_set_its_root_Module(self):
        s = SocExplorer.Soc("Leon3")
        w = SocExplorer.Workspace(s,"Workspace")
        m = SocExplorer.PySocModule("Module", w)
        w.set_root_module(m)
        self.assertIs(m, w.root_module())

if __name__ == '__main__':
    unittest.main()
