#!/usr/bin/env python

import unittest
from SocExplorerBindings import SocExplorer
import struct


class APySocModule(unittest.TestCase):
    def setUp(self):
        self.soc = SocExplorer.Soc("default")

    def test_can_be_constructed(self):
        p = SocExplorer.PySocModule("", self.soc)
        self.assertIsNotNone(p)

    def test_returns_no_widget_by_default(self):
        p = SocExplorer.PySocModule("", self.soc)
        self.assertIsNone(p.ui())

    def test_has_max_int_as_default_vid_pid(self):
        p = SocExplorer.PySocModule("", self.soc)
        max_int64 = 2 ** 64 -1
        self.assertEqual(p.vid, max_int64)
        self.assertEqual(p.pid, max_int64)


class APySocModuleHierarchy(unittest.TestCase):
    def setUp(self):
        self.soc = SocExplorer.Soc("default")
        self.root = SocExplorer.PySocModule("root", self.soc)
        SocExplorer.PySocModule("child1", self.soc, self.root)
        SocExplorer.PySocModule("child2", self.soc, self.root)

    def test_parent_plugin_list_children(self):
        children = self.root.children()
        self.assertEqual(len(children), 2)
        for child in children:
            self.assertIn("child", child.name())

    def test_child_plugin_has_a_parent(self):
        children = self.root.children()
        for child in children:
            parent = child.parent()
            self.assertIsNotNone(parent)
            self.assertIs(parent, self.root)



if __name__ == '__main__':
    unittest.main()
