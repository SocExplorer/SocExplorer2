socexplorer_src = files(
[
  'Soc/SocModule.cpp',
  'Soc/Soc.cpp'
]
)

socexplorer_headers = files(
[
  'Workspace.hpp',
  'SocExplorerObject.hpp',
  'plugin/ISocModule.hpp',
  'plugin/ISoc.hpp',
  'Soc/SocModule.hpp',
  'Soc/Soc.hpp'
]
)

socexplorer_moc_files = qt5.preprocess(moc_headers : socexplorer_headers)

socexplorer_lib = library('socexplorer',
                          socexplorer_src,
                          socexplorer_moc_files,
                          dependencies:[qt5core, qt5widgets, qt5gui,opaque_dep,range_dep])

socexplorer_dep = declare_dependency(link_with:socexplorer_lib,
                      dependencies:[qt5core, qt5widgets, qt5gui,opaque_dep,range_dep],
                      include_directories : ['.'])

subdir('bindings')
