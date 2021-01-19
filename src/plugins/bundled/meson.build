
subdir('rmap')

bundled_plugins_moc_files = qt5.preprocess(moc_headers : 'bundled_plugins.hpp', dependencies:[socexplorer_dep])

bundled_plugins = static_library('bundled_plugins', ['bundled_plugins.cpp', bundled_plugins_moc_files],
        extra_files:['bundled_plugins.hpp', 'bundled_plugins.json'],
        dependencies:[socexplorer_dep, rmap_plugin_dep],
        cpp_args: ['-DQT_STATICPLUGIN', '-DQT_PLUGIN'])

bundled_plugins_dep = declare_dependency(link_with: bundled_plugins, include_directories: '.')
