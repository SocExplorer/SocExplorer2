socexplorer_src = files(
[
  'Soc/SocModule.cpp',
  'Soc/Soc.cpp',
  'Factory/SocExplorerFactory.cpp'
]
)

socexplorer_headers = files(
[
  'Workspace.hpp',
  'SocExplorerObject.hpp',
  'plugin/ISocModule.hpp',
  'plugin/ISoc.hpp',
  'Soc/SocModule.hpp',
  'Soc/Soc.hpp',
  'Factory/SocExplorerFactory.hpp'
]
)

socexplorer_moc_files = qt5.preprocess(moc_headers : socexplorer_headers)

socexplorer_lib = library('socexplorer',
                          socexplorer_src,
                          socexplorer_moc_files,
                          dependencies:[qt5core, qt5widgets, qt5gui,opaque_dep,range_dep, cpp_utils_dep],
                          extra_files:socexplorer_headers
                          )

socexplorer_dep = declare_dependency(link_with:socexplorer_lib,
                      dependencies:[qt5core, qt5widgets, qt5gui,opaque_dep,range_dep, cpp_utils_dep],
                      include_directories : ['.'])

subdir('bindings')
