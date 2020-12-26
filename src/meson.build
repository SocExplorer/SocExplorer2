socexplorer_src = files(
[
  'plugin/SocModule.cpp'
]
)

socexplorer_headers = files(
[
  'plugin/SocModule.hpp'
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
