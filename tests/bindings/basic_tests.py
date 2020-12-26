#!/usr/bin/env python

import unittest
from ddt import ddt, data, unpack
from SocExplorerBindings import SocExplorer
import struct


@ddt
class APlugin(unittest.TestCase):
    def test_can_be_constructed(self):
        p = SocExplorer.PySocModule("")
        self.assertIsNotNone(p)

    def test_returns_no_widget_by_default(self):
        p = SocExplorer.PySocModule("")
        self.assertIsNone(p.ui())

    def test_has_max_int_as_default_vid_pid(self):
        p = SocExplorer.PySocModule("")
        max_int64 = 2 ** 64 -1
        self.assertEqual(p.vid, max_int64)
        self.assertEqual(p.pid, max_int64)

    @data("", "SomeRandomName", "1otherN@me")
    def test_gets_its_name_from_ctor(self, name):
        p = SocExplorer.PySocModule(name)
        self.assertEqual(p.name(), name)


class APluginHierarchy(unittest.TestCase):
    def setUp(self):
        self.root = SocExplorer.PySocModule("root")
        SocExplorer.PySocModule("child1", self.root)
        SocExplorer.PySocModule("child2", self.root)

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
