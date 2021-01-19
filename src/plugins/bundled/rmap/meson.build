
rmap_plugin_moc_files = qt5.preprocess(moc_headers : 'rmap_plugin.hpp', dependencies:[socexplorer_dep])

rmap_plugin = static_library('rmap_plugin', ['rmap_plugin.cpp', rmap_plugin_moc_files],
        extra_files:['rmap_plugin.hpp'],
        dependencies:[socexplorer_dep, SpaceWireZMQ_dep],
        cpp_args: ['-DQT_STATICPLUGIN', '-DQT_PLUGIN'])

rmap_plugin_dep = declare_dependency(link_with: rmap_plugin, include_directories: '.')
